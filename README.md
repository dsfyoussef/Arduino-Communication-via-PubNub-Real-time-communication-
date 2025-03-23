# Arduino-Communication-via-PubNub-Real-time-communication-
Arduino Communication via PubNub (Real time communication )
Read the pdf to know the details.
Objective: In this project, the goal is to establish communication between two Arduino devices using the PubNub platform for real-time data exchange. The communication is achieved through three main steps:
		-Setting up a Web Server on the First Arduino
		-Publishing Data from the First Arduino to PubNub
		-Receiving Data on the Second Arduino from PubNub
		-This project involves using the PubNub API and Arduino IDE to communicate over the internet, making the process ideal for IoT (Internet of Things) applications.

Tools & Components:
-Arduino Uno boards (2 units)
-Ethernet Shields (for connecting Arduinos to the internet)
-PubNub Account
-LAN network (local network to assign IPs via DHCP)
-Arduino IDE
-PubNub API keys (for publishing and subscribing to messages)

Project Overview
1. Arduino Web Server Setup
The first part of this project sets up an Arduino with an Ethernet shield as a local web server. This allows the Arduino to interact with devices over the local network.

2. Publishing Data to PubNub
The second Arduino sends a "Bonjour" message to PubNub in a JSON format. This is done using the PubNub publish API, which allows the message to be sent to a specific channel.

3. Receiving Data from PubNub
The second Arduino subscribes to the same PubNub channel to receive the data sent from the first Arduino. Once the message is received, it is displayed on the serial monitor.

Steps to Set Up the Project
1. Set Up PubNub Account
Go to PubNub and create a free account.
Create a new application in the PubNub console.
Generate and save the Publish Key and Subscribe Key.
Set up a channel (e.g., CanalMTI1) for communication.
2. Prepare Arduino and Ethernet Shield
Attach the Ethernet Shield to your Arduino Uno.
Connect your Arduino to a LAN network that can assign it an IP address (via DHCP).
Ensure your Arduino is powered and ready for code upload.
3. Code Overview
This repository contains three parts of the code:

1. Web Server Code for Arduino (Arduino 1)
This code sets up a web server on the first Arduino to listen for incoming HTTP requests from other devices. It is ready to interact with the second Arduino.

2. Data Publishing Code (Arduino 1)
This code is responsible for publishing a message (e.g., "Bonjour") from the first Arduino to the PubNub platform.

3. Data Reception Code (Arduino 2)
The second Arduino subscribes to the PubNub channel and waits to receive the data sent by the first Arduino. It then displays the received message.

Detailed Explanation of the Code
Web Server Code (Arduino 1)
This code creates a simple HTTP web server on the Arduino, allowing the first Arduino to be reachable on a network. The code initializes the Ethernet connection and listens for incoming HTTP requests.

Key elements:

#include <Ethernet.h>: Manages the Ethernet connection.
EthernetServer server(80): Sets up the web server to listen on port 80.
Ethernet.begin(mac, ip): Initializes Ethernet with the defined MAC address and IP.
Data Publishing Code (Arduino 1)
This code sends a message ("Bonjour") to PubNub in the form of a JSON object. The Arduino communicates with the PubNub service to publish the message to a specific channel.

Key elements:

#include <PubNub.h>: Allows interaction with the PubNub API.
PubNub.begin(pubkey, subkey): Initializes PubNub with the publish and subscribe keys.
PubNub.publish(channel, message): Sends the message to the channel.
Data Reception Code (Arduino 2)
The second Arduino subscribes to the PubNub channel to receive the published message. It then processes and displays the message on the serial monitor.

Key elements:

PubSubClient *pclient = PubNub.subscribe(channel): Subscribes to the PubNub channel.
deserializeJson(doc, Message): Parses the JSON message.
serializeJsonPretty(doc, Serial): Formats the received JSON message for display.
