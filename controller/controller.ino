#define BLUE_LOWER 11
#define RED_LOWER 10
#define GREEN_LOWER 9

#define BLUE_UPPER 6
#define RED_UPPER 5
#define GREEN_UPPER 3

#define BUTTONPIN 2

struct lightControl {
  private:
    /* Lower RGB Pins */
    int pins_low[3] = {RED_LOWER, GREEN_LOWER, BLUE_LOWER};

    /* Upper RGB Pins */
    int pins_upp[3] = {RED_UPPER, GREEN_UPPER, BLUE_UPPER};;

    /* Lower and Upper Brightness */
    float bn_low = 1.0;
    float bn_upp = 1.0;

  public:

  lightControl(void) { }

  /* Initializes each PWM RGB pin to an output. 
   *  Requires: Must call in setup. */
  void init() {
    for (int i = 0; i < sizeof(pins_low) ; i++ ) {
      pinMode(pins_low[i], OUTPUT);
      pinMode(pins_upp[i], OUTPUT);
    }
  }

  /* Takes in Serial input and subsequently changes the lights. 
   *  Requires: String input of the form
   *            "bn_low,r_low,g_low,b_low,bn_upp,r_upp,g_upp,b_upp,". */
  void submit_input(String inp) {
    int color_lower[3] = {};
    int color_upper[3] = {};
    parse_input(inp, color_lower, color_upper);

    write_color(color_lower, color_upper);
  
  }

  /* Converts serial input to [r_low, g_low, b_low], [r_upp, g_upp, b_upp] lists and stores them in c_low, c_upp.
   *  Also stores brightnesses in bn_low and bn_upp. 
   *  Requires: Brightness must be an integer between 0 and 255.
   *  Example: "50,0,0,255,100,255,0,0," is [50, 0, 0, 255, 100, 255, 0, 0,". RGB code (0, 0, 255) at 50% brightness. */
  void parse_input(String inp, int c_low[3], int c_upp[3]) {
    int c = 0; String acc;
    for (int i = 0; i < inp.length(); i++ ) {
      char temp = inp[i];
      if (temp == ',') {
        
        if (c == 0) bn_low = acc.toFloat();
        else if (c < 4) c_low[c - 1] = acc.toFloat() * 255;
        else if (c == 4) bn_upp = acc.toFloat(); 
        else c_upp[c - 5] = acc.toFloat() * 255;
        c++ ; acc = "";
      } else acc += temp;
    }
  }

  /* Writes [r_low, g_low, b_low] and [r_upp, g_upp, b_upp] to the LED strip 
   *  with brightnesses bn_low and bn_upp. */
  void write_color(int c_low[3], int c_upp[3]) {
    for (int i = 0; i < 3; i++ ) {

      analogWrite(pins_low[i], c_low[i] * bn_low);
      analogWrite(pins_upp[i], c_upp[i] * bn_upp);
    }
  }
 
};



/* Light Control Object */
struct lightControl lc = lightControl();

void setup() {
  Serial.begin(9600);
  lc.init()
}


void loop() {
  while ( Serial.available() ) lc.submit_input(Serial.readString());
  
}











//      Serial.println(String(pins_low[i]) + " " + String(c_low[i]) + " " + String(bn_low) + " " + String(i));
//      Serial.println(String(pins_upp[i]) + " " + String(c_upp[i]) + " " + String(bn_upp) + " " + String(i));


//  pinMode(BUTTONPIN, INPUT);
//int color0[2][3] = {{255, 0, 0}, {0, 0, 255}};
//int color1[2][3] = {{0, 255, 0}, {255, 0, 0}};
//int color2[2][3] = {{0, 0, 255}, {0, 255, 0}};
//int colors[3] = {color0, color1, color2};
//int current_color = 0;
//int c_low[3], c_upp[3];
//
//int light_on = 0;
//int btn_state = 0;
//int btn_ready = 1;

//  btn_state = digitalRead(BUTTONPIN);
//
//  if ( btn_ready && btn_state ) {
//    switch (current_color) {
//      case 0:
//        c_low = color0[0]; c_upp = color0[1];
//        break;
//      default:
//        break;
//    }
//    int c_low[3] = colors[current_color][0];
//    int color_set[] = colors[current_color];
//    lc.write_color(color_set[0], color_set[1]);
//    current_color = (current_color + 1) % 3;
//    btn_ready = LOW;
//
//  } else if ( !btn_state ) { 
//    btn_ready = HIGH;
//  }
//  
