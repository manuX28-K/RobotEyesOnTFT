/* Directional Gaze-Based Dual Blue Eye Animation (OLED-style) with Blinks.
   > ESP32 + ST7789 (240x280) using TFT_eSPI and sprites.
   > The only working sketch so far, nothing else works. For S3; specially use PSRAM type as QSPI and USB CDC set to disabled.
   > Add the command ' #define USE_HSPI_PORT ' to USER_SETUP file in the TFT_eSPI library folder, without it S3s (literally) refuses to work. 
   > MUST use pin 11 as SDA(MOSI) and pin 12 as SCL(SCLK), DO NOT USE MISO if your display DOES NOT have touch input. Instead set MISO -1 to deactivate
   the requirement for that mode: use these pins in the TFT_eSPI library setup for S3s. Rest of the ESPs work just fine without adding that specific
   command...actually they don't need it tbh...this sketch uses DMA through the TFT_eSPI library so add the command '#define SUPPORT_TRANSACTIONS' 
   to the setup file to enable it. NODE MCUs such as ESP8266/D1 MINIs aren't tested, test at your own risk.  */


/* This is my first time making something like this, my LCD screen getting fried is what inspired me to make it (LOL). and i want to mention that
   I am no coding expert which means ChatGPT helped me a lot ( actually a lot ) to bring this to reality, kudos to GPT for its help. And thank
   you for testing this out and if there's any improvement or suggestion to this please let me know, hope you'll enjoy !!! - manuX */

#include <TFT_eSPI.h>
#include <SPI.h>

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite leftEye = TFT_eSprite(&tft);
TFT_eSprite rightEye = TFT_eSprite(&tft);

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 280

int eyeWidth = 70;      // width of a one EYE --> applied to both
int eyeHeight = 80;     // height of a one EYE --> applied to both
int eyeSpacing = 65;    // minimum should be 65 or else two sprite instances would overlap and causes flickering.
int centerY = (SCREEN_HEIGHT / 2) - 40;

int leftX = SCREEN_WIDTH / 2 - eyeSpacing;
int rightX = SCREEN_WIDTH / 2 + eyeSpacing;
int leftY = centerY;
int rightY = centerY;

float currentX = 0, currentY = 0;
int targetX = 0, targetY = 0;
unsigned long lastMove = 0;
unsigned long moveInterval = 3000; // every 3s new gaze, DO NOT set the same time as blink time to avoid crashing
float easing = 0.5;

bool blinking = false;
unsigned long lastBlink = 0;
unsigned long blinkInterval = 5000;  // blinks every 5 seconds
unsigned long blinkDuration = 150;   // blink duration set to 150 miliseconds (use between 100 - 300)

// setup part happens here. DO NOT change values.
void setup() {
  tft.init();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);

  leftEye.createSprite(eyeWidth + 60, eyeHeight + 120);
  rightEye.createSprite(eyeWidth + 80, eyeHeight + 120);
  leftEye.setSwapBytes(true);
  rightEye.setSwapBytes(true);
}
// Drawing of the eye happens here, creates a new Sprite object to draw the eyes outside of the screen to avoid flickering.
void drawBlueEye(TFT_eSprite &eye, int eyeX, int eyeY, int moveX, int moveY, bool closed) {
  eye.fillSprite(TFT_BLACK);
  if (closed) {
    eye.fillRect(10, eyeHeight / 2, eyeWidth, 10, TFT_CYAN; /* change the TFT_... color to your prefered color to
    apply that specific color to the eyelid */
  } else {
    eye.fillRoundRect(10 + moveX, 10 + moveY, eyeWidth, eyeHeight, 20, TFT_CYAN); /* same goes here, not all RGB colors are supported
    at the moment. only supports colors from the TFT_eSPI library */
  }
  eye.pushSprite(eyeX - (eyeWidth / 2 + 10), eyeY - (eyeHeight / 2 + 10));
}

// pushing sprite eyes to the screen using pushsprite method, DO NOT edit values.
void loop() {
  unsigned long now = millis();

  // Blink logic
  if (!blinking && now - lastBlink > blinkInterval) {
    blinking = true;
    lastBlink = now;
  }
  if (blinking && now - lastBlink > blinkDuration) {
    blinking = false;
    lastBlink = now;
  }

  // Choose a new random gaze direction every few seconds
  if (now - lastMove > moveInterval && !blinking) {
    lastMove = now;
    targetX = random(-10, 50); // adjust gaze box
    targetY = random(-10, 50); // i got this part from Chat-GPT so i have no clue how it works, experiment to find out for yourself.
  }

  // Easing movement toward target
  currentX += (targetX - currentX) * easing;
  currentY += (targetY - currentY) * easing;

  drawBlueEye(leftEye, leftX, leftY, (int)currentX, (int)currentY, blinking);
  drawBlueEye(rightEye, rightX, rightY, (int)currentX, (int)currentY, blinking);

  delay(30);
}
