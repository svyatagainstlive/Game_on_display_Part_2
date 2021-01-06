#if 1

#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;
#include <TouchScreen.h>
#define MINPRESSURE 200
#define MAXPRESSURE 1000

// ALL Touch panels and wiring is DIFFERENT
// copy-paste results from TouchScreen_Calibr_native.ino
const int XP = 6, XM = A2, YP = A1, YM = 7; //ID=0x9341
const int TS_LEFT = 907, TS_RT = 136, TS_TOP = 942, TS_BOT = 139;

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

Adafruit_GFX_Button on_btn, off_btn, staz, istreb_uron, resets;

int pixel_x, pixel_y;     //Touch_getXY() updates global vars
bool Touch_getXY(void)
{
  TSPoint p = ts.getPoint();
  pinMode(YP, OUTPUT);      //restore shared pins
  pinMode(XM, OUTPUT);
  digitalWrite(YP, HIGH);   //because TFT control pins
  digitalWrite(XM, HIGH);
  bool pressed = (p.z > MINPRESSURE && p.z < MAXPRESSURE);
  if (pressed) {
    pixel_x = map(p.x, TS_LEFT, TS_RT, 0, tft.width()); //.kbv makes sense to me
    pixel_y = map(p.y, TS_TOP, TS_BOT, 0, tft.height());
  }
  return pressed;
}

#define BLACK 0x0000
#define NAVY 0x000F
#define DARKGREEN 0x03E0
#define DARKCYAN 0x03EF
#define MAROON 0x7800
#define PURPLE 0x780F
#define OLIVE 0x7BE0
#define LIGHTGREY 0xC618
#define DARKGREY 0x7BEF
#define BLUE 0x001F
#define GREEN 0x07E0
#define CYAN 0x07FF
#define RED 0xF800
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF
#define ORANGE 0xFD20
#define GREENYELLOW 0xAFE5
#define PINK 0xF81F
int x = 0;
int steps_2 = 0;
int steps_1 = 0;
int xp = 0;
int hod_1 = 0;
int step_heart_1 = 0;
int istreb_ur = 0;
int super_ur_2 = 0;
int stepu = 0;

void setup(void)
{
  Serial.begin(9600);
  uint16_t ID = tft.readID();
  Serial.print("TFT ID = 0x");
  Serial.println(ID, HEX);
  Serial.println("Calibrate for your Touch Panel");
  if (ID == 0xD3D3) ID = 0x9486; // write-only shield
  tft.begin(ID);
  tft.setRotation(0);            //PORTRAIT
  tft.fillScreen(BLACK);
  on_btn.initButton(&tft,  280, 35, 70, 70, WHITE, RED, BLACK, "Game", 2);
  off_btn.initButton(&tft, 100, 355, 70, 70, WHITE, BLUE, BLACK, "Osn", 2);
  staz.initButton(&tft, 175, 355, 70, 70, WHITE, DARKGREEN, BLACK, "Staz", 2);
  istreb_uron.initButton(&tft, 260, 355, 70, 70, WHITE, PURPLE, BLACK, "Istreb", 2);
  resets.initButton(&tft, 280, 435, 70, 70, WHITE, CYAN, BLACK, "Reset", 2);
  on_btn.drawButton(false);
  off_btn.drawButton(false);
  staz.drawButton(false);
  istreb_uron.drawButton(false);
  resets.drawButton(false);
}

//////////////////////////////////////
int myheart_1 = random(4000, 4500);///
int myheart_2 = random(4000, 4500);///
int arheart_1 = random(7000, 8000);//
int arheart_2 = random(7000, 8000);//
//////////////////////////////////////

void loop(void)
{
  clicking();
}

void clicking(void) {
  bool down = Touch_getXY();
  on_btn.press(down && on_btn.contains(pixel_x, pixel_y));
  off_btn.press(down && off_btn.contains(pixel_x, pixel_y));
  staz.press(down && staz.contains(pixel_x, pixel_y));
  istreb_uron.press(down && istreb_uron.contains(pixel_x, pixel_y));
  resets.press(down && resets.contains(pixel_x, pixel_y));
  MyHeroy1();
  MyHeroy2();
  if (on_btn.justPressed()) {
    resets.drawButton();
    on_btn.drawButton();
    staz.drawButton();
    istreb_uron.drawButton();
    background_game();
    off_btn.drawButton(false);
    artifHeroy();
    artifHeroy2();
  }
  if (arheart_2 <= 0) {
    winner();
  }
  if (myheart_1 <= 0) {
    defeat();
  }
}
void background_game(void) {
  tft.fillScreen(BLACK);
  for (x = 0; x <= 180; x++) {
    int xRnd = random(0, 480);
    int yRnd = random(0, 320);
    tft.drawPixel(yRnd, xRnd, WHITE);
  }
}

void MyHeroy1(void) {
  int gray = tft.color565(192, 192, 192);
  tft.fillRoundRect(30, 200, 80, 30, 2, gray);
  tft.setCursor(20, 183);
  tft.setTextColor(GREEN);
  tft.setTextSize(2);
  tft.print(myheart_1);
  if (off_btn.justReleased()) {
    off_btn.drawButton();
  }
  if (off_btn.justPressed()) {
    off_btn.drawButton();
    int xi = random(100, 450);
    Serial.println(xi);
    hod_1 = hod_1 + 1;
    step_heart_1 = step_heart_1 + 1;
    istreb_ur = istreb_ur + 1;
    steps_1 = steps_1 + 1;
    arheart_1 = arheart_1 - xi;
    arheart_2 = arheart_2 - xi;
    tft.setCursor(230, 20);
    tft.setTextColor(ORANGE);
    tft.setTextSize(4);
    tft.print(xi);
    delay(150);
    my_heroy_animation();
  }
  if (staz.justReleased()) {
    staz.drawButton();
  }
  if (staz.justPressed() and steps_1 >= 3) {
    steps_1 = steps_1 - 3;
    int stazist = random(200, 300);
    staz.drawButton(false);
    arheart_2 = arheart_2 - stazist;
    arheart_1 = arheart_1 - stazist;
    tft.setCursor(230, 20);
    tft.setTextColor(ORANGE);
    tft.setTextSize(4);
    tft.print(stazist);
    my_heroy_animation();
    background_game();
    artifHeroy();
    artifHeroy2();
    off_btn.drawButton();
    staz.drawButton();
    istreb_uron.drawButton();
  }
  if (istreb_uron.justReleased()) {
    istreb_uron.drawButton();
  }
  if (istreb_uron.justPressed() and istreb_ur >= 8) {
    istreb_ur = istreb_ur - 8;
    int istr = random(700, 1000);
    staz.drawButton(false);
    arheart_2 = arheart_1 - istr;
    arheart_1 = arheart_2 - istr;
    tft.setCursor(230, 20);
    tft.setTextColor(RED);
    tft.setTextSize(4);
    tft.print(istr);
    delay(500);
    background_game();
    tft.fillRoundRect(40, 160, 80, 30, 2, gray);
    delay(1000);
    background_game();
    artifHeroy();
    artifHeroy2();
    off_btn.drawButton();
    staz.drawButton();
    istreb_uron.drawButton();
  }
  if (steps_1 >= 3) {
    tft.setTextColor(GREEN);
    tft.setCursor(440, 420);
    tft.setTextSize(2);
    tft.print("Super Damage: 100%");
  }
  if (istreb_ur >= 8) {
    tft.setTextColor(GREEN);
    tft.setCursor(440, 440);
    tft.setTextSize(2);
    tft.print("Fighter Damage: 100%");
  }
}

void MyHeroy2(void) {
  int gray = tft.color565(192, 192, 192);
  tft.fillRoundRect(30, 140, 80, 30, 2, gray);
  tft.setCursor(20, 123);
  tft.setTextColor(GREEN);
  tft.setTextSize(2);
  tft.print(myheart_2);
  if (off_btn.justReleased()) {
    off_btn.drawButton();
  }
  if (off_btn.justPressed()) {
    off_btn.drawButton();
    int xi = random(100, 450);
    Serial.println(xi);
    arheart_1 = arheart_1 - xi;
    arheart_2 = arheart_2 - xi;
    tft.setCursor(230, 20);
    tft.setTextColor(ORANGE);
    tft.setTextSize(4);
    tft.print(xi);
    delay(150);
    my_heroy_animation();
  }
  if (staz.justReleased()) {
    staz.drawButton();
  }
  if (staz.justPressed() and steps_1 >= 3) {
    steps_1 = steps_1 - 3;
    int stazist = random(200, 300);
    staz.drawButton(false);
    arheart_2 = arheart_2 - stazist;
    arheart_1 = arheart_1 - stazist;
    tft.setCursor(230, 20);
    tft.setTextColor(ORANGE);
    tft.setTextSize(4);
    tft.print(stazist);
    my_heroy_animation();
    background_game();
    artifHeroy();
    artifHeroy2();
    off_btn.drawButton();
    staz.drawButton();
    istreb_uron.drawButton();
  }
  if (istreb_uron.justReleased()) {
    istreb_uron.drawButton();
  }
  if (istreb_uron.justPressed() and istreb_ur >= 8) {
    istreb_ur = istreb_ur - 8;
    int istr = random(700, 1000);
    staz.drawButton(false);
    arheart_2 = arheart_1 - istr;
    arheart_1 = arheart_2 - istr;
    tft.setCursor(230, 20);
    tft.setTextColor(RED);
    tft.setTextSize(4);
    tft.print(istr);
    delay(500);
    background_game();
    tft.fillRoundRect(40, 160, 80, 30, 2, gray);
    delay(1000);
    background_game();
    artifHeroy();
    artifHeroy2();
    off_btn.drawButton();
    staz.drawButton();
    istreb_uron.drawButton();
  }
  if (steps_1 >= 3) {
    tft.setTextColor(GREEN);
    tft.setCursor(440, 420);
    tft.setTextSize(2);
    tft.print("Super Damage: 100%");
  }
  if (istreb_ur >= 8) {
    tft.setTextColor(GREEN);
    tft.setCursor(440, 440);
    tft.setTextSize(2);
    tft.print("Fighter Damage: 100%");
  }
}

void artifHeroy(void) {
  tft.fillRoundRect(200, 150, 80, 30, 2, OLIVE);
  tft.fillRoundRect(200, 150, 50, 40, 2, OLIVE);
  tft.setCursor(223, 155);
  tft.setTextColor(GREEN);
  tft.setTextSize(2);
  tft.print(arheart_1);
  if (hod_1 >= 1) {
    hod_1 = hod_1 - 1;
    stepu = stepu + 1;
    int ix = random(300, 550);
    myheart_1 = myheart_1 - ix;
    myheart_2 = myheart_2 - ix;
    tft.setCursor(20, 20);
    tft.setTextColor(ORANGE);
    tft.setTextSize(4);
    tft.print(ix);
    delay(500);
    artif_heroy_animation();
  }
  if (stepu >= 2) {
    stepu = stepu - 2;
    int py = random(200, 400);
    arheart_2 = arheart_2 + py;
  }
  if (arheart_1 <= 0) {
    tft.fillRoundRect(200, 150, 80, 30, 2, BLACK);
    tft.fillRoundRect(200, 150, 50, 40, 2, BLACK);
  }
}

void artifHeroy2(void) {
  tft.fillRoundRect(200, 220, 80, 30, 2, OLIVE);
  tft.fillRoundRect(200, 220, 50, 40, 2, OLIVE);
  tft.setCursor(200, 225);
  tft.setTextColor(GREEN);
  tft.setTextSize(2);
  tft.print(arheart_2);
  if (hod_1 >= 1) {
    hod_1 = hod_1 - 1;
    stepu = stepu + 1;
    int ix = random(300, 550);
    myheart_1 = myheart_1 - ix;
    myheart_2 = myheart_2 - ix;
    tft.setCursor(20, 20);
    tft.setTextColor(ORANGE);
    tft.setTextSize(4);
    tft.print(ix);
    delay(500);
  }
  if (stepu >= 2) {
    stepu = stepu - 2;
    int py = random(200, 500);
    arheart_2 = arheart_2 + py;
  }
  if (arheart_2 <= 0) {
    tft.fillRoundRect(200, 220, 80, 30, 2, BLACK);
    tft.fillRoundRect(200, 220, 50, 40, 2, BLACK);
  }
}

void winner(void) {
  tft.fillScreen(BLACK);
  tft.setCursor(50, 240);
  tft.setTextSize(5);
  tft.setTextColor(CYAN);
  tft.println("You Win!");
  delay(1000000);
}
void defeat(void) {
  tft.fillScreen(BLACK);
  tft.setCursor(45, 240);
  tft.setTextSize(5);
  tft.setTextColor(RED);
  tft.println("You lose!");
  delay(100000);
}
void my_heroy_animation(void) {
  int gray = tft.color565(192, 192, 192);
  int u = 0;
  int t = 0;
  delay(200);
  tft.fillRoundRect(10, 200, 80, 30, 2, gray);
  for (t = 120; t <= 180; t++) {
    for (u = 210; u <= 215; u++) {
      tft.drawFastHLine(t, u, 20, RED);
    }
    delay(5);
    for (u = 210; u <= 215; u++) {
      tft.drawFastHLine(t, u, 20, BLACK);
    }
  }
  artifHeroy();
  off_btn.drawButton();
  staz.drawButton();
  istreb_uron.drawButton();
}
void artif_heroy_animation(void) {
  int u = 0;
  int y = 0;
  for (y = 170; y >= 110; y--) {
    for (u = 210; u <= 215; u++) {
      tft.drawFastHLine(y, u, 20, RED);
    }
    delay(5);
    for (u = 210; u <= 215; u++) {
      tft.drawFastHLine(y, u, 20, BLACK);
    }
  }
  background_game();
  if (arheart_1 > 0) {
    artifHeroy();
  }
  artifHeroy2();
  off_btn.drawButton();
  staz.drawButton();
  istreb_uron.drawButton();
}
#endif
