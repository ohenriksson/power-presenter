
"%programFiles(x86)%\Arduino\hardware\tools\avr/bin/avrdude" 
-C"%programFiles(x86)%\Arduino\hardware\tools\avr/etc/avrdude.conf" -v -patmega328p -carduino -PCOM3 -b115200 -D -Uflash:w:C:\Users\path\to\project\rust-arduino-blink\target\avr-atmega328p\debug\rust-arduino-blink.elf:e'