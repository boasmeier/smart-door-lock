# Smart Door Lock Docker Gateway
This folder contains the code for the gateway running on the Raspberry PI.
This will probably be split into two submodules containing the code for the communication to the IoT Device and separately the Backend.

## Connection
``
ssh pi@raspberrypi31
``

``
pw: raspberry
``

## Installation

``
curl -fsSL https://get.docker.com -o get-docker.sh
sudo sh get-docker.sh
``

``
sudo pip3 install docker-compose
``


``
cd door_lock_edge_agent
pip3 install -r requirements.txt 
``

## Run

MQTT Broker
``
sudo docker-compose up --build
``

Edge Agent
``
cd door_lock_edge_agent/src
``
``
python3 main.py
``
