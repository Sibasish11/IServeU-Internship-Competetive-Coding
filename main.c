#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "MQTTClient.h"
#include "cJSON.h"
#include "playback.h"

#define ADDRESS     "tcp://broker.hivemq.com:1883"  // Use your broker address
#define CLIENTID    "AudioClient123"
#define TOPIC       "9876543210"
#define QOS         1
#define TIMEOUT     10000L

void messageArrivedCallback(MessageData* data) {
    MQTTMessage* message = data->message;
    char* payload = (char*)message->payload;

    cJSON* json = cJSON_Parse(payload);
    if (json == NULL) {
        printf("Invalid JSON\n");
        return;
    }

    cJSON* file = cJSON_GetObjectItem(json, "file");
    cJSON* priority = cJSON_GetObjectItem(json, "priority");

    if (cJSON_IsString(file) && cJSON_IsNumber(priority)) {
        enqueue_audio(file->valuestring, priority->valueint);
    }

    cJSON_Delete(json);
}

int main() {
    MQTTClient client;
    Network network;
    unsigned char sendbuf[1000], readbuf[1000];

    NetworkInit(&network);
    NetworkConnect(&network, "broker.hivemq.com", 1883);

    MQTTClientInit(&client, &network, 3000, sendbuf, sizeof(sendbuf), readbuf, sizeof(readbuf));

    MQTTPacket_connectData connectData = MQTTPacket_connectData_initializer;
    connectData.MQTTVersion = 3;
    connectData.clientID.cstring = CLIENTID;

    if (MQTTConnect(&client, &connectData) != 0) {
        printf("MQTT Connect failed\n");
        return -1;
    }

    MQTTSubscribe(&client, TOPIC, QOS, messageArrivedCallback);

    init_playback_thread();

    while (1) {
        MQTTYield(&client, 1000);
    }

    return 0;
}
