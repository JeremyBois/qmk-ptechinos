# README


## Build
Flash using **EEPROM** for handness
  - Left --> `make --jobs=1 ptechinos/2040:dev:uf2-split-left trackpad=true`
  - Right --> `make --jobs=1 ptechinos/2040:dev:uf2-split-right trackball=true`

Compile using **#define** for handness
  - Left --> `make --jobs=1 ptechinos/2040:dev trackpad=true`
  - Right --> `make --jobs=1 ptechinos/2040:dev trackball=true`

## TODO
  - [x] Secure option
    - https://github.com/qmk/qmk_firmware/blob/master/docs/feature_secure.md
    - Not really needed
  - [x] Keymap
    - [x] Create MOUSE layer
     - Mirror left and right side (same experience with both pointers)
    - [x] Improve NUM layer
      - All numbers on the same side
    - [x] Improve NAV layer
      - Easier scrolling
      - Tab motion
      - Desktop motion on left hand (drag and drop with mouse will changing desktop)
      - Same location for left and right clic as the MOUSE layer (easier to remenber)
  - [ ] nkro
  - [x] Quick tap
    - https://github.com/vial-kb/vial-qmk/blob/vial/docs/tap_hold.md
    - 0 <= `QUICK_TAP_TERM` <= `TAPPING_TERM`
      - tap time <= `QUICK_TAP_TERM` --> trigger auto repeat key feature
    - Currently `QUICK_TAP_TERM` == `TAPPING_TERM` (default)
  - [x] Combos
    - Adjust the hold `COMBO_HOLD_TERM` to be higher than than typical `TAPPING_TERM`
    - `TAPPING_TERM` == 200 --> `COMBO_HOLD_TERM` == 220
  - [x] One shot layer
    - [x] Fix implementation
    - [x] Add generic way to test modifier and mod tap
    - [x] Add filter for mod tap key
  - [ ] [Kinetic mouse keys](https://qmk.github.io/qmk_mkdocs/master/en/feature_mouse_keys/#kinetic-mode)
  - [x] Trackpad + Trackball
    - [x] Scroll
      - [x] Left
      - [x] Right
    - [x] Mouse
      - [x] Left
      - [x] Right
    - [x] DPI cycling
      - [x] Left
      - [x] Right
    - [x] Auto mouse layer
      - [x] Setup + Test
      - [x] Override keyboard level to define ptechinos mouse keys
      - [x] Override user level to define keymap mouse keys
  - [x] Mouse keys behave weird when auto mouse is enable
    - ?? Maybe a device make a small motion move to another layer ??
    - Mouse key scrolling activate the layer
  - [x] Auto mouse key timer is not reset when using custom keycodes (like CPI increase)
