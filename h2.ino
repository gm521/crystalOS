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

char h2c(const char *h, int o) {
    return ((h[o] >= 'a' ? h[o] - 87 : h[o] - 48) << 4) |
    (h[o + 1] >= 'a' ? h[o + 1] - 87 : h[o + 1] - 48);
}

void setup() {
  Serial.begin(9600);
  lang_3bc_print(h, tty_output, [](char* str){
    Serial.write(str);    
  });
  char O[196];
  sd.begin(10, SD_SCK_MHZ(4));
  File32 f = sd.open("prg.v");
  while (f.available()) {
    char c = f.read();
    strncat(O, &c, 1);
  }
  char* ln = strtok(O, ";");
  while (ln != nullptr) {
    char a0 = h2c(ln, 0);
    char a1 = h2c(ln, 2);
    char a2 = h2c(ln, 4);
    
    lang_3bc_line(h, a0, a1, a2);
    ln = strtok(nullptr, ";");
  }
}
void loop() {
  lang_3bc_update(h);
}
