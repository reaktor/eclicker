# [Read part 1 here](https://discourse.reaktor.com/t/hobby-project-a-programmable-internet-connected-keyfob-using-narrowband-iot/3525)

# TL;DR
In my post 3 weeks ago, I proposed creating a programmable physical clicker device (similar to a garage door opener) that could be used for simple transactional situations where

# Video Overview
[![IMAGE ALT TEXT HERE](https://img.youtube.com/vi/z0r-3W1F3kc/0.jpg)](https://www.youtube.com/watch?v=z0r-3W1F3kc)

# The Gear
Virtually none of the physical components I originally planned on were used in the actual

### Arduino Uno
![](https://i.imgur.com/t3gIHFA.png)

### Waveshare E-ink Display
![](https://i.imgur.com/XXpPBYs.png)

### Just A Battery
![](https://i.imgur.com/JglD39x.png)

# The Design

### Diagram
![](https://i.imgur.com/r6RPICb.png)

### Schematic
![](https://i.imgur.com/llkntUk.png)

# The Build
![](https://i.imgur.com/6ZhMcEQ.jpg)
![](https://i.imgur.com/ODHr4h9.jpg)
![](https://i.imgur.com/lHd85V1.jpg)


# The Software
https://github.com/reaktor/eclicker

# Road Map
1. Make a device that sends data (even just a single ping) over CAT-M1
1. ~Connect a 4 button keypad to the device, and send a 4 bit message when any of the buttons is pressed~
1. ~Receive the 4 bit message and convert it to JSON and then forward the request over HTTP~
1. ~Attach an e-ink display and make it show a static, unchangable list of button labels~
1. ~Build a feature that allows the e-ink labels to be updated with a network request~
1. ~Build a physical hardware button that fetches triggers the label update behavior.~
1. ~Build a web portal to configure the routing of the HTTP requests.~
1. Build a POC dog walker app.
1. Build a POC pizza app.
1. Build a device enclosure