#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Screen;

class Cinema {
private:
    string name;
    vector<Screen> screens; // Composition: Cinema owns screens.

public:
    Cinema(string name) {
        this->name = name; // this keyword
    }

    void addScreen(const Screen& screen) { screens.push_back(screen); }
    string getName() const { return name; }
    vector<Screen>& getScreens() { return screens; }
    const vector<Screen>& getScreens() const { return screens; }
};
