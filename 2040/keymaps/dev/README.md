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
    - [x] Auto mouse layer
      - [x] Setup + Test
      - [x] Override keyboard level to define ptechinos mouse keys
      - [x] Override user level to define keymap mouse keys
  - [x] Mouse keys behave weird when auto mouse is enable
    - ?? Maybe a device make a small motion move to another layer ??
    - Mouse key scrolling activate the layer


## Bug

### Avoid triggering auto mouse layer when using MouseKey to scroll
```c
static bool is_mouse_record(uint16_t keycode, keyrecord_t* record) {
    // allow for keyboard to hook in and override if need be
    if (is_mouse_record_kb(keycode, record) || IS_MOUSEKEY(keycode)) return true;
    return false;
}
// Rewrite as
static bool is_mouse_record(uint16_t keycode, keyrecord_t* record) {
    // allow for keyboard to hook in and override if need be
    return is_mouse_record_kb(keycode, record);
}
// with a custom user record as defined below
bool is_mouse_record_user(uint16_t keycode, keyrecord_t* record) {
    // Avoid moving to L_MOUSE layer using a mouse key
    if (IS_LAYER_OFF(L_MOUSE)) {
        return false;
    }

    // Add custom keys from the L_MOUSE layer that continue the auto mouse feature
    switch (keycode) {
        case C_Z:
        case LALT_T(C_X):
        case C_X:
        case C_C:
        case C_V:
        case C_Y:
            return true;
    }

    // Finally include all mouse keys as in original QMK is_mouse_record
    return IS_MOUSEKEY(keycode);
}
```
