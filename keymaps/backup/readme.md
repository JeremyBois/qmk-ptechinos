# Keymap

## Used Features

- Support for Qwerty / Colemak

- Consistent layer one shot / hold / move
  - no timer
    - hold the trigger while tapping another key
      - key from layer while holding
    - tap/release the trigger before hitting another key
      - change layer (move or activate)
  - hold + one shot layer
  - hold + move layer
  - hold + activate layer

- Navigation layer
  - no timer
  - mouse, 4 buttons and scroll
  - arrows, begin, end
  - auto ctrl for common task (paste, copy, ...)
  - hold + move layer

- Numpad layer
  - no timer
  - numbers on the middle row
  - function keys on the top row
  - hold / one shot layer

- Symbol layer
  - no timer
  - shifted keys without shift required
  - hold / one shot layer
  - auto shift

- Adjust layer
  - no timer
  - media functions
  - keyboard maintenance

- Smart control modifier
  - space on tap but LCtrl on hold
  - enter on tap but RCtrl on hold

- Leader key sequence to input accentuated character
  - no timer
  - works on upper and lower character
  - e, u, i, c, y, a
  - direct access on default layer

- Combos
  - escape
  - del / backspace
  - app launcher
  - tabulation

- Swapper on one key
  - no timer
  - ctrl-tab
  - alt-tab

- Modtap for modifiers
  - shift on home row
  - alt / win / altgr on bottom row
  - ctrl on thumbs
  - no misfire that could occurs if all modifiers are on the home row

- Encoder support on left and right sides


## Other features

- Consistent hold / tap for modifiers
  - no timer
    - hold the trigger while tapping another key
      - send trigger + key
    - tap/release the trigger before hitting another key
      - queue the modifier for next non modifier key (sticky)
  - sticky modifiers
    - remain activated on layer switch
    - user defined entry point to select key that cancel queued modifiers
    - user defined entry point to selet key thatt does not affect queueing
