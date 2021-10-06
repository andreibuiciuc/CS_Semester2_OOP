#pragma once
#include "../Domain/material.h"

/// \summary: Converts a string to an integer if possible.
/// \param string: a given string
/// \return: the number, -1 otherwise
int convert_to_numbers(char string[]);


/// \summary: Converts and validates the quantity.
/// \param price: the price as a string
/// \return: the price as an integer, -1 otherwise
int validate_quantity(char price[]);


/// \summary: Converts and validates the year.
/// \param year: the year as a string
/// \return: the year as an integer, -1 otherwise
int validate_year(char year[]);


/// \summary: Converts and validates the month.
/// \param month: the month as a string
/// \return: the month as an integer, -1 otherwise
int validate_month(char month[]);

/// \summary: Converts and validates the day.
/// \param day: the day as a string
/// \return: the day as an integer, -1 otherwise
int validate_day(char day[]);