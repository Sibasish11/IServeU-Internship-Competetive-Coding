#ifndef PLAYBACK_H
#define PLAYBACK_H

void init_playback_thread();
void enqueue_audio(const char* filename, int priority);

#endif
