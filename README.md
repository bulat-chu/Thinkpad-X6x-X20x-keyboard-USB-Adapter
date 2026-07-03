### ThinkPad X6x/X20x Keyboard USB-C Adapter Project v0.1

This adapter is based on the RP2040 microcontroller and supports QMK firmware.

* QMK firmware source and build files: `<link-to-folder>`
* PCB layout and schematic: `<link-to-folder>`

**Schematic**
`<Circuit-scheme-file-link>`

**PCB layout**
`<PCB-layout-file-link>`

## Photos

`<photo-file-link>`

## Hints

### 1. Flashing new QMK firmware

To flash a new firmware (`.uf2` file):

1. Unplug the adapter from USB.
2. Press and hold the **CS# (Flash)** button on the adapter.
3. Plug the adapter into a USB port.
4. Release the button.
5. Copy the `.uf2` file to the `RPI-RP2` drive that appears. The firmware will be flashed automatically, and the adapter will reboot.
6. To verify that everything works correctly, run:

```bash
qmk console
```

### 2. Direct USB cable connection

You can connect a USB cable directly to the board using the following pads:

* `D-`
* `D+`
* `PWR (+5V)`
* `GND`

These pads are marked with arrows on the PCB.

### 3. Direct power button connection

Connect the laptop's power button cable to the `PWR SW` and `GND` pads.

These pads are marked with arrows on the PCB.

**Note:** `PWR SW` is **active low**. Pressing the keyboard power button shorts the `PWR SW` pad to `GND`.

Depending on the laptop model, the `PWR SW` pad may have approximately 3.3 V present even when the adapter is connected and the button is not pressed.
If required, you can replace the 0 Ω resistor next to the PWR SW pad with a resistor of a different value.
