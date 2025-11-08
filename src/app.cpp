#include "app.h"

// ==================== Menu Implementation ====================

Menu::Menu(TFT_eSPI* display) : tft(display), selectedItem(0) {}

void Menu::draw() {
    tft->fillScreen(TFT_BLACK);
    tft->setTextColor(TFT_WHITE, TFT_BLACK);
    tft->setTextSize(2);
    
    // Draw title
    tft->setCursor(50, 20);
    tft->println("BOARD GAMES");
    
    // Draw menu items
    for (int i = 0; i < numItems; i++) {
        int yPos = 70 + i * 50;
        
        if (i == selectedItem) {
            tft->fillRect(10, yPos - 5, 220, 40, TFT_BLUE);
            tft->setTextColor(TFT_WHITE, TFT_BLUE);
        } else {
            tft->setTextColor(TFT_WHITE, TFT_BLACK);
        }
        
        tft->setCursor(20, yPos + 5);
        tft->println(menuItems[i]);
    }
}

void Menu::selectNext() {
    selectedItem = (selectedItem + 1) % numItems;
    draw();
}

void Menu::selectPrevious() {
    selectedItem = (selectedItem - 1 + numItems) % numItems;
    draw();
}

int Menu::getSelected() {
    return selectedItem;
}

const char* Menu::getSelectedName() {
    return menuItems[selectedItem];
}

// ==================== Bidding App Implementation ====================

BiddingApp::BiddingApp(TFT_eSPI* display) : tft(display), currentBid(0), bidLocked(false) {}

void BiddingApp::reset() {
    currentBid = 0;
    bidLocked = false;
    draw();
}

void BiddingApp::draw() {
    tft->fillScreen(TFT_BLACK);
    tft->setTextColor(TFT_WHITE, TFT_BLACK);
    
    // Draw title
    tft->setTextSize(2);
    tft->setCursor(70, 20);
    tft->println("BIDDING");
    
    // Draw current bid
    tft->setTextSize(4);
    tft->setCursor(80, 100);
    tft->print("Bid: ");
    tft->println(currentBid);
    
    // Draw status
    tft->setTextSize(2);
    tft->setCursor(60, 180);
    if (bidLocked) {
        tft->setTextColor(TFT_GREEN, TFT_BLACK);
        tft->println("LOCKED");
    } else {
        tft->setTextColor(TFT_YELLOW, TFT_BLACK);
        tft->println("OPEN");
    }
    
    // Draw instructions
    tft->setTextSize(1);
    tft->setTextColor(TFT_CYAN, TFT_BLACK);
    tft->setCursor(20, 240);
    tft->println("A: Increment  B: Lock/Reset");
    tft->setCursor(20, 260);
    tft->println("BACK: Return to Menu");
}

void BiddingApp::incrementBid() {
    if (!bidLocked) {
        currentBid++;
        draw();
    }
}

void BiddingApp::toggleLock() {
    if (!bidLocked) {
        bidLocked = true;
    } else {
        // Second press: reset
        currentBid = 0;
        bidLocked = false;
    }
    draw();
}

bool BiddingApp::isLocked() {
    return bidLocked;
}

// ==================== Win Tracker App Implementation ====================

WinTrackerApp::WinTrackerApp(TFT_eSPI* display) : tft(display), player1Wins(0), player2Wins(0) {}

void WinTrackerApp::reset() {
    player1Wins = 0;
    player2Wins = 0;
    draw();
}

void WinTrackerApp::draw() {
    tft->fillScreen(TFT_BLACK);
    tft->setTextColor(TFT_WHITE, TFT_BLACK);
    
    // Draw title
    tft->setTextSize(2);
    tft->setCursor(40, 20);
    tft->println("WIN TRACKER");
    
    // Draw Player 1
    tft->setTextSize(3);
    tft->setCursor(20, 80);
    tft->println("Player 1");
    tft->setCursor(100, 120);
    tft->println(player1Wins);
    
    // Draw Player 2
    tft->setCursor(20, 180);
    tft->println("Player 2");
    tft->setCursor(100, 220);
    tft->println(player2Wins);
    
    // Draw instructions
    tft->setTextSize(1);
    tft->setTextColor(TFT_CYAN, TFT_BLACK);
    tft->setCursor(20, 280);
    tft->println("A: P1+  B: P2+  BACK: Menu");
}

void WinTrackerApp::incrementPlayer1() {
    player1Wins++;
    draw();
}

void WinTrackerApp::incrementPlayer2() {
    player2Wins++;
    draw();
}

// ==================== Point Tracker App Implementation ====================

PointTrackerApp::PointTrackerApp(TFT_eSPI* display) : tft(display), player1Points(0), player2Points(0) {}

void PointTrackerApp::reset() {
    player1Points = 0;
    player2Points = 0;
    draw();
}

void PointTrackerApp::draw() {
    tft->fillScreen(TFT_BLACK);
    tft->setTextColor(TFT_WHITE, TFT_BLACK);
    
    // Draw title
    tft->setTextSize(2);
    tft->setCursor(30, 20);
    tft->println("POINT TRACKER");
    
    // Draw Player 1
    tft->setTextSize(3);
    tft->setCursor(20, 80);
    tft->println("Player 1");
    tft->setCursor(100, 120);
    tft->println(player1Points);
    
    // Draw Player 2
    tft->setCursor(20, 180);
    tft->println("Player 2");
    tft->setCursor(100, 220);
    tft->println(player2Points);
    
    // Draw instructions
    tft->setTextSize(1);
    tft->setTextColor(TFT_CYAN, TFT_BLACK);
    tft->setCursor(20, 280);
    tft->println("A: P1+  B: P2+  BACK: Menu");
}

void PointTrackerApp::incrementPlayer1() {
    player1Points++;
    draw();
}

void PointTrackerApp::incrementPlayer2() {
    player2Points++;
    draw();
}

void PointTrackerApp::decrementPlayer1() {
    if (player1Points > 0) {
        player1Points--;
        draw();
    }
}

void PointTrackerApp::decrementPlayer2() {
    if (player2Points > 0) {
        player2Points--;
        draw();
    }
}

// ==================== Regicide App Implementation ====================

RegicideApp::RegicideApp(TFT_eSPI* display) : tft(display), health(50), maxHealth(50) {}

void RegicideApp::reset() {
    health = maxHealth;
    draw();
}

void RegicideApp::draw() {
    tft->fillScreen(TFT_BLACK);
    tft->setTextColor(TFT_WHITE, TFT_BLACK);
    
    // Draw title
    tft->setTextSize(2);
    tft->setCursor(60, 20);
    tft->println("REGICIDE");
    
    // Draw health bar background
    int barWidth = 200;
    int barHeight = 40;
    int barX = 20;
    int barY = 100;
    
    tft->drawRect(barX, barY, barWidth, barHeight, TFT_WHITE);
    
    // Draw health bar fill
    int fillWidth = (health * barWidth) / maxHealth;
    if (health > 0) {
        uint16_t color = TFT_GREEN;
        if (health < maxHealth / 3) {
            color = TFT_RED;
        } else if (health < (maxHealth * 2) / 3) {
            color = TFT_YELLOW;
        }
        tft->fillRect(barX + 2, barY + 2, fillWidth - 4, barHeight - 4, color);
    }
    
    // Draw health text
    tft->setTextSize(3);
    tft->setCursor(60, 170);
    tft->print("HP: ");
    tft->print(health);
    tft->print("/");
    tft->println(maxHealth);
    
    // Draw instructions
    tft->setTextSize(1);
    tft->setTextColor(TFT_CYAN, TFT_BLACK);
    tft->setCursor(20, 260);
    tft->println("A: Damage  B: Heal");
    tft->setCursor(20, 280);
    tft->println("BACK: Return to Menu");
}

void RegicideApp::decrementHealth() {
    if (health > 0) {
        health--;
        draw();
    }
}

void RegicideApp::incrementHealth() {
    if (health < maxHealth) {
        health++;
        draw();
    }
}
