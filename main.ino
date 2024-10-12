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
#define TBC_SCU_FORCE
#include <3bc.h>

SdFat sd;
struct app_3bc_s* h = lang_3bc_init();
Ssd1306Console t;

void setup() {
  // configure OLED
  ssd1306_128x64_i2c_init();
  ssd1306_clearScreen();
  ssd1306_setFixedFont(ssd1306xled_font6x8);
  
  // graphics driver
  lang_3bc_print(h, tty_output, [](char* str){
    t.print(str);
  });
  t.print("Crystal OS\n"); delay(100);
  t.print("Drivers:\n"); delay(100);

  /******* File I/O Driver *******/
  sd.begin(10, SD_SCK_MHZ(4)); // Begin SD card

  // Open file function
  driver_custom_set(h, 10, 1,
  [](data_3bc_t chr) {
    char filename[12];
    int itr = 0;
    while (driver_memory_data_get(h, chr + itr) != 0) {
      char c = driver_memory_data_get(h, chr + itr);
      strncat(filename, &c, 1);
      itr ++;
    }
    sd.open("boot.v");
  });
  t.print("File I/O Driver [OK]"); delay(100);

  char O[255];
  File32 f = sd.open("boot.v");
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
