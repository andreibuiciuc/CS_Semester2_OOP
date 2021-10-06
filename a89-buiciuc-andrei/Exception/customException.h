#pragma once
#include <exception>
#include <string>

class CustomException: public std::exception {
protected:
    std::string message;

public:

    CustomException();

    explicit CustomException(const std::string& message);

    std::string error() ;
};

class ControllerException: public CustomException {
public:
    explicit ControllerException(const std::string& message);
};

class ValidatorException: public CustomException {
public:
    ValidatorException(const std::string& message);
};

