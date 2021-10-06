#include "validator.h"
#include "../Exception/customException.h"

int Validator::convertToNumbers(const std::string& str) {
    bool okay = true;
    int number = -1;

    if(str.empty())
        return -1;

    for(char i : str){
        if(isdigit(i) == false){
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

void Validator::validateTitle(const std::string &title) {
    if(title.empty() || title.length() < 3)
        throw ValidatorException("Invalid title input.");
}

void Validator::validatePresenter(const std::string &presenter) {
    if(presenter.empty() || presenter.length() < 3)
        throw ValidatorException("Invalid presenter input.");
}

int Validator::validateMinutes(const std::string& minutesStr) {
    int minutes = this->convertToNumbers(minutesStr); // -1 if not a number;
    if(minutes  > 59)
        throw ValidatorException("Invalid minutes input.");
    return minutes;
}

int Validator::validateSeconds(const std::string& secondsStr) {
    int seconds = this->convertToNumbers(secondsStr);
    if(seconds > 59)
        throw ValidatorException("Invalid seconds input.");
    return seconds;
}

int Validator::validateLikes(const std::string& likesStr) {
    int likes = this->convertToNumbers(likesStr);
    if(likes == -1)
        throw ValidatorException("Invalid number of likes input.");
    return likes;
}

void Validator::validateLink(std::string link) {
    // First 12 letters: https://www. in order to have the structure of a link.
    std::string sample = "https://www.";
    std::string beginning;
    std::string::iterator it;
    int count = 0;
    for(it = link.begin(); it != link.end(); it ++){
        count += 1;
        beginning += *it;
        if(count == 12)
            break;
    }

    if(sample != beginning)
        throw ValidatorException("Invalid link input.");
}

int Validator::validateCommand(const std::string& commandStr) {
    int command = this->convertToNumbers(commandStr);
    return command;
}
