# Smart Bulb

This was a project created by Team IoT Moment for the course Introduction to IoT Spring 2022. 

* This project makes uses IoT to make a Smart Bulb that uses a power saving model that switches the bulb off when there is no person in the room and dims it by the amount of light in the room.
* Components used - 
    1. ESP-32
    2. Bulb
    3. 2x Ultrasonic Sensors
    4. Light Dependent Resistor
    5. Breadboard and Connecting Wires
* This project also uploads the data to the cloud using oneM2M and uses all that data to operate the website which is made using Flask for Backend and Html/CSS for Frontend. The website shows data regarding the usage of the bulb and also provides the users with buttons to dominate all conditions and control the bulb.
* Setup all the hardware and run ```start.bat``` or ```start.sh``` to run oneM2M. To run the flask server,run ```server.py``` in another terminal and go to the link given there.
