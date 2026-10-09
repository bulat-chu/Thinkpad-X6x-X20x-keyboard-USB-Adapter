This is a new revision of adapter.

Changes:

1. Added easier way to disable a MIC-MUTE-LED for X220 series keyboard.

2. Added easier way to change a POWER button input/output for X220 series keyboard (marked as VOL-LED 1 2 3). 

(pin "1" connected to LED-VOL-MUTE in keyboard connector. pin "2" connected to RP2040 GPIO4. pin "3" connected to PWRSWITCH on keyboard connector and "PWR SW" on PCB)

3. Fixed internal +3V3 connection (in the Green version it was fixed with a soldered wire)

4. Added dedicated USB pads

5. Changed PR2040 debug pads to one sided instead of double sided.

