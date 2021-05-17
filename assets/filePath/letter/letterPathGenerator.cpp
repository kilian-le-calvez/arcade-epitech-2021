#include <iostream>
#include <vector>

int main() {
    std::string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    std::vector<std::string> content;
    std::string command;

    content.push_back("echo \'-SFML:(assets/ressources/sfml/letter/letter");
    content.push_back(".png):SFML-\n-SDL:(assets/ressources/sdl/letter/letter");
    content.push_back(".png):SDL-\n-NCURSES:(");
    content.push_back("):NCURSES-\'");
    
    for (std::size_t i = 0; i < letters.size(); i++) {
        command.clear();
        command += "touch ";
        command += letters[i];
        command += ".path";
        system(command.c_str());
        command.clear();
        for (std::size_t j = 0; j < content.size(); j++) {
            command += content[j];
            command += letters[i];
        }
        command.pop_back();
        command += " > ";
        command += letters[i];
        command += ".path";
        system(command.c_str());
    }
}