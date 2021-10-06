#include "test_validator.h"
#include "validator.h"
#include <assert.h>

void test_validator(){
    Validator* validator = new Validator;

    std::string s1 = "1234";
    int n1 = validator->convert_to_numbers(s1);
    assert(n1 == 1234);

    std::string s2 = "asd";
    int n2 = validator->convert_to_numbers(s2);
    assert(n2 == -1);

    std::string s3 = "0";
    int n3 = validator->convert_to_numbers(s3);
    assert(n3 == 0);

    std::string s4 = "40";
    int n4 = validator->validateMinutes(s4);
    assert(n4 == 40);

    std::string s5 = "67";
    int n5 = validator->validateMinutes(s5);
    assert(n5 == -1);

    std::string s6 = "40";
    int n6 = validator->validateSeconds(s6);
    assert(n6 == 40);

    std::string s7 = "67";
    int n7 = validator->validateSeconds(s7);
    assert(n7 == -1);

    std::string s8 = "1000";
    int n8 = validator->validateLikes(s8);
    assert(n8 == 1000);

    std::string s9 = "https://www.google.ro";
    bool n9 = validator->validateLink(s9);
    assert(n9 == true);

    std::string s10 = "asd";
    bool n10 = validator->validateLink(s10);
    assert(n10 == false);

    std::string s11 = "1";
    int n11 = validator->validateCommand(s11);
    assert(n11 == 1);

    delete validator;
}