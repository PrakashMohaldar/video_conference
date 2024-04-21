# Video Conference Application

This is a simple video conference application that allows communication between two devices over a network.

## Installation

Before running the application, make sure you have the required packages installed. You can install them using the following commands:

```bash
sudo apt-get install gstreamer1.0-plugins-bad gstreamer1.0-plugins-good
sudo apt-get install gstreamer1.0-libav
sudo apt-get install libgstreamer1.0-dev
```

## Usage

### 1 Initiating call as sender (Device 1)
1. Navigate to the `video_conference` directory:
```bash
cd ./video_conference
```
2. Compile the `transmit.c` file:
```bash
g++ -o initiate receive.c $(pkg-config --cflags --libs gstreamer-1.0)

```
3. Initiate the call by executing the compiled program with the IP address of the receiver (Device 2):
```bash
./initiate <Device_2_IP_address>
```

### 2 Recieving call as reciever (Device 2)
1. Navigate to the `video_conference` directory:
```bash
cd ./video_conference
```
2. Compile the `receive.c` file:
```bash
./initiate <Device_2_IP_address>
```
3. Receive the call by executing the compiled program with the IP address of the sender (Device 1):
```bash
./initiate <Device_1_IP_address>
```

### Notes

- Replace `<Device_1_IP_address>` and `<Device_2_IP_address>` with the actual IP addresses of the devices.
- Ensure that both devices are connected to the same network for communication to occur.
