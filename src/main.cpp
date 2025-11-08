#include <Arduino.h>
#include <TFT_eSPI.h>
#include "app.h"

// Display object
TFT_eSPI tft = TFT_eSPI();

// App objects
Menu menu(&tft);
BiddingApp biddingApp(&tft);
WinTrackerApp winTrackerApp(&tft);
PointTrackerApp pointTrackerApp(&tft);
RegicideApp regicideApp(&tft);

// Current app state
AppState currentState = MENU;

// Button pins (configure based on your hardware)
const int BUTTON_A_PIN = 25;      // Increment/Action button
const int BUTTON_B_PIN = 26;      // Lock/Confirm button
const int BUTTON_BACK_PIN = 27;   // Back/Menu button
const int BUTTON_UP_PIN = 32;     // Navigate up in menu
const int BUTTON_DOWN_PIN = 33;   // Navigate down in menu

// Debouncing variables
unsigned long lastButtonPressA = 0;
unsigned long lastButtonPressB = 0;
unsigned long lastButtonPressBack = 0;
unsigned long lastButtonPressUp = 0;
unsigned long lastButtonPressDown = 0;
const unsigned long debounceDelay = 200;

void setup() {
    Serial.begin(115200);
    Serial.println("Board Game Status - Starting...");
    
    // Initialize display
    tft.init();
    tft.setRotation(0); // Portrait mode (240x320)
    tft.fillScreen(TFT_BLACK);
    
    // Initialize button pins
    pinMode(BUTTON_A_PIN, INPUT_PULLUP);
    pinMode(BUTTON_B_PIN, INPUT_PULLUP);
    pinMode(BUTTON_BACK_PIN, INPUT_PULLUP);
    pinMode(BUTTON_UP_PIN, INPUT_PULLUP);
    pinMode(BUTTON_DOWN_PIN, INPUT_PULLUP);
    
    // Draw initial menu
    menu.draw();
    
    Serial.println("Setup complete!");
}

void handleMenuButtons() {
    unsigned long currentTime = millis();
    
    // Navigate down
    if (digitalRead(BUTTON_DOWN_PIN) == LOW || digitalRead(BUTTON_A_PIN) == LOW) {
        if (currentTime - lastButtonPressDown > debounceDelay) {
            lastButtonPressDown = currentTime;
            menu.selectNext();
            Serial.println("Menu: Down");
        }
    }
    
    // Navigate up
    if (digitalRead(BUTTON_UP_PIN) == LOW) {
        if (currentTime - lastButtonPressUp > debounceDelay) {
            lastButtonPressUp = currentTime;
            menu.selectPrevious();
            Serial.println("Menu: Up");
        }
    }
    
    // Select menu item
    if (digitalRead(BUTTON_B_PIN) == LOW) {
        if (currentTime - lastButtonPressB > debounceDelay) {
            lastButtonPressB = currentTime;
            int selected = menu.getSelected();
            
            Serial.print("Selected: ");
            Serial.println(menu.getSelectedName());
            
            switch (selected) {
                case 0:
                    currentState = BIDDING;
                    biddingApp.draw();
                    break;
                case 1:
                    currentState = WIN_TRACKER;
                    winTrackerApp.draw();
                    break;
                case 2:
                    currentState = POINT_TRACKER;
                    pointTrackerApp.draw();
                    break;
                case 3:
                    currentState = REGICIDE;
                    regicideApp.draw();
                    break;
            }
        }
    }
}

void handleBiddingButtons() {
    unsigned long currentTime = millis();
    
    // Increment bid (Button A)
    if (digitalRead(BUTTON_A_PIN) == LOW) {
        if (currentTime - lastButtonPressA > debounceDelay) {
            lastButtonPressA = currentTime;
            biddingApp.incrementBid();
            Serial.println("Bidding: Increment");
        }
    }
    
    // Lock/Reset bid (Button B)
    if (digitalRead(BUTTON_B_PIN) == LOW) {
        if (currentTime - lastButtonPressB > debounceDelay) {
            lastButtonPressB = currentTime;
            biddingApp.toggleLock();
            Serial.println("Bidding: Toggle Lock");
        }
    }
    
    // Return to menu
    if (digitalRead(BUTTON_BACK_PIN) == LOW) {
        if (currentTime - lastButtonPressBack > debounceDelay) {
            lastButtonPressBack = currentTime;
            currentState = MENU;
            menu.draw();
            Serial.println("Return to Menu");
        }
    }
}

void handleWinTrackerButtons() {
    unsigned long currentTime = millis();
    
    // Increment Player 1 (Button A)
    if (digitalRead(BUTTON_A_PIN) == LOW) {
        if (currentTime - lastButtonPressA > debounceDelay) {
            lastButtonPressA = currentTime;
            winTrackerApp.incrementPlayer1();
            Serial.println("Win Tracker: Player 1 +1");
        }
    }
    
    // Increment Player 2 (Button B)
    if (digitalRead(BUTTON_B_PIN) == LOW) {
        if (currentTime - lastButtonPressB > debounceDelay) {
            lastButtonPressB = currentTime;
            winTrackerApp.incrementPlayer2();
            Serial.println("Win Tracker: Player 2 +1");
        }
    }
    
    // Return to menu
    if (digitalRead(BUTTON_BACK_PIN) == LOW) {
        if (currentTime - lastButtonPressBack > debounceDelay) {
            lastButtonPressBack = currentTime;
            currentState = MENU;
            menu.draw();
            Serial.println("Return to Menu");
        }
    }
}

void handlePointTrackerButtons() {
    unsigned long currentTime = millis();
    
    // Increment Player 1 (Button A)
    if (digitalRead(BUTTON_A_PIN) == LOW) {
        if (currentTime - lastButtonPressA > debounceDelay) {
            lastButtonPressA = currentTime;
            pointTrackerApp.incrementPlayer1();
            Serial.println("Point Tracker: Player 1 +1");
        }
    }
    
    // Increment Player 2 (Button B)
    if (digitalRead(BUTTON_B_PIN) == LOW) {
        if (currentTime - lastButtonPressB > debounceDelay) {
            lastButtonPressB = currentTime;
            pointTrackerApp.incrementPlayer2();
            Serial.println("Point Tracker: Player 2 +1");
        }
    }
    
    // Return to menu
    if (digitalRead(BUTTON_BACK_PIN) == LOW) {
        if (currentTime - lastButtonPressBack > debounceDelay) {
            lastButtonPressBack = currentTime;
            currentState = MENU;
            menu.draw();
            Serial.println("Return to Menu");
        }
    }
}

void handleRegicideButtons() {
    unsigned long currentTime = millis();
    
    // Damage (Button A)
    if (digitalRead(BUTTON_A_PIN) == LOW) {
        if (currentTime - lastButtonPressA > debounceDelay) {
            lastButtonPressA = currentTime;
            regicideApp.decrementHealth();
            Serial.println("Regicide: Damage");
        }
    }
    
    // Heal (Button B)
    if (digitalRead(BUTTON_B_PIN) == LOW) {
        if (currentTime - lastButtonPressB > debounceDelay) {
            lastButtonPressB = currentTime;
            regicideApp.incrementHealth();
            Serial.println("Regicide: Heal");
        }
    }
    
    // Return to menu
    if (digitalRead(BUTTON_BACK_PIN) == LOW) {
        if (currentTime - lastButtonPressBack > debounceDelay) {
            lastButtonPressBack = currentTime;
            currentState = MENU;
            menu.draw();
            Serial.println("Return to Menu");
        }
    }
}

void loop() {
    // Handle button inputs based on current state
    switch (currentState) {
        case MENU:
            handleMenuButtons();
            break;
        case BIDDING:
            handleBiddingButtons();
            break;
        case WIN_TRACKER:
            handleWinTrackerButtons();
            break;
        case POINT_TRACKER:
            handlePointTrackerButtons();
            break;
        case REGICIDE:
            handleRegicideButtons();
            break;
    }
    
    // Small delay to prevent excessive polling
    delay(10);
}
