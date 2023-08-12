# README


## Build
Flash using **EEPROM** for handness
  - Left --> `make --jobs=1 ptechinos/2040:dev:uf2-split-left trackpad=true`
  - Right --> `make --jobs=1 ptechinos/2040:dev:uf2-split-right trackball=true`

Compile using **#define** for handness
  - Left --> `make --jobs=1 ptechinos/2040:dev trackpad=true`
  - Right --> `make --jobs=1 ptechinos/2040:dev trackball=true`

## TODO
  - [ ] Secure option
    - https://github.com/qmk/qmk_firmware/blob/master/docs/feature_secure.md
  - [ ] nkro
  - [ ] Quick tap
  - [ ] Test case `QK_MODS ... QK_MODS_MAX` and one shot layer bitshifting
  - [ ] [Kinetic mouse keys](https://qmk.github.io/qmk_mkdocs/master/en/feature_mouse_keys/#kinetic-mode)
  - [ ] Trackpad + Trackball
    - [x] Scroll
      - [x] Left
      - [x] Right
    - [ ] Sniping
      - [ ] Left
      - [ ] Right
    - [ ] Gesture
      - [ ] Left
      - [ ] Right
    - [x] Mouse
      - [x] Left
      - [x] Right
    - [x] DPI cycling
      - [x] Left
      - [x] Right
