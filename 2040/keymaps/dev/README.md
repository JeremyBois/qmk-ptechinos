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
  - [ ] Leader key on inner right thumb
    - Leader + Leader = TO(0)
  - [x] Shift on thumbs
    - Remove mod-taps on pinkies allowing game full compatibility
    - Reduce complexity associated with selection of the correct pinky for the correct side
  - [x] Easy access to symbols while inside the number layer
    - Use a move_hold switcher for numbers
      - Allow permanent switch to this layer (like for navigation)
    - Use a oneshot_hold switcher for symbols with layer activation not move
      - Previous *move* layer (nav or num) is still active and only replaced temporary by the symbol layer
    - Can now stay inside the num layer for debugging and typing numbers while still getting access to symbols
  - [x] Create a more ergonomic base layer that is compatible with the existing layer without drastic changes
    - Inspiration from the following layers
      - `Graphite` for keys global placement
      - `Fire` for increasing rolls without increasing redirects to much using `m` with vowels
  - [x] Avoid parasitics mouse movement due to trackball tiny movements while typing
    - If mouse layer is active then mouse report is untouched
    - If mouse layer is inactive then mouse report is erased

