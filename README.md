Klock- och Temperaturprojekt
Författare: Kaan Önal
Datum: 2024-10-10

Beskrivning
Detta projekt använder en DS3231 realtidsklocka (RTC) och ett temperaturstyrsystem som visas på en OLED-skärm. Projektet visar aktuell tid och temperaturavläsningar på OLED-skärmen och använder en kontinuerlig servomotor för att justera hastigheten baserat på temperaturavläsningarna. När temperaturen överstiger en viss gräns tänds en LED som en visuell varning.

Komponenter
Arduino mikrokontroller – Huvudkontroller för projektet.
DS3231 RTC-modul – Håller reda på tid och temperatur.
OLED-display (128x64, I2C) – Visar tid och temperaturinformation.
Servomotor – Justerar hastighet baserat på temperatur.
LED – Tänds när temperaturen överstiger en angiven gräns.
Termistor (valfritt) – Läser omgivningens temperatur som ett alternativt indata.
Nödvändiga Bibliotek
Servo.h – För att styra den kontinuerliga servomotorn.
RTClib.h – För att kommunicera med DS3231 RTC-modulen.
Wire.h – För I2C-kommunikation.
U8glib.h – För att hantera OLED-displayen.
