### ThinkPad X6x/X20x Keyboard USB-C Adapter Project v0.1

This adapter is based on the RP2040 microcontroller and supports QMK firmware.

Currently, only the JIS layout is supported.

Available to purchase on [`tindie`](https://www.tindie.com/products/43186)


**1. QMK firmware source and build files:**
[`Link-to-folder`](https://github.com/bulat-chu/Thinkpad-X6x-X20x-keyboard-USB-Adapter/tree/main/QMK-Firmware/keyboards/Thinkpad_X201_kbd_USB-C)

[`Modified suspend.c file fot ThinkPad like wakeup by pressing only Fn or Power button`](https://github.com/bulat-chu/Thinkpad-X6x-X20x-keyboard-USB-Adapter/blob/main/QMK-Firmware/platforms/suspend.c)

To create your own keyboard layout, edit the `keymap.c` file. The keyboard matrix (row/column mapping) is provided in the `table-*.txt` files.

**2. Schematic**
[`Circuit scheme file`](https://github.com/bulat-chu/Thinkpad-X6x-X20x-keyboard-USB-Adapter/blob/main/Scheme-PCB/Thinkpad_X201_kbd_USB-C-Scheme.pdf)

**3. PCB layout**
[`PCB layout - gerber files`](https://github.com/bulat-chu/Thinkpad-X6x-X20x-keyboard-USB-Adapter/tree/main/Scheme-PCB/PCB-manufacturing-files)

**4. PCB layout**
[`BOM`](https://github.com/bulat-chu/Thinkpad-X6x-X20x-keyboard-USB-Adapter/blob/main/Scheme-PCB/BOM_Thinkpad_X201_kbd_USB-C-Scheme.xlsx)


## Photos

<img width="3323" height="2467" alt="IMG_20261026_195923_1" src="https://github.com/user-attachments/assets/77983ad7-2e72-4ed1-8c8a-e2a483acea3c" />
<img width="3938" height="2141" alt="IMG_20261026_201020_1" src="https://github.com/user-attachments/assets/010f44a9-ec19-4114-89ca-d163ca009c7b" />


## Hints

### 1. If HID keys not working

Linux:

1. Download [`Linux-HWDB file`](https://github.com/bulat-chu/Thinkpad-X6x-X20x-keyboard-USB-Adapter/blob/main/driver-or-hwdb-file/99-thinkpad-x20x-kbd-usb-c.hwdb)

2. And put it into `/etc/udev/hwdb.d/`

3. Update hwdb:
`sudo systemd-hwdb update`
`sudo udevadm trigger`

Windows:
?

### 2. Flashing new QMK firmware

To flash a new firmware (`.uf2` file):

1. Unplug the adapter from USB.
2. Press and hold the **CS# (Flash)** button on the adapter.
3. Plug the adapter into a USB port.
4. Release the button.
5. Copy the `.uf2` file to the `RPI-RP2` drive that appears. The firmware will be flashed automatically, and the adapter will reboot.
6. To verify that everything works correctly, run and press any button:

```bash
qmk console
```

### 3. Direct USB cable connection

You can connect a USB cable directly to the board using the following pads:

* `D-`
* `D+`
* `PWR (+5V)`
* `GND`

On Green PCB these pads are marked with arrows on the PCB.

On Black PCB these pads are marked on the back side of the PCB.

### 3. Direct power button connection

Connect the laptop's power button cable to the `PWR SW` and `GND` pads.

On Green PCB these pads are marked with arrows on the PCB.

On Black PCB these pads are marked on the back side of the PCB.

**Note:** `PWR SW` is **active low**. Pressing the keyboard power button shorts the `PWR SW` pad to `GND`.

Depending on the laptop model, the `PWR SW` pad may have approximately 3.3 V present even when the adapter is connected and the button is not pressed.
If required, you can replace the 0 Ω resistor next to the PWR SW pad with a resistor of a different value.
