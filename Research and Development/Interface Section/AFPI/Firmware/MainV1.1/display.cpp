#include "display.h"

#include "config.h"
#include "rotary_encoder_ctrl.h"
#include "home_button.h"
// Initialize the display object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire1, OLED_RESET);

// Define the bitmaps
const unsigned char PROGMEM logo_bmp[] = {
  0b00000000, 0b11000000,
  0b00000001, 0b11000000,
  0b00000001, 0b11000000,
  0b00000011, 0b11100000,
  0b11110011, 0b11100000,
  0b11111110, 0b11111000,
  0b01111110, 0b11111111,
  0b00110011, 0b10011111,
  0b00011111, 0b11111100,
  0b00001101, 0b01110000,
  0b00011011, 0b10100000,
  0b00111111, 0b11100000,
  0b00111111, 0b11110000,
  0b01111100, 0b11110000,
  0b01110000, 0b01110000,
  0b00000000, 0b00110000
};

const uint8_t bitmap37[] = {
  0x00, 0x00, 0x00,
  0x00, 0x00, 0x00,
  0x00, 0x00, 0x00,
  0x00, 0x00, 0x00,
  0x00, 0x00, 0x00,
  0x7f, 0xff, 0xe0,
  0xff, 0xff, 0xf0,
  0xc0, 0x00, 0x30,
  0xc0, 0x00, 0x30,
  0xc0, 0x00, 0x30,
  0xc0, 0x00, 0x33,
  0xc0, 0x00, 0x33,
  0xc0, 0x00, 0x33,
  0xc0, 0x00, 0x33,
  0xc0, 0x00, 0x30,
  0xc0, 0x00, 0x30,
  0xc0, 0x00, 0x30,
  0xff, 0xff, 0xf0,
  0x7f, 0xff, 0xe0,
  0x00, 0x00, 0x00,
  0x00, 0x00, 0x00,
  0x00, 0x00, 0x00,
  0x00, 0x00, 0x00,
  0x00, 0x00, 0x00
};


void initializeDisplay() {
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        for (;;); // Infinite loop to halt execution if display initialization fails
    }

    display.display();
    setOLEDContrast(oledContrast);
    testLoadingScreen();
}


void setOLEDContrast(uint8_t contrast) {
  display.ssd1306_command(SSD1306_SETCONTRAST);
  display.ssd1306_command(contrast);
}



void testLoadingScreen() {
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.setFont(NULL);
    display.setCursor(0, 10);
    display.println("Expeditioner ");
    display.println("Alex Stewart");
    display.println("");
    display.println("Loading...");
    display.display();
}


const uint8_t bitmap21[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xe0, 0xff, 0xff, 0xf0, 0xc0, 0x00, 0x30, 0xc0, 0x00, 0x30, 0xc0, 0x00, 0x30, 0xc0, 0x00, 0x33, 0xc0, 0x00, 0x33, 0xc0, 0x00, 0x33, 0xc0, 0x00, 0x33, 0xc0, 0x00, 0x30, 0xc0, 0x00, 0x30, 0xc0, 0x00, 0x30, 0xff, 0xff, 0xf0, 0x7f, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

void setFXTemplatePage(char title[], bool& FXActive, bool fxCheck) {
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setFont(NULL);
  display.setCursor(0, 10);
  display.setCursor(0, 5);
  display.setTextWrap(0);
  display.setCursor(28, 5);
  display.println(title);
  display.drawLine(0, 18, 128, 18, 1);
  display.drawRect(109, 50, 17, 12, 1);
  display.drawTriangle(114, 58, 120, 55, 114, 52, 1);
  display.drawRect(2, 50, 17, 12, 1);
  display.drawTriangle(13, 58, 13, 52, 6, 55, 1);
  display.fillTriangle(114, 58, 120, 55, 114, 52, 1);
  display.fillTriangle(13, 58, 13, 52, 6, 55, 1);
  display.drawBitmap(102, -3, bitmap21, 24, 24, 1);
  if (fxCheck) {
    if (FXActive == true){
      display.fillRoundRect(60, 50, 10, 10, 3, 1);
    }
    else {
      display.drawRoundRect(60, 50, 10, 10, 3, 1);
    }
  }
}

void checkScreenTime() {
    unsigned long currentMillis = millis(); // Get the current time

    // Check if 10 seconds have passed since the last reset and button has not been pressed
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis; // Reset the timer
      screenSaverActive();
    }
}

void screenSaverActive() {
    display.clearDisplay();
    display.display();
    while (true) {
      if (checkActivity()) {
        break;
      }
      delay(50);
    }
    resetScreenSaver();

}

void resetScreenSaver() {
    previousMillis = millis();
}

bool checkActivity() {
  if (!ss.digitalRead(SS_ENC3_SWITCH)) {
      while (!ss.digitalRead(SS_ENC3_SWITCH)) {
        delay(50);
      }
    return true;
  }

  if (!ss.digitalRead(SS_ENC2_SWITCH)) {
      while (!ss.digitalRead(SS_ENC2_SWITCH)) {
        delay(50);
      }
      return true;
  }

  if (!ss.digitalRead(SS_ENC1_SWITCH)) {
      while (!ss.digitalRead(SS_ENC1_SWITCH)) {
        delay(50);
      }
      return true;
  }

  if (!ss.digitalRead(SS_ENC0_SWITCH)) {
      while (!ss.digitalRead(SS_ENC0_SWITCH)) {
        delay(50);
      }
      return true;
  }

  if (homeButtonActivity()) {
      return true;
  }

  int32_t enc_pos0 = ss.getEncoderPosition(0);
  if (enc_positions[0] != enc_pos0) {
    enc_positions[0] = enc_pos0;
    return true;
  }
  int32_t enc_pos1 = ss.getEncoderPosition(1);
  if (enc_positions[1] != enc_pos1) {
    enc_positions[1] = enc_pos1;
    return true;
  }
  int32_t enc_pos2 = ss.getEncoderPosition(2);
  if (enc_positions[2] != enc_pos2) {
    enc_positions[2] = enc_pos2;
    return true;
  }
  int32_t enc_pos3 = ss.getEncoderPosition(3);
  if (enc_positions[3] != enc_pos3) {
    enc_positions[3] = enc_pos3;
    return true;
  } else {
    return false;
  }

}