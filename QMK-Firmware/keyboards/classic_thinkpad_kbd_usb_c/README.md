# Classic ThinkPad Keyboard Adapter (X6x X20x X220) — QMK Firmware

A custom keyboard adapter based on the RP2040.

---

## Pin Mapping

### Keyboard Matrix X6x X20x

| QMK row | GPIO | Connector Signal |
|---------|------|------------------|
| 0       | GP0  | SENSE5           |
| 1       | GP1  | SENSE0           |
| 2       | GP2  | SENSE3           |
| 3       | GP3  | SENSE2           |
| 4       | GP5  | SENSE7           |
| 5       | GP6  | SENSE6           |
| 6       | GP7  | SENSE1           |
| 7       | GP8  | SENSE4           |

| QMK col | GPIO | Connector Signal |
|---------|------|------------------|
| 0       | GP12 | DRV13            |
| 1       | GP13 | DRV15            |
| 2       | GP14 | DRV12            |
| 3       | GP15 | DRV14            |
| 4       | GP16 | DRV11            |
| 5       | GP17 | DRV0             |
| 6       | GP18 | DRV9             |
| 7       | GP19 | DRV1             |
| 8       | GP20 | DRV10            |
| 9       | GP21 | DRV2             |
| 10      | GP22 | DRV7             |
| 11      | GP23 | DRV3             |
| 12      | GP24 | DRV6             |
| 13      | GP25 | DRV8             |
| 14      | GP26 | DRV5             |
| 15      | GP27 | DRV4             |
| 16      | GP28 | HOTKEY            |

### TrackPoint (PS/2 Bit-Banging)

| GPIO | Signal        |
|------|---------------|
| GP10 | TP4-DATA-3V3  |
| GP11 | TP4-CLK-3V3   |
| GP29 | TP4-RESET-3V3 |

### Other Connections

| GPIO | Function                        |
|------|---------------------------------|
| GP4  | PWRSWITCH (INPUT_PULLUP)        |
| GP9  | LED-CAPS-LOCK (OUTPUT) |

---

## Building

```bash
# Copy the folder to keyboards/classic_thinkpad_kbd_usb_c inside the QMK repository
cp -r classic_thinkpad_kbd_usb_c ~/qmk_firmware/keyboards/

# Compile
qmk compile -kb classic_thinkpad_kbd_usb_c -km default

# Flash (RP2040 in BOOTSEL mode)
qmk flash -kb classic_thinkpad_kbd_usb_c -km default
```

---
