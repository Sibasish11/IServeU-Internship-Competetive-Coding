# **MQTT Audio Player** 🚀

## Problem Statement 📋

**MQTT CONTROLLED AUDIO PLAYBACK QUEUE**: C program that connects to a non-SSL MQTT broker.\
**TASK OVERVIEW**: A C program that connects to non-SSL MQTT Broker domain, subscribes to topic mobile number, parses incoming JSON messages: `{ "file": "beep.wav", "priority": 1 }`, plays the files from one storage. These playback must happen in separate thread.

This project implements an audio player that subscribes to an MQTT topic, receives JSON messages containing audio file names and priorities, and plays the audio files in a priority-based order using a threaded playback system. The application is built in C, utilizing the Paho MQTT library for MQTT communication, cJSON for JSON parsing, and the `aplay` command for audio playback on Linux systems. 🎵

## Features 🎉

- 🔗 Subscribes to an MQTT topic to receive audio playback instructions.
- 📜 Parses JSON messages to extract audio file names and priorities.
- 📊 Maintains a priority queue for audio tasks, ensuring higher-priority audio files are played first.
- 🧵 Uses a separate thread for audio playback to avoid blocking the main MQTT loop.
- 🔊 Plays audio files stored in a `storage/` directory using the `aplay` command.

## Prerequisites 🛠️

- **Linux System**: The application uses the `aplay` command, which is typically available on Linux systems. 🐧
- **Dependencies**:
  - `gcc` (GNU Compiler Collection)
  - `make` (for building the project)
  - `aplay` (part of the ALSA utilities for audio playback)
  - `libpthread` (for threading support)
- **Libraries**:
  - Paho MQTT C library (included in `libs/paho`) 📡
  - cJSON library (included in `libs/cJSON`) 📄

## About the Developer 👨‍💻

![Developer coding](path/to/your-photo.jpg)This project was developed with passion and curiosity for MQTT and audio processing. The photo above captures me in action, coding this project.

## Installation ⚙️

1. **Clone the Repository**:

   ```bash
   git clone https://github.com/your-username/mqtt-audio-player.git
   cd mqtt-audio-player
   ```

2. **Ensure Audio Files**:

   - Place your audio files (e.g., `.wav` files) in a `storage/` directory within the project root. The `aplay` command will look for files in this directory. 📂

3. **Build the Project**:

   - Run the following command to compile the application:

     ```bash
     make
     ```

   - This will generate the `audio_player` executable. 🖥️

4. **Install Dependencies** (if not using the included libraries):

   - Ensure the Paho MQTT C library and cJSON library are available. The provided `libs/` directory includes these libraries, so no external installation is needed unless you want to use different versions.

## Usage 🎮

1. **Run the Application**:

   ```bash
   ./audio_player
   ```

   - The application connects to the MQTT broker at `tcp://broker.hivemq.com:1883` with the client ID `AudioClient123` and subscribes to the topic `9876543210`. 🌐

2. **Send MQTT Messages**:

   - Publish JSON messages to the MQTT topic `9876543210` with the following format:

     ```json
     {
       "file": "example.wav",
       "priority": 1
     }
     ```

   - The `file` field specifies the audio file name (must be in the `storage/` directory).

   - The `priority` field determines the playback order (lower values indicate higher priority). 🔢

3. **Example MQTT Publish Command** (using `mosquitto_pub`):

   ```bash
   mosquitto_pub -h broker.hivemq.com -t 9876543210 -m '{"file":"example.wav","priority":1}'
   ```

## Project Structure 📁

- `main.c`: Main application logic, handles MQTT connection and subscription.
- `playback.c`: Implements the audio playback thread and priority queue.
- `playback.h`: Header file for playback-related functions.
- `Makefile`: Build script for compiling the application.
- `libs/paho/`: Paho MQTT C library source files.
- `libs/cJSON/`: cJSON library source files.
- `storage/`: Directory where audio files should be placed (not included in the repository).

## Configuration 🔧

- **MQTT Broker**: Modify the `ADDRESS` macro in `main.c` to use a different MQTT broker if needed.
- **Client ID**: Change the `CLIENTID` macro in `main.c` for a unique client identifier.
- **Topic**: Update the `TOPIC` macro in `main.c` to subscribe to a different MQTT topic.
- **Timeout and QoS**: Adjust `TIMEOUT` and `QOS` in `main.c` for different connection or quality-of-service settings.

## Cleaning Up 🧹

To remove compiled files and the executable:

```bash
make clean
```

## Notes 📝

- Ensure the `storage/` directory exists and contains valid `.wav` files compatible with `aplay`.
- The application assumes the MQTT broker does not require authentication. For brokers requiring credentials, modify the `connectData` structure in `main.c` to include username and password.
- The priority queue ensures that audio files with lower priority numbers are played first. If multiple files have the same priority, they are played in the order they were received.

## Troubleshooting 🐞

- **MQTT Connection Issues**: Verify the broker address and port. Ensure the broker is accessible and does not require authentication.
- **Audio Playback Issues**: Confirm that `aplay` is installed and that audio files in `storage/` are valid `.wav` files.
- **JSON Parsing Errors**: Ensure published MQTT messages follow the correct JSON format.

## Contributing 🤝

Contributions are welcome! Please submit a pull request or open an issue for bug reports or feature requests.

## License 📜

This project is licensed under the MIT License. See the LICENSE file for details.

## Disclaimer ⚠️

This project is not my own creation. I took help from mentors, seniors at that event, quite significantly AI because this topic was out of my competency at that moment and hence required a lot of research about MQTT and SSL. Also no i did not present a code generated by AI at the event, i used my code there but there i wasn't able to even complete their given task, even they allowed research about MQTT at that moment because they too believed we as participants were not too familiar with fintech technologies.