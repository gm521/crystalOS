/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
              CRYSTAL OS
           By GamingGamer521

          h2 (Hydrogen-2) BIOS
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

#include <SdFat.h>
#include <Wire.h>
#include "ssd1306.h"
#include "ssd1306_console.h"
#define _3BC_DISABLE_INTERPRETER
#define TBC_CUSTOM
#include <3bc.h>
SdFat sd;
struct app_3bc_s* h = lang_3bc_init();
Ssd1306Console t;

void setup() {
  ssd1306_128x64_i2c_init();
  ssd1306_clearScreen();
  ssd1306_setFixedFont(ssd1306xled_font6x8);
  lang_3bc_print(h, tty_output, [](char* str){
    t.print(str);
  });
  lang_3bc_custom(h, 1, 1,
  [](register_3bc_t reg, address_3bc_t addr, data_3bc_t chr) {
    t.print("ok");
  });
  t.println("ok");
  char O[255];
  sd.begin(10, SD_SCK_MHZ(4));
  File32 f = sd.open("prg.v");
  while (f.available()) {
    char c = f.read();
    strncat(O, &c, 1);
  }
  for (int i = 0; O[i] != 0; i += 4) {
    lang_3bc_line(h, MODE, NILL, O[0 + i]-16);
    lang_3bc_line(h, O[1 + i]-16, O[2 + i]-16, O[3 + i]-16);
  }
}
void loop() {
  lang_3bc_update(h);
}
