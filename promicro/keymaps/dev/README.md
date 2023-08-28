# Experimental layout

  - https://www.rousette.org.uk/archives/back-to-beakl/
  - https://keymapdb.com/rafaelromao/


## Build
Flash using **EEPROM** for handness
  - Left --> `qmk flash -kb ptechinos/promicro -km dev -bl dfu-split-left`
  - Right --> `qmk flash -kb ptechinos/promicro -km dev -bl dfu-split-right`


## Todo

  - [ ] Add a way to make diacritics software independant
    - unicode to output diacritics on Azerty/Qwerty without dead keys
