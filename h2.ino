/*-=-= HYDROGEN 2 -=-=*/
// Creators github: https://github.com/gm521)

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
  char O[128] = "";
  sd.begin(10, SD_SCK_MHZ(4));
  File32 f = sd.open("prg.v");
  while (f.available()) {
    char c = f.read();
    strncat(O, &c, 1);
  }
  char* ln = strtok(O, ";");
  while (ln != nullptr) {
    lang_3bc_line(h, ln[0] - 48, ln[1] - 48, ln[2]);
    ln = strtok(nullptr, ";");
  }
}
void loop() {
  lang_3bc_update(h);
}
