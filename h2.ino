/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
             HYDROGEN-2
          By GamingGamer521
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

// - Used in Crystal OS, an operating system for the arduino nano
// - Used in other personal projects of mine
#include <SdFat.h>
#define _3BC_DISABLE_INTERPRETER
#include <3bc.h>
SdFat sd;
struct app_3bc_s* h = lang_3bc_init();
void setup() {
  Serial.begin(9600);
  lang_3bc_print(h, tty_output, [](char* str){
    Serial.write(str);    
  });
  char O[196] = "";
  sd.begin(10, SD_SCK_MHZ(4));
  File32 f = sd.open("prg.v");
  while (f.available()) {
    char c = f.read();
    strncat(O, &c, 1);
  }
  char* ln = strtok(O, "\n");
  while (ln != nullptr) {
    char a0 = (10000 * (ln[0x0] - 48)) + (1000 * (ln[0x1] - 48)) + (100 * (ln[0x2] - 48)) + (10 * (ln[0x3] - 48)) + (ln[0x4] - 48);
    char a1 = (10000 * (ln[0x5] - 48)) + (1000 * (ln[0x6] - 48)) + (100 * (ln[0x7] - 48)) + (10 * (ln[0x8] - 48)) + (ln[0x9] - 48);
    char a2 = (10000 * (ln[0xa] - 48)) + (1000 * (ln[0xb] - 48)) + (100 * (ln[0xc] - 48)) + (10 * (ln[0xd] - 48)) + (ln[0xe] - 48);
    
    lang_3bc_line(h, a0, a1, a2);
    ln = strtok(nullptr, "\n");
  }
}
void loop() {
  lang_3bc_update(h);
}
