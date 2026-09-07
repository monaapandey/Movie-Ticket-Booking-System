#include <iostream>
#include <string>
using namespace std;

class Movie {
private:
    string title;
    string language;
    int duration;

public:
    // Compile-time polymorphism: overloaded constructors
    Movie() {
        title = "";
        language = "";
        duration = 0;
    }

    Movie(string title, string language, int duration) {
        this->title = title;          // this keyword
        this->language = language;
        this->duration = duration;
    }

    string getTitle() const {
        return title;
    }

    string getLanguage() const {
        return language;
    }

    int getDuration() const {
        return duration;
    }
};