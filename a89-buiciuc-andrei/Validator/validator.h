#pragma once
#include <string>

class Validator{

public:
    static int convertToNumbers(const std::string& str);

    int validateMinutes(const std::string& minutesStr);

    int validateSeconds(const std::string& secondStr);

    int validateLikes(const std::string& likesStr);

    static void validateLink(std::string);

    static void validateTitle(const std::string& title);

    static void validatePresenter(const std::string& presenter);

    int validateCommand(const std::string& commandStr);
};