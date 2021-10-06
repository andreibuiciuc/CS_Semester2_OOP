#pragma once

typedef struct {
    int year;
    int month;
    int day;
}Date;

typedef struct
{
    char name[50];
    char supplier[50];
    int quantity;
    Date expiration_date;

}Material;


/// \summary: Creates an expiration date.
/// \param year: a given year
/// \param month: a given month
/// \param day: a given day
/// \return: an expiration date of type Date
Date create_expiration_date(int year, int month, int day);


/// \summary: Creates a material.
/// \param name: a given name
/// \param supplier: a given supplier
/// \param quantity: a given quantity
/// \param expiration_date: a given expiration date
/// \return: a material of type Material
Material create_material(char name[], char supplier[], int quantity, Date expiration_date);


/// \summary: Sets the quantity.
/// \param material: a given material
/// \param value: a new value for the quantity
void set_quantity(Material* material, int value);


/// \summary: Creates a string with the material details.
/// \param material: a given material
/// \param str: a string with the material details.
void to_str(Material material, char str[]);


// char* get_name(Material* material);


// char* get_supplier(Material* material);


// int get_quantity(Material* material);


// Date get_expiration_date(Material* material);


// void set_name(Material* material, char value[]);


// void set_supplier(Material* material, char value[]);
