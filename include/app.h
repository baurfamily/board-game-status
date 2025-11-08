#ifndef APP_H
#define APP_H

#include <TFT_eSPI.h>

// App states
enum AppState {
    MENU,
    BIDDING,
    WIN_TRACKER,
    POINT_TRACKER,
    REGICIDE
};

// Menu class
class Menu {
private:
    TFT_eSPI* tft;
    int selectedItem;
    const int numItems = 4;
    const char* menuItems[4] = {"Bidding", "Win Tracker", "Point Tracker", "Regicide"};
    
public:
    Menu(TFT_eSPI* display);
    void draw();
    void selectNext();
    void selectPrevious();
    int getSelected();
    const char* getSelectedName();
};

// Bidding App class
class BiddingApp {
private:
    TFT_eSPI* tft;
    int currentBid;
    bool bidLocked;
    
public:
    BiddingApp(TFT_eSPI* display);
    void reset();
    void draw();
    void incrementBid();
    void toggleLock();
    bool isLocked();
};

// Win Tracker App class (placeholder)
class WinTrackerApp {
private:
    TFT_eSPI* tft;
    int player1Wins;
    int player2Wins;
    
public:
    WinTrackerApp(TFT_eSPI* display);
    void reset();
    void draw();
    void incrementPlayer1();
    void incrementPlayer2();
};

// Point Tracker App class (placeholder)
class PointTrackerApp {
private:
    TFT_eSPI* tft;
    int player1Points;
    int player2Points;
    
public:
    PointTrackerApp(TFT_eSPI* display);
    void reset();
    void draw();
    void incrementPlayer1();
    void incrementPlayer2();
    void decrementPlayer1();
    void decrementPlayer2();
};

// Regicide App class (placeholder)
class RegicideApp {
private:
    TFT_eSPI* tft;
    int health;
    int maxHealth;
    
public:
    RegicideApp(TFT_eSPI* display);
    void reset();
    void draw();
    void decrementHealth();
    void incrementHealth();
};

#endif // APP_H
