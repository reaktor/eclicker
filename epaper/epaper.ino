#include <SPI.h>
#include <epd2in9.h>
#include <epdpaint.h>
#include "imagedata.h"

#define COLORED     0
#define UNCOLORED   1
#define IF_INVERT_COLOR     0

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
};

struct buttons prev;
struct buttons current;

void setup() {
  Serial.begin(9600);
  buttonSetup();
  if (epd.Init(lut_full_update) != 0) {
    Serial.print("e-Paper init failed");
    return;
  }
  epd.ClearFrameMemory(0xFF);
  epd.DisplayFrame();
  epd.ClearFrameMemory(0xFF);
  epd.DisplayFrame();

  paint.SetWidth(128);
  paint.SetHeight(64);
  paint.SetRotate(ROTATE_0);

  labelSetup("AA", "BB", "CC", "DX");
}

void loop() {
  buttonLoop();
}

void buttonSetup() {
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void buttonLoop() {
  current.a = digitalRead(2);
  current.b = digitalRead(3);
  current.c = digitalRead(5);
  current.d = digitalRead(6);

  if (current.a != prev.a) {
    if (current.a == HIGH) {
      say("a");
      delay(50);
    }
    prev.a = current.a;
  }

  if (current.b != prev.b) {
    if (current.b == HIGH) {
      say("b");
      delay(50);
    }
    prev.b = current.b;
  }

  if (current.c != prev.c) {
    if (current.c == HIGH) {
      say("c");
      delay(50);
    }
    prev.c = current.c;
  }

  if (current.d != prev.d) {
    if (current.d == HIGH) {
      say("d");
      delay(50);
    }
    prev.d = current.d;
  }
}

void say(const char* s) {
  paint.Clear(COLORED);
  paint.DrawStringAt(0, 0, s, &Font24, UNCOLORED);
  epd.SetFrameMemory(paint.GetImage(), 0, 0, paint.GetWidth(), paint.GetHeight());
  epd.DisplayFrame();
}

void labelSetup(const char* a, const char* b, const char* c, const char* d) {
  paint.Clear(COLORED);
  paint.DrawStringAt(0, 0, a, &Font24, UNCOLORED);
  paint.DrawStringAt(0, 40, b, &Font24, UNCOLORED);
  paint.DrawStringAt(0, 80, c, &Font24, UNCOLORED);
  paint.DrawStringAt(0, 120, d, &Font24, UNCOLORED);
  epd.SetFrameMemory(paint.GetImage(), 0, 0, paint.GetWidth(), paint.GetHeight());
  epd.DisplayFrame();
}
