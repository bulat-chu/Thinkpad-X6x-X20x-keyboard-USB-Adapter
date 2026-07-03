# ThinkPad X201 Keyboard Adapter — QMK firmware

Кастомный адаптер клавиатуры ThinkPad X201 на базе RP2040.

---

## Маппинг пинов

### Матрица клавиатуры

| QMK row | GPIO | Сигнал разъёма |
|---------|------|----------------|
| 0       | GP0  | SENSE5         |
| 1       | GP1  | SENSE0         |
| 2       | GP2  | SENSE3         |
| 3       | GP3  | SENSE2         |
| 4       | GP5  | SENSE7         |
| 5       | GP6  | SENSE6         |
| 6       | GP7  | SENSE1         |
| 7       | GP8  | SENSE4         |

| QMK col | GPIO | Сигнал разъёма |
|---------|------|----------------|
| 0       | GP12 | DRV13          |
| 1       | GP13 | DRV15          |
| 2       | GP14 | DRV12          |
| 3       | GP15 | DRV14          |
| 4       | GP16 | DRV11          |
| 5       | GP17 | DRV0           |
| 6       | GP18 | DRV9           |
| 7       | GP19 | DRV1           |
| 8       | GP20 | DRV10          |
| 9       | GP21 | DRV2           |
| 10      | GP22 | DRV7           |
| 11      | GP23 | DRV3           |
| 12      | GP24 | DRV6           |
| 13      | GP25 | DRV8           |
| 14      | GP26 | DRV5           |
| 15      | GP27 | DRV4           |
| 16      | GP28 | HOTKEY         |

### TrackPoint (PS/2 bitbang)

| GPIO | Сигнал        |
|------|---------------|
| GP10 | TP4-DATA-3V3  |
| GP11 | TP4-CLK-3V3   |
| GP29 | TP4-RESET-3V3 |

### Прочее

| GPIO | Функция                       |
|------|-------------------------------|
| GP4  | PWRSWITCH (INPUT_PULLUP)      |
| GP9  | LED-CAPS-LOCK (OUTPUT, HIGH=on)|

---

## Сборка

```bash
# Скопировать папку в keyboards/tp_x201_adapter внутри QMK
cp -r tp_x201_adapter ~/qmk_firmware/keyboards/

# Собрать
qmk compile -kb tp_x201_adapter -km default

# Прошить (RP2040 в режиме BOOTSEL)
qmk flash -kb tp_x201_adapter -km default
```

---

## Восстановление матрицы клавиш

Текущий keymap содержит KC_TRNS во всех позициях.
Для определения раскладки:

1. Прошить debug-версию
2. Открыть консоль: `qmk console` или QMK Toolbox → Console
3. Нажимать каждую клавишу — в консоль выводится `KEY: row=X col=Y`
4. Заносить в таблицу и заполнять keymap.c

---

## Статус

- [x] Скелет проекта
- [x] GPIO маппинг
- [x] TrackPoint PS/2 config
- [x] LED Caps Lock
- [x] Debug вывод row/col
- [ ] Восстановление матрицы (прозвонка)
- [ ] Финальный keymap
- [ ] Кнопка питания (custom keycode)
