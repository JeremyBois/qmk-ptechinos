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
  - [ ] Trackpad + Trackball
    - [x] Scroll
      - [x] Left
      - [x] Right
    - [ ] Sniping
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
  - [x] Auto mouse key timer is not reset when using custom keycodes (like CPI increase)


## Bug
### Allow a mouse key to reset the timer to stay in the mouse layer
```c
void auto_mouse_keyevent(bool pressed) {
    if (pressed) {
        auto_mouse_context.status.mouse_key_tracker++;
    } else {
        auto_mouse_context.status.mouse_key_tracker--;
    }
    auto_mouse_context.timer.delay = 0;
}
// Rewrite as
void auto_mouse_keyevent(bool pressed) {
    if (pressed) {
        auto_mouse_context.status.mouse_key_tracker++;
    } else {
        auto_mouse_context.status.mouse_key_tracker--;
    }
#    ifdef AUTO_MOUSE_MOUSEKEY_ACTIVATION
    // Timer will also be reset by any mousekey press while mouse layer is on
    if (layer_state_is((AUTO_MOUSE_TARGET_LAYER))) {
        auto_mouse_context.timer.active = timer_read();
    }
#    endif
    auto_mouse_context.timer.delay = 0;
}
```

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
