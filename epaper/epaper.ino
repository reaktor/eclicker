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
  unsigned int e:1;//reset button
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

  clearDisplay();
  labelSetup("Option A", "Option B", "Option C", "Option D");
  epd.DisplayFrame();
}

void loop() {
  buttonLoop();
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
      delay(50);
    }
    prev.a = current.a;
  }

  if (current.b != prev.b) {
    if (current.b == HIGH) {
      // say("b");
      delay(50);
    }
    prev.b = current.b;
  }

  if (current.c != prev.c) {
    if (current.c == HIGH) {
      // say("c");
      delay(50);
    }
    prev.c = current.c;
  }

  if (current.d != prev.d) {
    if (current.d == HIGH) {
      // say("d");
      delay(50);
    }
    prev.d = current.d;
  }

  //The reset button
  if (current.e != prev.e) {
    if (current.e == HIGH) {
      // Serial.print("matt");
      clearDisplay();
      labelSetup("Option Z", "Option B", "Option C", "Option D");
      epd.DisplayFrame();
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