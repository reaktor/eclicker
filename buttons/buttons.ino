struct buttons {
    unsigned int a:1;
    unsigned int b:1;
    unsigned int c:1;
    unsigned int d:1;
};

struct buttons prev;
struct buttons current;

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  //todo, break this into a shared function
  current.a = digitalRead(2);
  if (current.a != prev.a) {
    if (current.a == HIGH) {
      Serial.println("a");
      delay(50);
    }
    prev.a = current.a;
  }

  current.b = digitalRead(3);
  if (current.b != prev.b) {
    if (current.b == HIGH) {
      Serial.println("b");
      delay(50);
    }
    prev.b = current.b;
  }

  current.c = digitalRead(5);
  if (current.c != prev.c) {
    if (current.c == HIGH) {
      Serial.println("c");
      delay(50);
    }
    prev.c = current.c;
  }

  current.d = digitalRead(6);
  if (current.d != prev.d) {
    if (current.d == HIGH) {
      Serial.println("d");
      delay(50);
    }
    prev.d = current.d;
  }
}
