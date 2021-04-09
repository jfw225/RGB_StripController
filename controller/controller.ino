#define BLUEPIN 6
#define REDPIN 5
#define GREENPIN 3
int pins[] = {REDPIN, GREENPIN, BLUEPIN};

/* Sets each color pin to OUTPUT. */
void init_pins() {
  for (int i = 0; i < 3; i++ ) pinMode(pins[i], OUTPUT);
}

/* Converts serial input to an [r, g, b] list. */
void parse_input(String inp, int rgb[3]) {
  int c = 0;
  String acc;
  for (int i = 0; i < inp.length(); i++ ) {
    char temp = inp[i];
    if (temp == ',') {
      rgb[c] = acc.toInt();
      Serial.println(acc);
      c++ ;
      acc = "";
    } else acc += temp;
  }
}

/* Pass in list [r, g, b]. */
void write_color(int colors[3]) {
  for (int i = 0; i < 3; i++ ) {
    analogWrite(pins[i], colors[i]);
  }
}

void setup() {
  Serial.begin(9600);
  init_pins();
}

// 255, 40, 0
// 255, 242, 0
int color1[3] = {255, 40, 0};
int color2[3] = {255, 242, 0};

void loop() {
  while ( Serial.available() ) {
    int rgb[3] = {};
    parse_input(Serial.readString(), rgb);
    write_color(rgb);
  } 
  
}
