# board-game-status
A small embedded app that will show current status of a board game being played.

## Hardware Requirements
- ESP32 development board
- TFT LCD display (240x320, ILI9341 driver)
- 5 push buttons (A, B, BACK, UP, DOWN)

## Features

### Top Level Menu
Navigate through four different board game applications:
- **Bidding** - Track current bids with lock/reset functionality
- **Win Tracker** - Keep score of wins between two players
- **Point Tracker** - Track points for two players
- **Regicide** - Health tracking for the Regicide board game

### Bidding App
- Button A: Increment the current bid by 1
- Button B: Lock the bid (first press) or reset to 0 (second press)
- BACK: Return to menu

### Win Tracker App
- Button A: Increment Player 1 wins
- Button B: Increment Player 2 wins
- BACK: Return to menu

### Point Tracker App
- Button A: Increment Player 1 points
- Button B: Increment Player 2 points
- BACK: Return to menu

### Regicide App
- Button A: Decrease health (damage)
- Button B: Increase health (heal)
- BACK: Return to menu

## Button Wiring (Default Pins)
- Button A (Action): GPIO 25
- Button B (Confirm): GPIO 26
- Button BACK (Menu): GPIO 27
- Button UP (Navigate): GPIO 32
- Button DOWN (Navigate): GPIO 33

All buttons should be wired with pull-up resistors (or use internal pull-ups).

## TFT Display Wiring (Default Pins)
- MISO: GPIO 19
- MOSI: GPIO 23
- SCLK: GPIO 18
- CS: GPIO 15
- DC: GPIO 2
- RST: GPIO 4

## Building and Flashing

### Using PlatformIO
```bash
# Install PlatformIO if not already installed
pip install platformio

# Build the project
pio run

# Upload to ESP32
pio run --target upload

# Monitor serial output
pio device monitor
```

### Configuration
Modify `platformio.ini` to adjust:
- Display driver settings
- Pin configurations
- SPI frequency settings

## Customization
- Adjust button pins in `src/main.cpp`
- Modify display colors and layouts in `src/app.cpp`
- Change debounce delay for button sensitivity
