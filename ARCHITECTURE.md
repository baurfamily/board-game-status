# Board Game Status - Application Architecture

## System Overview

```
┌─────────────────────────────────────┐
│      ESP32 + TFT LCD (240x320)      │
│  ┌───────────────────────────────┐  │
│  │      Top Level Menu           │  │
│  │  ┌─────────────────────────┐  │  │
│  │  │ > Bidding               │  │  │
│  │  │   Win Tracker           │  │  │
│  │  │   Point Tracker         │  │  │
│  │  │   Regicide              │  │  │
│  │  └─────────────────────────┘  │  │
│  └───────────────────────────────┘  │
└─────────────────────────────────────┘
```

## Application State Flow

```
     ┌─────────┐
     │  MENU   │
     └────┬────┘
          │
    ┌─────┴─────┬──────────┬──────────┐
    │           │          │          │
┌───▼────┐  ┌──▼───┐  ┌───▼────┐  ┌──▼──────┐
│BIDDING │  │ WIN  │  │ POINT  │  │REGICIDE │
│        │  │TRACK │  │ TRACK  │  │         │
└───┬────┘  └──┬───┘  └───┬────┘  └──┬──────┘
    │           │          │          │
    └───────────┴──────────┴──────────┘
                │
            ┌───▼────┐
            │  MENU  │
            └────────┘
```

## Button Mapping

### In Menu (MENU state)
- **Button A / DOWN**: Navigate down through menu items
- **Button UP**: Navigate up through menu items
- **Button B**: Select highlighted menu item
- **Button BACK**: (no action in menu)

### In Bidding App
- **Button A**: Increment bid by 1 (only when unlocked)
- **Button B**: Lock bid (1st press) / Reset to 0 (2nd press)
- **Button BACK**: Return to menu

### In Win Tracker App
- **Button A**: Increment Player 1 wins
- **Button B**: Increment Player 2 wins
- **Button BACK**: Return to menu

### In Point Tracker App
- **Button A**: Increment Player 1 points
- **Button B**: Increment Player 2 points
- **Button BACK**: Return to menu

### In Regicide App
- **Button A**: Decrease health (damage)
- **Button B**: Increase health (heal)
- **Button BACK**: Return to menu

## Class Structure

```
┌─────────────────┐
│   TFT_eSPI      │  (Display driver)
└────────┬────────┘
         │
    ┌────┴──────┬──────────┬───────────┬──────────┐
    │           │          │           │          │
┌───▼────┐  ┌──▼────┐  ┌──▼─────┐  ┌──▼────┐  ┌─▼──────┐
│ Menu   │  │Bidding│  │  Win   │  │ Point │  │Regicide│
│        │  │ App   │  │Tracker │  │Tracker│  │  App   │
└────────┘  └───────┘  └────────┘  └───────┘  └────────┘
```

## Screen Layouts

### Menu Screen
```
╔════════════════════════╗
║   BOARD GAMES          ║
║                        ║
║ ┌────────────────────┐ ║
║ │ Bidding            │ ║ <- Selected (blue)
║ └────────────────────┘ ║
║   Win Tracker          ║
║   Point Tracker        ║
║   Regicide             ║
╚════════════════════════╝
```

### Bidding Screen
```
╔════════════════════════╗
║      BIDDING           ║
║                        ║
║                        ║
║      Bid: 5            ║ <- Large text
║                        ║
║                        ║
║       LOCKED           ║ <- Status (GREEN/YELLOW)
║                        ║
║                        ║
║ A: Increment  B: Lock  ║
║ BACK: Return to Menu   ║
╚════════════════════════╝
```

### Win Tracker Screen
```
╔════════════════════════╗
║   WIN TRACKER          ║
║                        ║
║   Player 1             ║
║      3                 ║ <- Win count
║                        ║
║   Player 2             ║
║      2                 ║ <- Win count
║                        ║
║                        ║
║ A: P1+  B: P2+  BACK   ║
╚════════════════════════╝
```

### Regicide Screen
```
╔════════════════════════╗
║     REGICIDE           ║
║                        ║
║ ┌────────────────────┐ ║
║ │████████████        │ ║ <- Health bar
║ └────────────────────┘ ║
║                        ║
║    HP: 35/50           ║
║                        ║
║                        ║
║ A: Damage  B: Heal     ║
║ BACK: Return to Menu   ║
╚════════════════════════╝
```

## Pin Configuration Summary

### Display (SPI)
| Function | GPIO Pin |
|----------|----------|
| MISO     | 19       |
| MOSI     | 23       |
| SCLK     | 18       |
| CS       | 15       |
| DC       | 2        |
| RST      | 4        |

### Buttons (Digital Input with Pull-up)
| Button   | GPIO Pin | Function                    |
|----------|----------|-----------------------------|
| A        | 25       | Action/Increment            |
| B        | 26       | Confirm/Lock/Secondary      |
| BACK     | 27       | Return to Menu              |
| UP       | 32       | Navigate Menu Up            |
| DOWN     | 33       | Navigate Menu Down          |

## Customization Guide

### Changing Button Pins
Edit `src/main.cpp`:
```cpp
const int BUTTON_A_PIN = 25;      // Your pin here
const int BUTTON_B_PIN = 26;      // Your pin here
// ... etc
```

### Changing Display Pins
Edit `platformio.ini`:
```ini
-D TFT_MISO=19    # Your pin here
-D TFT_MOSI=23    # Your pin here
// ... etc
```

### Changing Colors
Edit `src/app.cpp` and look for TFT color constants:
- `TFT_BLACK`
- `TFT_WHITE`
- `TFT_BLUE`
- `TFT_GREEN`
- `TFT_YELLOW`
- `TFT_RED`
- `TFT_CYAN`

### Adjusting Debounce Timing
Edit `src/main.cpp`:
```cpp
const unsigned long debounceDelay = 200;  // milliseconds
```
