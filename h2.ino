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
    char a0 = (10000 * (ln[0] - 48)) + (1000 * (ln[1] - 48)) + (100 * (ln[2] - 48)) + (10 * (ln[3] - 48)) + (ln[4] - 48);
    char a1 = (10000 * (ln[5] - 48)) + (1000 * (ln[6] - 48)) + (100 * (ln[7] - 48)) + (10 * (ln[8] - 48)) + (ln[9] - 48);
    char a2 = (10000 * (ln[10] - 48)) + (1000 * (ln[11] - 48)) + (100 * (ln[12] - 48)) + (10 * (ln[13] - 48)) + (ln[14] - 48);
    
    lang_3bc_line(h, a0, a1, a2);
    ln = strtok(nullptr, "\n");
  }
}
void loop() {
  lang_3bc_update(h);
}
