/*
  TODO : benchmark if fillRect or drawBitmp() would be faster to clear canvas
*/

#include <Adafruit_GFX.h>     // Core graphics library
#include <Adafruit_ST7735.h>  // Hardware-specific library for ST7735
#include <SPI.h>

#define TFT_CS D1   // PyBadge/PyGamer display control pins: chip select.
#define TFT_RST D0  // Display reset.
#define TFT_DC D2   // Display data/command select.

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);



/*------------------------------
||      GLOBAL  SPRITES       ||
-------------------------------*/



const uint8_t dino_rest[] = { 0x0, 0x0, 0x0, 0x0, 0xF, 0xF0, 0x0, 0x1B, 0xF8, 0x0, 0x1F, 0xF8, 0x0, 0x1F, 0xF8, 0x0, 0x1F, 0xF8, 0x0, 0x1F, 0x0, 0x0, 0x1F, 0xE0, 0x40, 0x3E, 0x0, 0x40, 0xFE, 0x0, 0x61, 0xFF, 0x80, 0x73, 0xFE, 0x80, 0x7F, 0xFE, 0x0, 0x7F, 0xFE, 0x0, 0x3F, 0xFC, 0x0, 0xF, 0xF8, 0x0, 0x7, 0xF0, 0x0, 0x3, 0xB0, 0x0, 0x3, 0x10, 0x0, 0x2, 0x10, 0x0, 0x3, 0x18, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0 };                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   // w=22  h=23
const uint8_t track0[] = { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0x0, 0x0, 0x0, 0x8, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8, 0x0, 0x0, 0x0, 0x0, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x18, 0x0, 0x0, 0x0, 0x0, 0x0, 0x10, 0x0, 0x0, 0x0, 0x0, 0x10, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0x4, 0x0, 0x10, 0x0, 0x0, 0x0, 0x40, 0x20, 0x0, 0x0, 0x20, 0x0, 0x0, 0xC1, 0x0, 0x0, 0xC0, 0x10, 0x6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x0, 0x4, 0x4, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0 };        // w=300  h=6
const uint8_t track1[] = { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1C, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1E, 0x1, 0xE0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x63, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x21, 0x6, 0x10, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0xFF, 0x87, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0xF8, 0xF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0x0, 0x0, 0x0, 0x8, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8, 0x78, 0x0, 0x0, 0x0, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x18, 0x0, 0x0, 0x0, 0x0, 0x0, 0x10, 0x0, 0x0, 0x0, 0x0, 0x10, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0x4, 0x0, 0x10, 0x0, 0x0, 0x0, 0x40, 0x20, 0x0, 0x0, 0x20, 0x0, 0x0, 0xC1, 0x0, 0x0, 0xC0, 0x10, 0x6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x0, 0x4, 0x4, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0 };  // w=300  h=6
const uint8_t dino[] = { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xF, 0xF0, 0x0, 0x1B, 0xF8, 0x0, 0x1F, 0xF8, 0x0, 0x1F, 0xF8, 0x0, 0x1F, 0xF8, 0x0, 0x1F, 0x0, 0x0, 0x1F, 0xE0, 0x40, 0x3E, 0x0, 0x40, 0xFE, 0x0, 0x61, 0xFF, 0x80, 0x7F, 0xFE, 0x80, 0x7F, 0xFE, 0x0, 0x7F, 0xFE, 0x0, 0x1F, 0xFC, 0x0, 0xF, 0xF8, 0x0, 0x7, 0xF0, 0x0, 0x3, 0xB0, 0x0, 0x3, 0x10, 0x0, 0x3, 0x10, 0x0, 0x3, 0x18, 0x0, 0x3, 0x18, 0x0 };                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        // w=22  h=23
const uint8_t dino_run0[] = { 0x0, 0x0, 0x0, 0x0, 0xF, 0xF0, 0x0, 0x1F, 0xF8, 0x0, 0x1B, 0xF8, 0x0, 0x1F, 0xF8, 0x0, 0x1F, 0xF8, 0x0, 0x1F, 0xF8, 0x0, 0x1F, 0x0, 0x0, 0x1F, 0xE0, 0x40, 0x3E, 0x0, 0x61, 0xFF, 0x80, 0x73, 0xFF, 0x80, 0x7F, 0xFE, 0x0, 0x7F, 0xFE, 0x0, 0x3F, 0xFE, 0x0, 0x1F, 0xFC, 0x0, 0xF, 0xF8, 0x0, 0x7, 0xF0, 0x0, 0x3, 0x98, 0x0, 0x3, 0x0, 0x0, 0x2, 0x0, 0x0, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0 };                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     // w=22  h=23
const uint8_t dino_run1[] = { 0x0, 0x0, 0x0, 0x0, 0xF, 0xF0, 0x0, 0x1F, 0xF8, 0x0, 0x1B, 0xF8, 0x0, 0x1F, 0xF8, 0x0, 0x1F, 0xF8, 0x0, 0x1F, 0xF8, 0x0, 0x1F, 0x0, 0x0, 0x1F, 0xE0, 0x40, 0x3E, 0x0, 0x61, 0xFF, 0x80, 0x73, 0xFF, 0x80, 0x7F, 0xFE, 0x0, 0x7F, 0xFE, 0x0, 0x3F, 0xFE, 0x0, 0x1F, 0xFC, 0x0, 0xF, 0xF8, 0x0, 0x7, 0xF0, 0x0, 0x3, 0x30, 0x0, 0x1, 0x90, 0x0, 0x0, 0x10, 0x0, 0x0, 0x18, 0x0, 0x0, 0x0, 0x0 };                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  // w=22  h=23
const uint8_t* dinoSprite[] = { dino_run0, dino_run1 };

const uint8_t moon[] = { 0xFC, 0x0, 0x0, 0xFC, 0x0, 0x0, 0x1F, 0xC0, 0x0, 0x1F, 0xC0, 0x0, 0x7, 0xF0, 0x0, 0x7, 0xF0, 0x0, 0x1, 0xFC, 0x0, 0x1, 0xFC, 0x0, 0x0, 0xFF, 0x0, 0x0, 0xFF, 0x0, 0x0, 0xFF, 0x0, 0x0, 0x7F, 0xC0, 0x0, 0x7F, 0xC0, 0x0, 0x7F, 0xC0, 0x0, 0x7F, 0xF0, 0x0, 0x7F, 0xF0, 0x0, 0x7F, 0xF0, 0x0, 0x7F, 0xF0, 0x0, 0x7F, 0xF0, 0x0, 0x7F, 0xF0, 0x0, 0x7F, 0xF0, 0x0, 0x7F, 0xF0, 0x0, 0x7F, 0xF0, 0x0, 0x7F, 0xF0, 0x0, 0x7F, 0xF0, 0x0, 0x7F, 0xF0, 0x0, 0x7F, 0xC0, 0x0, 0x7F, 0xC0, 0x0, 0x7F, 0xC0, 0x0, 0xFF, 0x0, 0x0, 0xFF, 0x0, 0x0, 0xFF, 0x0, 0x1, 0xFC, 0x0, 0x1, 0xFC, 0x0, 0x7, 0xF0, 0x0, 0x7, 0xF0, 0x0, 0x1F, 0xC0, 0x0, 0x1F, 0xC0, 0x0, 0xFC, 0x0, 0x0, 0xFC, 0x0, 0x0 };  // w=20  h=40
const uint8_t star0[] = { 0x10, 0x54, 0x38, 0xFF, 0x38, 0x54, 0x10, 0x10 };                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       // w=8  h=8
const uint8_t star1[] = { 0x92, 0x10, 0x38, 0xFF, 0x38, 0x10, 0x92, 0x10 };                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       // w=8  h=8

const uint8_t bcactus0[] = { 0x6, 0x0, 0xF, 0x0, 0xF, 0x0, 0xF, 0x0, 0xF, 0x0, 0xF, 0x60, 0x6F, 0x70, 0xEF, 0x70, 0xEF, 0x70, 0xEF, 0x70, 0xEF, 0x70, 0xEF, 0x70, 0xEF, 0x70, 0xFF, 0xF0, 0xFF, 0xE0, 0x7F, 0xC0, 0x3F, 0x0, 0xF, 0x0, 0xF, 0x0, 0xF, 0x0, 0xF, 0x0, 0xF, 0x0, 0xF, 0x40, 0x3F, 0x0, 0x1, 0x0 };  // w=12  h=25
const uint8_t bcactus1[] = { 0x6, 0x0, 0xF, 0x0, 0xF, 0x0, 0xF, 0x0, 0xF, 0x0, 0xF, 0x60, 0x6F, 0xF0, 0xFF, 0xF0, 0xFF, 0xF0, 0xFF, 0xF0, 0xFF, 0xF0, 0xFF, 0xF0, 0xFF, 0xF0, 0xFF, 0xF0, 0xFF, 0xE0, 0x7F, 0xC0, 0x3F, 0x0, 0xF, 0x0, 0xF, 0x0, 0xF, 0x0, 0xF, 0x0, 0xF, 0x0, 0xF, 0xC0, 0x3F, 0x0, 0x1, 0x0 };  // w=12  h=25
// const uint8_t* bcactusSprites[] = { bcactus0, bcactus1 };

const uint8_t smcactus0[] = { 0x0, 0x18, 0x18, 0x1B, 0x1B, 0x5B, 0x5B, 0x5F, 0x5E, 0x7C, 0x78, 0x38, 0x18, 0x18, 0x18, 0x18, 0x18 };  // w=8  h=17
const uint8_t smcactus1[] = { 0x0, 0x18, 0x18, 0x7B, 0x7B, 0x7B, 0x7B, 0x7B, 0x3F, 0x1E, 0x1C, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18 };  // w=8  h=17
const uint8_t smcactus2[] = { 0x0, 0x18, 0x58, 0x58, 0x5A, 0x5B, 0x5B, 0x5B, 0x5B, 0x5B, 0x7B, 0x3E, 0x1C, 0x18, 0x18, 0x18, 0x18 };  // w=8  h=17
const uint8_t smcactus3[] = { 0x0, 0x18, 0x58, 0x5B, 0x5B, 0x5B, 0x5B, 0x7B, 0x7F, 0x3E, 0x1C, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18 };  // w=8  h=17
// const uint8_t* smcactusSprites[] = { smcactus0, smcactus1, smcactus2, smcactus3 };


struct Cactus {
  const uint8_t* data;
  const int w;
  const int h;
  int posX;
};

Cactus c0{ smcactus0, 8, 17, 100 };


uint8_t dinoSpriteIdx = 0;
/*------------------------------
||      GLOBAL  DECLARATIONS  ||
-------------------------------*/

constexpr float GRAVITY{ 0.2f };
float dinoVelY = 0.0f;
float dinoVelX = 1.0f;


#define JMP_BTN D3
#define REFERENCE_LEVEL 26

const int W = 160;
const int H = 128;


uint8_t dinoX;
uint8_t dinoY;
const uint8_t dinoBaseY = H - REFERENCE_LEVEL - 23 + 3;  // dino's Y cant be greater than this
const uint8_t dinoBaseX = 11;                            // dino's X cant be greater than this

const uint8_t dinoEndX = dinoBaseX + 22;


void setup(void) {
  pinMode(JMP_BTN, INPUT);

  tft.initR(INITR_BLACKTAB);
  tft.setRotation(1);

  clear();
  dinoY = dinoBaseY;  // At middle of track

  // idle
  uint8_t counter = 0;
  while (++counter) {
    if (counter >= 95) {
      
      tft.fillRect(13 + dinoX, 2 + dinoY, 1, 1, 0xFFFF);
    } else {
      
      tft.fillRect(13 + dinoX, 2 + dinoY, 1, 1, 0x0);
    }
    tft.drawBitmap(dinoX, dinoY, (uint8_t*)dino_rest, 22, 23, 0xFFFF);
    counter %= 101;
    int press = digitalRead(JMP_BTN);
    if (press == LOW) break;
    delay(10);
  }
  // During game start  the dino jumps and dino lands and moves little forward

  // start jump animation
  dinoJmp();
  clear();
  unsigned long then = millis();

  while (true) {
    unsigned long now = millis();
    float dt = (now - then) / 10.0f;
    then = now;
    tft.drawBitmap(dinoX, dinoY, (uint8_t*)dino, 22, 23, 0x0);
    updateDino(dt);
    if (dinoY > dinoBaseY) break;

    tft.drawBitmap(0, H - REFERENCE_LEVEL, (uint8_t*)track0, 22, 1, 0xFFFF);
    tft.drawBitmap(dinoX, dinoY, (uint8_t*)dino, 22, 23, 0xFFFF);
    delay(10);
  }

  // start run till baseX animation
  clear();
  drawStars();

  dinoY = dinoBaseY;
  while (true) {
    tft.drawBitmap(dinoX, dinoY, (uint8_t*)dinoSprite[dinoSpriteIdx], 22, 23, 0x0);
    dinoX += 1;
    if (dinoX >= dinoBaseX) {
      dinoX = dinoBaseX;
      break;
    }
    changeDinoSprite();
    tft.drawBitmap(0, H - REFERENCE_LEVEL, (uint8_t*)track0, 300, 6, 0xFFFF);
    tft.drawBitmap(dinoX, dinoY, (uint8_t*)dinoSprite[dinoSpriteIdx], 22, 23, 0xFFFF);
  }

  // clear();
  // drawStars();
  tft.drawBitmap(80, 10, moon, 20, 40, 0x9CF3, 0x0);
}




unsigned long then = millis();
int track0X = 0;
int track1X = 300;
float cloudX = 220.0f;
bool jumping = false;
uint8_t counter = 0;


GFXcanvas1 dino_ctx(22, dinoBaseY + 23);
GFXcanvas1 track_ctx(W, 6);
GFXcanvas1 cactusR_ctx(W - dinoEndX, 25);
GFXcanvas1 cactusL_ctx(dinoEndX, 25);
const uint8_t cactusSpriteY{ H - REFERENCE_LEVEL - 25 };

bool gameOver = false;
float score = 0.0f;


void loop() {



  if (gameOver) {
    tft.drawBitmap(c0.posX, cactusSpriteY + 25 - c0.h, c0.data, c0.w, c0.h, 0xFFFF);

    tft.invertDisplay(true);
    delay(500);
    tft.invertDisplay(false);
    delay(500);

    return;
  }

  unsigned long now = millis();
  float dt = (now - then) / 10.0f;
  then = now;






  /*-----------------
  ||  CLEAR canvas ||
  ------------------*/
  dino_ctx.fillRect(0, dinoY, 22, 23, 0x0);
  track_ctx.fillRect(0, 0, W, 6, 0x0);
  if (c0.posX < dinoEndX) {
    cactusL_ctx.fillRect(c0.posX, 25 - c0.h, c0.w, c0.h, 0x0);
  }
  // else { TODO : see how to make else working
  cactusR_ctx.fillRect(c0.posX - dinoEndX, 25 - c0.h, c0.w, c0.h, 0x0);
  // }












  /*----------------------
  ||  UPDATE everything ||
  -----------------------*/
  score += dt / 10.0f;
  const float dx = dinoVelX * dt;
  changeDinoSprite();

  track0X -= dx;
  track1X -= dx;
  c0.posX -= dx;
  dinoVelX += 0.003;

  counter++;
  counter %= 50;


  if (track0X + 300 <= 0) {
    track0X = track1X + 300;
  }
  if (track1X + 300 <= 0) {
    track1X = track0X + 300;
  }

  if ((digitalRead(JMP_BTN) == LOW) && !jumping) {
    dinoJmp();
    jumping = true;
  }
  updateDino(dt);

  if (dinoY > dinoBaseY) {
    jumping = false;
    dinoY = dinoBaseY;
    dinoVelY = 0;
  }

  if (c0.posX + c0.w < 0) {
    tft.fillRect(0, cactusSpriteY, dinoBaseX, 25, 0x0);
    c0.posX = 170;
  }

  // COLLISION
  if (
    (c0.posX < dinoX + 22) && (c0.posX + c0.w > dinoX)
    && (cactusSpriteY + (25 - c0.h) < (dinoY + 23))

  ) {
    gameOver = true;
    tft.setCursor(tft.width() / 2 - 30, tft.height() / 2);
    tft.print("GAME OVER :)");
  }





  /*---------------------
  ||  DRAW on canvas   ||
  ----------------------*/
  drawStars();

  track_ctx.drawBitmap(track0X, 0, (uint8_t*)track0, 300, 6, 0xFFFF);
  track_ctx.drawBitmap(track1X, 0, (uint8_t*)track1, 300, 6, 0xFFFF);
  if (jumping) {
    dino_ctx.drawBitmap(0, dinoY, dino, 22, 23, 0xFFFF);
  } else {
    dino_ctx.drawBitmap(0, dinoY, (uint8_t*)dinoSprite[dinoSpriteIdx], 22, 23, 0xFFFF);
  }


  if (c0.posX <= dinoEndX) {
    cactusL_ctx.drawBitmap(c0.posX, 25 - c0.h, c0.data, c0.w, c0.h, 0xFFFF);

  } else {
    cactusR_ctx.drawBitmap(c0.posX - dinoEndX, 25 - c0.h, c0.data, c0.w, c0.h, 0xFFFF);
  }



  if (counter >= 47) {
    dino_ctx.drawPixel(13, 3 + dinoY, 0xFFFF);
  } else {
    dino_ctx.drawPixel(13, 3 + dinoY, 0x0);
  }










  /*--------------------------
  ||  transfer to display   ||
  ---------------------------*/
  tft.fillRect(100, 0, 60, 9, 0x0);
  tft.setCursor(100, 0);
  tft.print((int)score);

  tft.drawBitmap(0, H - REFERENCE_LEVEL, track_ctx.getBuffer(), W, 6, 0xFFFF, 0x0);
  // tft.drawBitmap(80, 10, moon, 20, 40, 0x9CF3, 0x0);
  if (c0.posX <= dinoEndX) {
    tft.drawBitmap(0, cactusSpriteY, cactusL_ctx.getBuffer(), cactusL_ctx.width(), cactusL_ctx.height(), 0xFFFF, 0x0);
  }
  // else { TODO : see how to make else working
  tft.drawBitmap(dinoEndX, cactusSpriteY, cactusR_ctx.getBuffer(), cactusR_ctx.width(), cactusR_ctx.height(), 0xFFFF, 0x0);
  // }
  tft.drawBitmap(dinoX, -2, dino_ctx.getBuffer(), 22, dino_ctx.height(), 0xFFFF, 0x0);
}


void drawStars() {
  // star0
  tft.drawPixel(80, 74, random(0, 0xFFFF));
  tft.drawPixel(60, 50, random(0, 0xFFFF));
  tft.drawPixel(100, 80, random(0, 0xFFFF));

  dino_ctx.drawPixel(10, 60, random(0, 0xFFFF));

  tft.drawPixel(150, 20, random(0, 0xFFFF));
  tft.drawPixel(70, 30, random(0, 0xFFFF));
  tft.drawPixel(10, 10, random(0, 0xFFFF));
  tft.drawPixel(158, 90, random(0, 0xFFFF));
  tft.drawPixel(130, 70, random(0, 0xFFFF));
  tft.drawPixel(140, 68, random(0, 0xFFFF));
  tft.drawPixel(156, 98, random(0, 0xFFFF));
}


/*------------------------------
||      FUNCTION DEFINATIONS  ||
-------------------------------*/

void dinoJmp() {
  dinoVelY = -7.5f;
}

void updateDino(float dt) {
  dinoVelY += GRAVITY * dt; // dv=a*dt
  dinoY += dinoVelY * dt;  // ds=v*dt
}

void changeDinoSprite() {
  dinoSpriteIdx += 1;
  dinoSpriteIdx %= 2;
}


void clear() {
  tft.fillScreen(0);
}
