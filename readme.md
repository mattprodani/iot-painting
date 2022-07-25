# IoT Painting

## Description
This project allows the use of an Arduino to use paint as a capactive conductor.
We will use the response from the conductor to control HUE lights.

## Tools
* ESP8266 microcontroller (Any microcontroller with Wi-Fi and battery support)
* Copper tape
* Conductive Paint [Bare Conductive Paint](https://www.bareconductive.com/collections/electric-paint)
* IFTTT account for sending webhook requests

## Process Overview
* Connect the ESP8266 to the Conductive Paint
  * To do this, connect a wire to the breadboard capacitive pins, 
  and the other side to a connected strip of paint using the copper tape.
  * I put the breadboard in the back of the canvas and painted across the edges to connect.
* Find trigger thresholds for conductivity by using the debug mode and looking at the values in the serial monitor.
  * Notes: These are tricky, grounding for voltage from the battery is sometimes necessary.
* Load the *hue.ino* script after configuring threshold, API key, and Wi-Fi connections.
* Webhooks requests should then be sent when the painting is tapped.