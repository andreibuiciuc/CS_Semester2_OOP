#include "customException.h"


CustomException::CustomException() = default;

CustomException::CustomException(const std::string& message) {
    this->message = message;
}

std::string CustomException::error() {
    return this->message;
}

ControllerException::ControllerException(const std::string& message):CustomException(message){}

ValidatorException::ValidatorException(const std::string &message):CustomException(message){}
