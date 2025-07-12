CC=gcc
CFLAGS=-Ilibs/paho -Ilibs/cJSON -pthread
LDFLAGS=
SOURCES=main.c playback.c libs/cJSON/cJSON.c libs/paho/MQTTClient.c libs/paho/MQTTLinux.c
OBJECTS=$(SOURCES:.c=.o)
EXEC=audio_player

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(EXEC) *.o playback.o main.o
