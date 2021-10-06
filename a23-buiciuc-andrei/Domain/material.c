#include "material.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

Date create_expiration_date(int year, int month, int day){
    Date expiration_date;
    expiration_date.year = year;
    expiration_date.month = month;
    expiration_date.day = day;
    return expiration_date;
}

Material create_material(char name[], char supplier[], int quantity, Date expiration_date){
    Material material;
    strcpy(material.name, name);
    strcpy(material.supplier, supplier);
    material.quantity = quantity;
    material.expiration_date = expiration_date;

    return material;
}

void set_quantity(Material* material, int value){
    material->quantity = value;
}

void to_str(Material material, char str[]){
    sprintf(str, "%s - %s - %d - %d:%d:%d", material.name, material.supplier, material.quantity,
            material.expiration_date.day, material.expiration_date.month, material.expiration_date.year);
}


//char* get_name(Material* material){
//    return material->name;
//}
//
//char* get_supplier(Material* material){
//    return material->supplier;
//}
//
//int get_quantity(Material* material){
//    return material->quantity;
//}
//
//Date get_expiration_date(Material* material){
//    return material->expiration_date;
//}
//
//void set_name(Material* material, char value[]){
//    strcpy(material->name, value);
//}
//
//void set_supplier(Material* material, char value[]){
//    strcpy(material->supplier, value);
//}