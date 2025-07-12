#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "playback.h"

typedef struct AudioTask {
    char filename[256];
    int priority;
    struct AudioTask* next;
} AudioTask;

AudioTask* queue_head = NULL;
pthread_mutex_t queue_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void enqueue_audio(const char* filename, int priority) {
    AudioTask* new_task = malloc(sizeof(AudioTask));
    strcpy(new_task->filename, filename);
    new_task->priority = priority;
    new_task->next = NULL;

    pthread_mutex_lock(&queue_mutex);
    if (!queue_head || priority < queue_head->priority) {
        new_task->next = queue_head;
        queue_head = new_task;
    } else {
        AudioTask* current = queue_head;
        while (current->next && current->next->priority <= priority) {
            current = current->next;
        }
        new_task->next = current->next;
        current->next = new_task;
    }
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&queue_mutex);
}

void* playback_loop(void* arg) {
    while (1) {
        pthread_mutex_lock(&queue_mutex);
        while (!queue_head) {
            pthread_cond_wait(&cond, &queue_mutex);
        }

        AudioTask* task = queue_head;
        queue_head = task->next;
        pthread_mutex_unlock(&queue_mutex);

        char cmd[300];
        snprintf(cmd, sizeof(cmd), "aplay storage/%s", task->filename);
        system(cmd);
        free(task);
    }
    return NULL;
}

void init_playback_thread() {
    pthread_t tid;
    pthread_create(&tid, NULL, playback_loop, NULL);
    pthread_detach(tid);
}
