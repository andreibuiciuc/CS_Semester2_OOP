#include "test_validator.h"
#include "validator_material.h"
#include "validator_command.h"
#include <assert.h>


void test_convert_to_numbers(){
    char string1[5] = "1234";
    int number1 = convert_to_numbers(string1);
    assert(number1 == 1234);

    char string2[2] = "2";
    int number2 = convert_to_numbers(string2);
    assert(number2 == 2);

    char string3[2] = "0";
    int number3 = convert_to_numbers(string3);
    assert(number3 == 0);

    char string4[5] = "-234";
    int number4 = convert_to_numbers(string4);
    assert(number4 == -1);

    char string5[5] = "1a34";
    int number5 = convert_to_numbers(string5);
    assert(number5 == -1);
}


void test_validate_quantity(){
    char string1[5] = "1234";
    int number1 = validate_quantity(string1);
    assert(number1 == 1234);

    char string2[2] = "2";
    int number2 = validate_quantity(string2);
    assert(number2 == 2);

    char string3[2] = "0";
    int number3 = validate_quantity(string3);
    assert(number3 == 0);

    char string4[5] = "-234";
    int number4 = validate_quantity(string4);
    assert(number4 == -1);

}


void test_validate_year_month_day(){
    char string1[5] = "2001";
    int year1 = validate_year(string1);
    assert(year1 == 2001);

    char string2[5] = "1700";
    int year2 = validate_year(string2);
    assert(year2 == -1);

    char string3[6] = "12345";
    int year3 = validate_year(string3);
    assert(year3 == -1);

    char string4[2] = "5";
    int month1 = validate_month(string4);
    assert(month1 == 5);

    char string5[3] = "12";
    int month2 = validate_month(string5);
    assert(month2 == 12);

    char string6[3] = "13";
    int month3 = validate_month(string6);
    assert(month3 == -1);

    char string7[2] = "5";
    int day1 = validate_day(string7);
    assert(day1 == 5);

    char string8[3] = "30";
    int day2 = validate_day(string8);
    assert(day2 == 30);

    char string9[3] = "32";
    int day3 = validate_day(string9);
    assert(day3 == -1);
}

void test_validate_command(){
    char comm1[2] = "0";
    int command1 = validate_command(comm1);
    assert(command1 == 0);

    char comm2[5] = "abbe";
    int command2 = validate_command(comm2);
    assert(command2 == -1);

}

void test_validator(){
    test_convert_to_numbers();
    test_validate_quantity();
    test_validate_year_month_day();
    test_validate_command();
}
