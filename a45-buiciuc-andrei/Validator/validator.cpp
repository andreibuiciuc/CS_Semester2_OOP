#include "validator.h"
#include <iostream>

int Validator::convert_to_numbers(std::string str) {
    bool okay = true;
    int number = -1;

    for(int i = 0; i < str.length(); i ++){
        if(isdigit(str[i]) == false){
            okay = false;
            break;
        }
    }

    if(okay){
        /// Str is a number;
        number = std::stoi(str);
    }

    return number;
}

int Validator::validateMinutes(std::string minutesStr) {
    int minutes = this->convert_to_numbers(minutesStr); // -1 if not a number;
    if(minutes  > 59)
        minutes = -1;
    return minutes;
}

int Validator::validateSeconds(std::string secondsStr) {
    int seconds = this->convert_to_numbers(secondsStr);
    if(seconds > 59)
        seconds = -1;
    return seconds;

}

int Validator::validateLikes(std::string likesStr) {
    int likes = this->convert_to_numbers(likesStr);
    return likes;
}

bool Validator::validateLink(std::string link) {
    // First 12 letters: https://www. in order to have the structure of a link.
    std::string sample = "https://www.";
    std::string beginning = "";
    std::string::iterator it;
    int count = 0;
    for(it = link.begin(); it != link.end(); it ++){
        count += 1;
        beginning += *it;
        if(count == 12)
            break;
    }

    if(sample == beginning)
        return true;
    return false;
}

int Validator::validateCommand(std::string commandStr) {
    int command = this->convert_to_numbers(commandStr);
    return command;
}