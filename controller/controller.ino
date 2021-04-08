#define BLUEPIN 6
#define REDPIN 5
#define GREENPIN 3
int pins[] = {REDPIN, GREENPIN, BLUEPIN};

/* Pass in list [r, g, b]. */
void write_color(int colors[3]) {
  for (int i = 0; i < 3; i++ ) {
    analogWrite(pins[i], colors[i]);
  }
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for (int i = 0; i < 3; i++ ) {
    pinMode(pins[i], OUTPUT);
  }
}

// 255, 40, 0
// 255, 242, 0
int color1[3] = {255, 40, 0};
int color2[3] = {255, 242, 0};

void loop() {
  // put your main code here, to run repeatedly:
  
//  analogWrite(3, 255);
  write_color(color1);
  delay(500);
//  analogWrite(3, 0);
  write_color(color2);
  delay(500);
}
