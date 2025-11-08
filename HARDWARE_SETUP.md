# Hardware Setup Guide

## Required Components

1. **ESP32 Development Board** (e.g., ESP32-DevKitC, ESP32-WROOM-32)
2. **TFT LCD Display** - 240x320 pixels with ILI9341 driver
3. **Push Buttons** - 5x tactile push buttons
4. **Resistors** - 5x 10kΩ pull-up resistors (if not using internal pull-ups)
5. **Breadboard and Jumper Wires**
6. **USB Cable** for programming

## Wiring Diagram

### TFT Display to ESP32

```
TFT Display          ESP32
─────────────────────────────
VCC         ────────> 3.3V
GND         ────────> GND
CS          ────────> GPIO 15
RESET       ────────> GPIO 4
DC/RS       ────────> GPIO 2
SDI/MOSI    ────────> GPIO 23
SCK         ────────> GPIO 18
LED         ────────> 3.3V (backlight)
SDO/MISO    ────────> GPIO 19
```

### Push Buttons to ESP32

Each button should be wired as follows:

```
        3.3V
         │
         ├── 10kΩ Resistor (optional if using internal pull-up)
         │
         ├────────────> GPIO Pin
         │
      [Button]
         │
        GND
```

**Button Connections:**
```
Button A (Action)    ────────> GPIO 25
Button B (Confirm)   ────────> GPIO 26
Button BACK (Menu)   ────────> GPIO 27
Button UP (Navigate) ────────> GPIO 32
Button DOWN (Navigate)───────> GPIO 33
```

## Connection Tables

### Display Connection Table

| TFT Pin | Function | ESP32 GPIO | Notes |
|---------|----------|------------|-------|
| VCC     | Power    | 3.3V       | Do NOT use 5V |
| GND     | Ground   | GND        | Common ground |
| CS      | Chip Select | GPIO 15 | SPI Chip Select |
| RESET   | Reset    | GPIO 4     | Display Reset |
| DC/RS   | Data/Command | GPIO 2 | Command mode select |
| MOSI    | Data Out | GPIO 23    | SPI MOSI |
| SCK     | Clock    | GPIO 18    | SPI Clock |
| LED     | Backlight| 3.3V       | Through 100Ω resistor |
| MISO    | Data In  | GPIO 19    | SPI MISO (optional) |

### Button Connection Table

| Button Name | Function | ESP32 GPIO | Pull-up Mode |
|-------------|----------|------------|--------------|
| A           | Action/Increment | GPIO 25 | INPUT_PULLUP |
| B           | Confirm/Lock | GPIO 26 | INPUT_PULLUP |
| BACK        | Return to Menu | GPIO 27 | INPUT_PULLUP |
| UP          | Menu Navigate Up | GPIO 32 | INPUT_PULLUP |
| DOWN        | Menu Navigate Down | GPIO 33 | INPUT_PULLUP |

## Assembly Steps

### Step 1: Connect the Display
1. Connect all display pins according to the table above
2. Ensure proper 3.3V power supply (NOT 5V)
3. Add a 100Ω resistor in series with the LED pin for backlight protection
4. Double-check all connections before powering on

### Step 2: Connect the Buttons
1. Wire each button with one side to the assigned GPIO pin
2. Connect the other side of each button to GND
3. If not using internal pull-ups, add 10kΩ resistors between 3.3V and each GPIO pin
4. Verify no shorts between adjacent pins

### Step 3: Power Supply
1. Connect USB cable to ESP32 for programming and power
2. Ensure stable 3.3V supply for the display
3. Total current draw should be under 500mA

## Verification Steps

### Before Programming
1. **Visual Inspection**
   - Check all connections match the wiring diagram
   - Verify no crossed wires or shorts
   - Ensure power and ground are correct

2. **Continuity Test**
   - Use multimeter to verify connections
   - Check for shorts between power and ground
   - Verify button connections

### After Programming
1. **Initial Boot**
   - Display should initialize (may flash briefly)
   - Menu should appear on screen
   - Serial monitor should show "Board Game Status - Starting..."

2. **Button Test**
   - Press each button and verify response
   - Check serial monitor for button press logs
   - Verify menu navigation works

3. **App Test**
   - Select each app from menu
   - Test functionality in each app
   - Verify return to menu works

## Troubleshooting

### Display Issues

**Problem: Display is blank**
- Check power connections (3.3V and GND)
- Verify CS, DC, and RESET pins are connected
- Check SPI pins (MOSI, SCK)
- Verify display is receiving proper voltage

**Problem: Display shows garbage/noise**
- Check SPI clock frequency in platformio.ini
- Verify proper grounding
- Check for loose connections
- Try different SPI pins if available

**Problem: Display colors are wrong**
- Verify correct display driver (ILI9341)
- Check BGR/RGB setting in TFT_eSPI configuration

### Button Issues

**Problem: Buttons not responding**
- Check button is pressed (multimeter continuity test)
- Verify GPIO pin connections
- Check pull-up resistors or internal pull-up configuration
- Verify button is wired to GND when pressed

**Problem: Multiple button presses detected**
- Increase debounce delay in main.cpp
- Check for button bounce (mechanical issue)
- Add capacitor (0.1µF) across button terminals

### ESP32 Issues

**Problem: ESP32 won't program**
- Press and hold BOOT button during upload
- Check USB cable and drivers
- Verify correct board selected in platformio.ini
- Try different USB port

**Problem: Device resets/crashes**
- Check power supply stability
- Verify no shorts in wiring
- Check serial monitor for error messages
- Reduce SPI frequency if display timing is issue

## Alternative Pin Configurations

If the default pins conflict with other peripherals, you can modify the pin assignments:

### Alternative Display Pins
Edit `platformio.ini`:
```ini
-D TFT_MISO=12
-D TFT_MOSI=13
-D TFT_SCLK=14
-D TFT_CS=5
-D TFT_DC=21
-D TFT_RST=22
```

### Alternative Button Pins
Edit `src/main.cpp`:
```cpp
const int BUTTON_A_PIN = 34;      // Use any available GPIO
const int BUTTON_B_PIN = 35;
const int BUTTON_BACK_PIN = 36;
const int BUTTON_UP_PIN = 39;
const int BUTTON_DOWN_PIN = 13;
```

**Note:** Avoid using:
- GPIO 0 (BOOT button)
- GPIO 1 (TX)
- GPIO 3 (RX)
- GPIO 6-11 (Flash memory)

## Safety Notes

⚠️ **Important Safety Information:**

1. **Never apply 5V to the display** - ESP32 and most TFT displays are 3.3V devices
2. **Check polarity** before connecting power
3. **Avoid static discharge** - Use ESD protection when handling
4. **Disconnect power** before changing wiring
5. **Use current-limited power supply** - Protect against shorts

## Power Consumption

Typical power consumption:
- ESP32: ~80-240mA (depending on WiFi/BT usage)
- TFT Display: ~50-150mA (depending on brightness and content)
- Total: ~200-400mA typical operation

USB port can provide up to 500mA, which is sufficient for this project.

## Next Steps

After assembly:
1. Flash the firmware using `pio run --target upload`
2. Open serial monitor using `pio device monitor`
3. Test each feature systematically
4. Adjust debounce timing if needed
5. Customize for your specific board game needs
