#include "validator_material.h"
#include <string.h>


int convert_to_numbers(char string[]){
    // Function that converts a numbers as a string into an integer
    // Return the number if valid, -1 otherwise
    int okay = 1, real_number = 0;
    char digits[11] = "0123456789";
    for(int i = 0; i < strlen(string); i ++){
        if(!strchr(digits, string[i])){
            okay = 0;
            break;
        }
        else{
            real_number = real_number * 10 + (string[i] - '0');
        }
    }

    if(okay == 0)
        real_number = -1;

    return real_number;
}

int validate_quantity(char quantity[]){
    // Quantity must be a positive integer.
    int real_quantity;
    real_quantity = convert_to_numbers(quantity);
    return real_quantity;
}

int validate_year(char year[]){
    // Year must be a positive integer, greater than 1900, only 4 digits..
    int real_year;
    real_year = convert_to_numbers(year);
    if(real_year < 1900 || real_year > 9999)
        return -1;

    return real_year;
}

int validate_month(char month[]){
    // Month must be a 2 digit positive integer between 1, 12.
    int real_month;
    real_month = convert_to_numbers(month);
    if(real_month <= 0 || real_month >= 13)
        return -1;

    return real_month;
}

int validate_day(char day[]){
    // Day must be a positive integer between 1 and 30
    int real_day;
    real_day = convert_to_numbers(day);
    if(real_day < 1 || real_day > 30)
        return  -1;

    return real_day;
}