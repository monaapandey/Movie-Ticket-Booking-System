#include <iostream>
#include <string>
using namespace std;

class Movie {
private:
    string title;
    string language;
    int duration;

public:
    Movie() : title(""), language(""), duration(0) {}

    // Compile-time polymorphism: overloaded constructors.
    Movie(string title, string language, int duration) {
        this->title = title;       // this keyword
        this->language = language;
        this->duration = duration;
    }

    string getTitle() const { return title; }
    string getLanguage() const { return language; }
    int getDuration() const { return duration; }
};
