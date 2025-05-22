#include <iostream>
#include "Assistant.h"

int main() {
    Assistant assistant;
    assistant.speak("Привет, меня зовут " + assistant.get_name() + "! Чем могу быть полезен?");

    return 0;
}