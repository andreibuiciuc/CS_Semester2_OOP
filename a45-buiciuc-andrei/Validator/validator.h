#pragma once
#include <string>

class Validator{

public:

    int convert_to_numbers(std::string str);

    int validateMinutes(std::string minutesStr);

    int validateSeconds(std::string secondStr);

    int validateLikes(std::string likesStr);

    bool validateLink(std::string);

    int validateCommand(std::string commandStr);
};