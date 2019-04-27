#pragma once
#include <U8g2_for_Adafruit_GFX.h>
#include <GxEPD2_BW.h>
#include <GxEPD2_3C.h>

extern  GxEPD2_BW<GxEPD2_213, MAX_HEIGHT(GxEPD2_213)> display;
extern  U8G2_FOR_ADAFRUIT_GFX u8g2Fonts;
const char E_START[] = "Emart Start-up...";
const char E_READY[] = "Ready";
const char E_SHOPPING[] = "Start Shopping!";
const char E_SCAN[] = "Scanning...";
const char E_ADD[] = "Item Added";
const char E_END[] = "Shopping Ends";

void EPaperStart();
void EndCallback(const void *);
void EPaperEnd();
void StartCallback(const void *);
void EPaperReady();
void ReadyCallback(const void *);
void EPaperShopping();
void EPaperScan();
void ShoppingCallback(const void *);
void ScanCallback(const void *);
void EPaperAdd();
void AddCallback(const void *);

void EPaperStart(){
  uint16_t bg = GxEPD_WHITE;
  uint16_t fg = GxEPD_BLACK;
  display.setRotation(1);
  u8g2Fonts.setFontMode(1);         // use u8g2 transparent mode (this is default)
  u8g2Fonts.setFontDirection(0);    // left to right (this is default)
  u8g2Fonts.setForegroundColor(fg); // apply Adafruit GFX color
  u8g2Fonts.setBackgroundColor(bg); // apply Adafruit GFX color
  u8g2Fonts.setFont(u8g2_font_timR24_tr);
  display.setFullWindow();
  display.drawPaged(StartCallback, 0);
}
void StartCallback(const void *) {
  uint16_t tbw;
  tbw = u8g2Fonts.getUTF8Width(E_START);
  // display.getTextBounds(E_START, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t x = (display.width() - tbw) / 2;
  uint16_t y = (display.height() + 24) / 2; // y is base line!
  display.fillScreen(GxEPD_WHITE);
  u8g2Fonts.setCursor(x, y); // start writing at this position
  u8g2Fonts.println(E_START);
}
void EPaperReady() {
  uint16_t bg = GxEPD_WHITE;
  uint16_t fg = GxEPD_BLACK;
  display.setRotation(1);
  u8g2Fonts.setFontMode(1);         // use u8g2 transparent mode (this is default)
  u8g2Fonts.setFontDirection(0);    // left to right (this is default)
  u8g2Fonts.setForegroundColor(fg); // apply Adafruit GFX color
  u8g2Fonts.setBackgroundColor(bg); // apply Adafruit GFX color
  u8g2Fonts.setFont(u8g2_font_timR24_tr);
  // display.setFullWindow();
  display.setPartialWindow(0, 0, display.width(), display.height());
  display.drawPaged(ReadyCallback, 0);
}
void ReadyCallback(const void *) {
  uint16_t tbw;
  tbw = u8g2Fonts.getUTF8Width(E_READY);
  // display.getTextBounds(E_START, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t x = (display.width() - tbw) / 2;
  uint16_t y = (display.height() + 24) / 2; // y is base line!
  display.fillScreen(GxEPD_WHITE);
  u8g2Fonts.setCursor(x, y); // start writing at this position
  u8g2Fonts.println(E_READY);
}
void EPaperShopping() {
  uint16_t bg = GxEPD_WHITE;
  uint16_t fg = GxEPD_BLACK;
  display.setRotation(1);
  u8g2Fonts.setFontMode(1);         // use u8g2 transparent mode (this is default)
  u8g2Fonts.setFontDirection(0);    // left to right (this is default)
  u8g2Fonts.setForegroundColor(fg); // apply Adafruit GFX color
  u8g2Fonts.setBackgroundColor(bg); // apply Adafruit GFX color
  u8g2Fonts.setFont(u8g2_font_timR24_tr);
  // display.setFullWindow();
  display.setPartialWindow(0, 0, display.width(), display.height());
  display.drawPaged(ShoppingCallback, 0);
}
void ShoppingCallback(const void *) {
  uint16_t tbw;
  tbw = u8g2Fonts.getUTF8Width(E_SHOPPING);
  // display.getTextBounds(E_START, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t x = (display.width() - tbw) / 2;
  uint16_t y = (display.height() + 24) / 2; // y is base line!
  // display.fillScreen(GxEPD_WHITE);
  u8g2Fonts.setCursor(x, y); // start writing at this position
  u8g2Fonts.println(E_SHOPPING);
}
void EPaperScan() {
  uint16_t bg = GxEPD_WHITE;
  uint16_t fg = GxEPD_BLACK;
  display.setRotation(1);
  u8g2Fonts.setFontMode(1);         // use u8g2 transparent mode (this is default)
  u8g2Fonts.setFontDirection(0);    // left to right (this is default)
  u8g2Fonts.setForegroundColor(fg); // apply Adafruit GFX color
  u8g2Fonts.setBackgroundColor(bg); // apply Adafruit GFX color
  u8g2Fonts.setFont(u8g2_font_timR24_tr);
  display.setPartialWindow(0, 0, display.width(), display.height());
  display.drawPaged(ScanCallback, 0);
}
void ScanCallback(const void *) {
  uint16_t tbw;
  tbw = u8g2Fonts.getUTF8Width(E_SCAN);
  // display.getTextBounds(E_START, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t x = (display.width() - tbw) / 2;
  uint16_t y = (display.height() + 24) / 2; // y is base line!
  display.fillScreen(GxEPD_WHITE);
  u8g2Fonts.setCursor(x, y); // start writing at this position
  u8g2Fonts.println(E_SCAN);
}
void EPaperAdd() {
  uint16_t bg = GxEPD_WHITE;
  uint16_t fg = GxEPD_BLACK;
  display.setRotation(1);
  u8g2Fonts.setFontMode(1);         // use u8g2 transparent mode (this is default)
  u8g2Fonts.setFontDirection(0);    // left to right (this is default)
  u8g2Fonts.setForegroundColor(fg); // apply Adafruit GFX color
  u8g2Fonts.setBackgroundColor(bg); // apply Adafruit GFX color
  u8g2Fonts.setFont(u8g2_font_timR24_tr);
  display.setPartialWindow(0, 0, display.width(), display.height());
  display.drawPaged(AddCallback, 0);
}
void AddCallback(const void *) {
  uint16_t tbw;
  tbw = u8g2Fonts.getUTF8Width(E_ADD);
  // display.getTextBounds(E_START, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t x = (display.width() - tbw) / 2;
  uint16_t y = (display.height() + 24) / 2; // y is base line!
  display.fillScreen(GxEPD_WHITE);
  u8g2Fonts.setCursor(x, y); // start writing at this position
  u8g2Fonts.println(E_ADD);
}
void EPaperEnd() {
  uint16_t bg = GxEPD_WHITE;
  uint16_t fg = GxEPD_BLACK;
  display.setRotation(1);
  u8g2Fonts.setFontMode(1);         // use u8g2 transparent mode (this is default)
  u8g2Fonts.setFontDirection(0);    // left to right (this is default)
  u8g2Fonts.setForegroundColor(fg); // apply Adafruit GFX color
  u8g2Fonts.setBackgroundColor(bg); // apply Adafruit GFX color
  u8g2Fonts.setFont(u8g2_font_timR24_tr);
  display.setFullWindow();
  display.drawPaged(EndCallback, 0);
}
void EndCallback(const void *) {
  uint16_t tbw;
  tbw = u8g2Fonts.getUTF8Width(E_END);
  // display.getTextBounds(E_START, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t x = (display.width() - tbw) / 2;
  uint16_t y = (display.height() + 24) / 2; // y is base line!
  // display.fillScreen(GxEPD_WHITE);
  u8g2Fonts.setCursor(x, y); // start writing at this position
  u8g2Fonts.println(E_END);
}
