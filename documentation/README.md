# [Read part 1 here](https://discourse.reaktor.com/t/hobby-project-a-programmable-internet-connected-keyfob-using-narrowband-iot/3525)

# TL;DR
In my post about 3 weeks ago, I proposed creating a programmable physical clicker device (similar to a garage door opener) that could be used for quick transactional situations where it's annoying to open a smart phone app.  Since that time, I've built out a prototype of the device which achieves essentially all of the functional goals described in that post.  This post is about how I built it, and the challenges I faced along the way.

# Video Overview
[![IMAGE ALT TEXT HERE](https://img.youtube.com/vi/z0r-3W1F3kc/0.jpg)](https://www.youtube.com/watch?v=z0r-3W1F3kc)

# The Gear
Virtually all of the physical components described in the original post proved to be unobtainable.  This is mostly due to the fact that IoT devices need to be certified by cell phone carriers, and cell phone carriers are only really interested in doing this for major corporations planning to produce thousands of devices.

### Arduino Uno
![image](file:///Users/mkorostoff/Arduino/documentation/img/t3gIHFA.png)

Arduino serves as the primary controller for this project.  It is responsible for interfacing with the physical buttons, addressing pixels on the epaper display, and sending network requests.  This hardware choice also mandated that I program the firmware in C++, a language I have never used before, and had to learn basically from scratch.

### CAT-M1 Modem:
![image](file:///Users/mkorostoff/Arduino/documentation/img/Nrb5a4Z.png)

This is the key piece that proved virtually impossible to obtain.  While two major phone carriers in the US (theoretically) supply dev kits which enable CAT-M1 connections, in practice they wouldn't return my calls.  For a minute, it seemed like my only real option would be to buy a chip direct from the manufacturer and solder it onto a board.  This is where [Botletics](https://www.botletics.com/) enters the picture.  Botletics is essentially just one dude (Timothy Woo) assembling circuit boards in his basement.  One Botletics product is the [SIM7000 Arduino shield for CAT-M1](https://www.botletics.com/products/sim7000-shield), which I purchased for $75.

### SIM Card from Hologram.io:
![image](file:///Users/mkorostoff/Arduino/documentation/img/fr1osOY.jpg)

From what I can tell, hologram is the only provider selling ready-to-use sim cards for CAT-M1 in the United States.  Major carriers theoretically offer this, but I was not able to obtain one.  This was recommended by the by the modem manufacturer, Botletics.

### Waveshare E-Paper Display
![image](file:///Users/mkorostoff/Arduino/documentation/img/XXpPBYs.png)

This is a simple, low cost display similar to an Amazon Kindle.  The major advantage of this technology is that continues to display with literally zero electricity, only requiring power when updating the display.  This model conveniently ships with ready-made Arduino libraries.

### Just A Battery
![image](file:///Users/mkorostoff/Arduino/documentation/img/JglD39x.png)

Tim from Botletics tells me that this regular, run of the mill battery could power his board for about 3 years without recharging, though of course the modem is not the only component this battery needs to power.  For development, I am powering the device via USB, but eventually I will migrate to battery power.

# The Build

Literally every aspect of this build was new to me.  I had essentially no relevant experience with any of the underlying technologies before beginning.  I had never designed a physical circuit before, never programmed a serial interface, never authored ANY code in C/C++, never soldered a wire, and never dealt with a micro-controller of any kind.  There was a lot of learning, and a lot of mistakes.

![image](file:///Users/mkorostoff/Arduino/documentation/img/6ZhMcEQ.jpg)

The first circuit I assembled just detected one button push and printed on screen "button pushed," which you can vaguely make out in this picture.  You may also notice here on the far right of the breadboard a red/black connection that connects essentially nothing.  This is something I did because I was rote-copying a wire diagram that contained this needless connection.  You will see this unnecessary connection in every subsequent photo.

![image](file:///Users/mkorostoff/Arduino/documentation/img/ODHr4h9.jpg)

Close up of the first connection.

![image](file:///Users/mkorostoff/Arduino/documentation/img/lHd85V1.jpg)

After getting one button wired up, I was able to get the remaining buttons wired up pretty easily by analogy with the first.

![image](file:///Users/mkorostoff/Arduino/documentation/img/clicks.gif)

I wrote a simple node application to act as the back end and receive button clicks.  Here you see it printing my button pushes to console.

![image](file:///Users/mkorostoff/Arduino/documentation/img/JQCKjm6.jpg)

Network shield in place!  This photo is pretty much just for show, because when it was taken I was still waiting for my soldering iron and my SIM card.  The actual modem is the white square in the center of the board.  The surrounding blue circuit board is just for interfacing with Arduino.  As you can see, this board is designed as a "shield" which is to say it plugs into every arduino pin, while also supplying a female pin to allow simultaneous pin access for other devices.

![image](file:///Users/mkorostoff/Arduino/documentation/img/ILprBPD.jpg)

Fully assembled!  Note, the epaper is not actually booted up here, because I had it wired wrong.

![image](file:///Users/mkorostoff/Arduino/documentation/img/EVdIKyM.jpg)

This was a huge win, that took the better part of a day to achieve.  This the demo arduino application put out by waveshare (the epaper manufacturer).  The epaper display literally just had 8 bare wires sticking out of it with no documentation about how to connect them, along with esoteric, meaningless labels (RST, CLK, DIN...).

I figured out pretty quickly which wires were the power input and ground based on color coding.  Four other connections I was able to work out by browsing the example source code provided by the manufacturer.  The last two I eventually figured out from some one off forum post.

Seeing this screen finally boot up was a huge relief!

![image](file:///Users/mkorostoff/Arduino/documentation/img/uae608g.jpg)

Another huge win: finally being able to write some custom content to the screen.  This was a long struggle mostly because the device has (I think) a bunch of undocumented memory limits where only about 20% of the pixels can be addressed in a single API call.  So if you want to fill up the whole screen, you need to make 5 separate API calls.  There's also no error messaging, so I spent HOURS making seemingly valid calls which failed silently for no apparent reason.

![image](file:///Users/mkorostoff/Arduino/documentation/img/3ExsKOg.jpg)

The display FINALLY showing data in the format I intended.

![image](file:///Users/mkorostoff/Arduino/documentation/img/update.gif)

I added a reset button which will fetch configuration from the server and update the button labels.  Here you can see it in action.

# The Design

### Diagram
![image](file:///Users/mkorostoff/Arduino/documentation/img/schematic_bb.png)

For the initial build I decided to focus on the physical switches, the epaper display, and learning the Arduino firmware programming ecosystem.  I decided to simulate network traffic over a physical serial connection using [Node SerialPort](https://www.npmjs.com/package/serialport).

The main reason that I decided to do simulated networking rather than connect to a real-life CAT-M1 in build phase 1 is that my CAT-M1 modem requires sodering in order to work, which I have never done before.  While I waited for my new sodering iron to arrive in the mail (it arrived two days ago) I did not want to delay the rest of the project.  Also, I had plenty of new stuff to learn without worrying about networking just yet.  Real-life CAT-M1 networking will be the first feature implemented in build phase 2.

The circuitry here is rather simple.  As you can see, the breadboard on the right hand side features 5 buttons.  Because the buttons are meant to be programmable by consumers, I gave them the arbitrary names A, B, C, and D (left to right) and then a special fifth reset button on the far right.  I also programmed in a special "clear screen" feature when buttons C & D are pushed simultaneously, mostly as a developer convenience.

The basic idea behind the button wiring is that the top row of wires each always feed _some_ signal to an input pin.  When the button is pushed, the input pin is connected to a 5V supply.  When the button is unpushed, the input pin is connected directly to ground, through a 10kΩ resistor.  You can see this more clearly if we isolate the circuitry for a single button:

### Button
![image](file:///Users/mkorostoff/Arduino/documentation/img/button.png)

### Pressed
![image](file:///Users/mkorostoff/Arduino/documentation/img/pressed.png)

### Unpressed
![image](file:///Users/mkorostoff/Arduino/documentation/img/unpressed.png)

So, depending on whether the button is pressed or unpressed, we can read either 5V or \~0V on the input pin.  Then we simply program the firmware to take action when a 5V input is detected.  Note, this is not some special, unique circuit design, it is merely how all buttons work in Arduino land, and (usually) how physical buttons on electronics work in general.

The epaper display connects to Arduino over serial, and calls for a 3.3V input.  Arduino thankfully supplies both 5V and 3.3V power output pins, so I was able to dedicate one pin to the physical buttons, and another to the epaper display.  Data is exchanged between the Arduino and the epaper over serial using an esoteric set of API commands that require you to address individual pixels.  The manufacturer _mercifully_ supplies an Arduino C++ library which abstracts the process of pixel addressing substantially.

### Schematic
![image](file:///Users/mkorostoff/Arduino/documentation/img/llkntUk.png)

When the unit is powered on, it sends a bootup signal to the server (literally just the numeral "1").  The server responds with a pipe-separated configuration string, e.g. `These|Are|Your|Labels`.  My firmware processes this string, and converts it into the appropriate serial commands, which are then transmitted to the epaper display.

![image](file:///Users/mkorostoff/Arduino/documentation/img/bootup.jpg)

<sup>The bootup sequence</sup>

If the reset button is pushed, essentially the same sequence fires.  If button A/B/C/D is pushed, this is transmitted to the server (literally as "A", "B", etc) and there is no interaction with the epaper display.  If buttons C and D are pushed simultaneously, the appropriate serial commands are sent to epaper to clear the screen.

# The Software
You can checkout all the source files here https://github.com/reaktor/eclicker.  Here's the main Arduino firmware though.

```c
/**
 * Todo:
 * - Subroutine dividerSetup()
 * - Turn button listening into a loop
 * - Resize text labels based on length
 * - Implement word wrapping
 */
#include <SPI.h>
#include <epd2in9.h>
#include <epdpaint.h>
#include "imagedata.h"

#define COLORED     0
#define UNCOLORED   1
#define IF_INVERT_COLOR     0

String incoming = "";
String newLabels[4];
int labelIteration = 0;
int offSet = 0;
unsigned char image[1024];
Paint paint(image, 0, 0); // width should be the multiple of 8
Epd epd;
unsigned long time_start_ms;
unsigned long time_now_s;

struct buttons {
  unsigned int a:1;
  unsigned int b:1;
  unsigned int c:1;
  unsigned int d:1;
  unsigned int e:1;//reset button
};

struct buttons prev;
struct buttons current;

void setup() {
  Serial.begin(9600);
  buttonSetup();
  if (epd.Init(lut_full_update) != 0) {
    return;
  }
  greet();
  Serial.print("1");
}

void loop() {
  buttonLoop();
  //todo: handle invalid inputs
  while(Serial.available() > 0) {
    if (labelIteration == 0) {
      clearDisplay();
    }
    newLabels[labelIteration] = Serial.readStringUntil('|');
    labelIteration++;
  }
  if (labelIteration >= 4) {
    labelSetup(newLabels[0].c_str(), newLabels[1].c_str(), newLabels[2].c_str(), newLabels[3].c_str());
    epd.DisplayFrame();
    labelIteration = 0;
  }
}

void buttonSetup() {
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(12, INPUT);//reset button
  pinMode(LED_BUILTIN, OUTPUT);
}

void buttonLoop() {
  current.a = digitalRead(2);
  current.b = digitalRead(3);
  current.c = digitalRead(5);
  current.d = digitalRead(6);
  current.e = digitalRead(12);

  if (current.a != prev.a) {
    if (current.a == HIGH) {
      Serial.print("a");
      delay(50);
    }
    prev.a = current.a;
  }

  if (current.b != prev.b) {
    if (current.b == HIGH) {
      Serial.print("b");
      delay(50);
    }
    prev.b = current.b;
  }

  if (current.c != prev.c) {
    if (current.c == HIGH) {
      Serial.print("c");
      delay(50);
    }
    prev.c = current.c;
  }

  if (current.d != prev.d) {
    if (current.d == HIGH) {
      if (current.c == HIGH) {
        clearDisplay();
      }
      Serial.print("d");
      delay(50);
    }
    prev.d = current.d;
  }

  //The reset button
  if (current.e != prev.e) {
    if (current.e == HIGH) {
      Serial.print("2");
      delay(50);
    }
    prev.e = current.e;
  }
}

void say(const char* s, int yPosition) {
  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 27, s, &Font20, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 0, yPosition, paint.GetWidth(), paint.GetHeight());
}

void greet() {
  clearDisplay();
  paint.SetWidth(128);
  paint.SetHeight(64);
  paint.SetRotate(ROTATE_0);
  say("Welcome!", 112);
  epd.DisplayFrame();
}

void labelSetup(const char* a, const char* b, const char* c, const char* d) {
  paint.SetWidth(128);
  paint.SetHeight(64);
  paint.SetRotate(ROTATE_0);

  say(a, 0);
  say(b, 74);
  say(c, 148);
  say(d, 222);
  dividerSetup();
}

//Todo: subroutine this
void dividerSetup() {
  paint.SetWidth(128);
  paint.SetHeight(2);

  paint.Clear(UNCOLORED);
  paint.DrawLine(0, 0, 300, 1, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 0, 74, paint.GetWidth(), paint.GetHeight());

  paint.Clear(UNCOLORED);
  paint.DrawLine(0, 0, 300, 1, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 0, 148, paint.GetWidth(), paint.GetHeight());

  paint.Clear(UNCOLORED);
  paint.DrawLine(0, 0, 300, 1, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 0, 222, paint.GetWidth(), paint.GetHeight());
}

void clearDisplay() {
  epd.ClearFrameMemory(0xFF);
  epd.DisplayFrame();
  epd.ClearFrameMemory(0xFF);
  epd.DisplayFrame();
}
```

# Proof of Concept Application
I wanted to build out one of the "apps" I contemplated in my previous post.  This is an application one might build for pizza delivery.  Each delivery driver would be issued a clicker, to report stats back to home base.

![image](file:///Users/mkorostoff/Arduino/documentation/img/pizza.jpg)

This is used to send alerts to customers when their orders arrive, and also by the pizza dispatcher to create a display like this:

![image](file:///Users/mkorostoff/Arduino/documentation/img/pizza.gif)

# Build Phase 2

One word: soldering!

![image](file:///Users/mkorostoff/Arduino/documentation/img/soldering.jpg)

The first and most important feature for build phase 2 is to make CAT-M1 connectivity actually, really work, not just as a simulation.  For this, I'll need to solder some headers onto the modem shown above.  Next, I'll convert the breadboard circuitry (the white thing with all the wires sticking out) into a permanent circuit with soldered perf-board.  Finally, I'll convert the whole thing to battery powered, and throw it in a (3D printed?) plastic enclosure, finally giving me a mobile, pocket sized IoT clicker.

In the end, it should be about this size, plus an enclosure and battery:

![image](file:///Users/mkorostoff/Arduino/documentation/img/size.jpg)

# Build Phase 3?

I sincerely doubt there will be a build phase 3 at all, but if that ever happens, I will eliminate arduino entirely and integrate all the components into a single, professionally printed circuit board.  For this phase, I'll burn the firmware into a standalone processor

![image](file:///Users/mkorostoff/Arduino/documentation/img/future.jpg)

<sup>Just some photo I pulled off of google images that kind of looks the way my thing should look.</sup>

There's no planned build phase 4, but I suppose the logical next step if phase 3 were completed successfully would be to manufacture these devices in a factory and start selling them.

