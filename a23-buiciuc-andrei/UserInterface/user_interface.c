#include "user_interface.h"
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "../Validator/validator_material.h"
#include "../Validator/validator_command.h"
#include <stdlib.h>

UserInterface* create_user_interface(int repo_capacity){
    UserInterface* ui = (UserInterface*)malloc(sizeof(UserInterface));
    if(ui == NULL){
        return NULL;
    }

    ui->controller = create_controller(repo_capacity);
    ui->undo_controller = create_undo_controller(100, 100);
    return ui;
}


void destroy_user_interface(UserInterface* ui){
    // Free the controller.
    destroy_controller(ui->controller);
    // Free the undo_controller.
    destroy_undo_controller(ui->undo_controller);
    // Free the UI.
    free(ui);
}

void print_menu(){
    printf("\nHello and welcome to Bread'n Bagel. Choose a command below. \n");
    printf("1. Add a material.\n");
    printf("2. Delete a material. \n");
    printf("3. Update a material.\n");
    printf("4. Display materials past expiration date.\n");
    printf("5. Display all materials.\n");
    printf("6. Display short on supply.\n");
    printf("7. Undo.\n");
    printf("8. Redo.\n");
    printf("0. Exit\n");
}

void sub_menu(){
    printf("\na. Sort ascending by material name.");
    printf("\nb. Sort ascending by supplier.\n");
}

void menu_b(){
    printf("i. Display past expiration date.\n");
    printf("ii. Display from a given supplier.\n");
}

int add_material_ui(UserInterface* ui){
    int real_quantity, real_year, real_month, real_day;
    char name[50], supplier[50], quantity[10], year[10], month[10], day[10];
    Date expiration_date;

    printf("Enter the name of the material: ");
    scanf("%s", name);
    printf("Enter the supplier: ");
    scanf("%s", supplier);

    printf("Enter the quantity: ");
    scanf("%s", quantity);
    real_quantity = validate_quantity(quantity);
    if(real_quantity == -1){
        printf("Invalid input!");
        return 1;
    }

    printf("Enter the expiration date: ");
    printf("\nEnter the year:");
    scanf("%s", year);
    real_year = validate_year(year);
    if(real_year == -1){
        printf("Invalid input!");
        return 1;
    }

    printf("Enter the month: ");
    scanf("%s", month);
    real_month = validate_month(month);
    if(real_month == -1){
        printf("Invalid input!");
        return 1;
    }

    printf("Enter the day:");
    scanf("%s", day);
    real_day = validate_day(day);
    if(real_day == -1){
        printf("Invalid input!");
        return 1;
    }

    expiration_date = create_expiration_date(real_year, real_month, real_day);
    add_element(ui->controller, name, supplier, real_quantity, expiration_date);
    record(ui->undo_controller, ui->controller->repository);

    return 0;
}

int delete_material_ui(UserInterface* ui){
    int real_year, real_month, real_day;
    char name[50], supplier[50], year[10], month[10], day[10];
    Date expiration_date;
    printf("Enter the name of the material for removal: ");
    scanf("%s", name);
    printf("Enter the supplier: ");
    scanf("%s", supplier);

    printf("Enter the expiration date");
    printf("\nEnter the year:");
    scanf("%s", year);
    real_year = validate_year(year);
    if(real_year == -1){
        printf("Invalid input!");
        return 1;
    }

    printf("Enter the month: ");
    scanf("%s", month);
    real_month = validate_month(month);
    if(real_month == -1){
        printf("Invalid input!");
        return 1;
    }

    printf("Enter the day:");
    scanf("%s", day);
    real_day = validate_day(day);
    if(real_day == -1){
        printf("Invalid input!");
        return 1;
    }

    expiration_date = create_expiration_date(real_year, real_month, real_day);

    if(delete_element(ui->controller, name, supplier, expiration_date) == -1){
        printf("\nElement not found.");
    }
    else{
        printf("\nSuccessful removal.");
        record(ui->undo_controller, ui->controller->repository);
    }

    return 0;
}

int update_material_ui(UserInterface* ui){
    int real_year, real_month, real_day, real_quantity;
    char name[50], supplier[50], year[10], month[10], day[10], new_quantity[10];
    Date expiration_date;

    printf("Enter the name of the material for update: ");
    scanf("%s", name);
    printf("Enter the supplier: ");
    scanf("%s", supplier);

    printf("Enter the expiration date: ");
    printf("\nEnter the year:");
    scanf("%s", year);
    real_year = validate_year(year);
    if(real_year == -1){
        printf("Invalid input!");
        return 1;
    }

    printf("Enter the month: ");
    scanf("%s", month);
    real_month = validate_month(month);
    if(real_month == -1){
        printf("Invalid input!");
        return 1;
    }

    printf("Enter the day:");
    scanf("%s", day);
    real_day = validate_day(day);
    if(real_day == -1){
        printf("Invalid day");
        return 1;
    }

    expiration_date = create_expiration_date(real_year, real_month, real_day);

    printf("Enter the new quantity: ");
    scanf("%s", new_quantity);
    real_quantity = validate_quantity(new_quantity);
    if(real_quantity == -1){
        return 1;
    }

    if(update_element(ui->controller, name, supplier, expiration_date, real_quantity) == -1){
        printf("\nElement not found.");
    }
    else{
        printf("\nSuccessful update.");
        record(ui->undo_controller, ui->controller->repository);
    }

    return 0;
}

void display_all_materials(UserInterface* ui){
    Dynamic_Array material_list = ui->controller->repository->material_list;
    char str[50];
    printf("\n");
    for(int i=0; i<material_list.length; i++){
        to_str(material_list.elements[i], str);
        printf("%s", str);
        printf("\n");
    }
}


void display_past_expiration_date(UserInterface* ui){
    int okay = 0;
    char substring[50], str[50];
    printf("Enter a substring: ");
    scanf("%s", substring);

    // With this header: #include <time.h>
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    int year = tm.tm_year + 1900;
    int month = tm.tm_mon + 1;
    int day = tm.tm_mday;


    Dynamic_Array material_list = get_data(ui->controller->repository);
    for(int i = 0; i < material_list.length; i ++){
        Material material = material_list.elements[i];
        if(strstr(material.name, substring) != NULL || strstr(material.supplier, substring) != NULL || strcmp(substring, "...") == 0) {
            if (material.expiration_date.year < year) {
                to_str(material, str);
                printf("%s", str);
                printf("\n");
                okay = 1;
            } else if(material.expiration_date.year == year && material.expiration_date.month < month){
                to_str(material, str);
                printf("%s", str);
                printf("\n");
                okay = 1;
            } else if(material.expiration_date.year == year && material.expiration_date.month == month &&
                      material.expiration_date.day < day){
                to_str(material, str);
                printf("%s", str);
                printf("\n");
                okay = 1;
            }
        }
    }

    if(okay == 0){
        printf("No such materials");
    }
}

int display_sorted(UserInterface* ui){
    Material* materials_data = (Material*)malloc(ui->controller->repository->material_list.length * sizeof(Material));
    char substring[50], str[50], option[50], mini_option[3], supplier[50];
    int array_length = 0;

    menu_b();
    printf("Your option is: ");
    scanf("%s", mini_option);

    if(strcmp(mini_option, "i") != 0 && strcmp(mini_option, "ii") != 0){
        printf("Invalid input!");
        return 1;
    }

    if(strcmp(mini_option, "i") == 0) {
        sub_menu();
        printf("\nYour option is (name/supplier): ");
        scanf("%s", option);
        if ((strcmp(option, "name") != 0) && (strcmp(option, "supplier") != 0)) {
            printf("Invalid input");
            return 1;
        }

        printf("\nEnter a substring(... for empty string): ");
        scanf("%s", substring);
        printf("\n");

        array_length = elements_past_expiration(ui->controller, materials_data, substring);
        if (array_length == 0) {
            printf("No such elements.");
        } else {
            sort_elements_options(materials_data, array_length, option);
            for (int i = 0; i < array_length; i++) {
                to_str(materials_data[i], str);
                printf("%s", str);
                printf("\n");
            }
        }
    }
    else if(strcmp(mini_option, "ii") == 0){
        printf("Enter the supplier: ");
        scanf("%s", supplier);
        array_length = elements_from_a_supplier(ui->controller, materials_data, supplier);
        if(array_length == 0) {
            printf("No such elements.");
        }
        else{
            sort_elements_options(materials_data, array_length, "name");
            for(int i = 0; i < array_length; i ++){
                to_str(materials_data[i], str);
                printf("%s", str);
                printf("\n");
            }
        }
    }
    free(materials_data);
    return 0;
}

int display_short_in_supply(UserInterface* ui){
    Material* materials_data = (Material*)malloc(ui->controller->repository->material_list.length * sizeof(Material));
    int array_length = 0, real_quantity;
    char option[15];
    char str[50], quantity[50];


    printf("Enter the sort method (ascending / descending): ");
    scanf("%s", option);
    if(strcmp(option, "ascending") != 0 && strcmp(option, "descending") != 0){
        printf("Invalid input!");
        return 1;
    }

    printf("\nEnter a quantity value: ");
    scanf("%s", quantity);
    real_quantity = validate_quantity(quantity);
    if(real_quantity == -1){
        printf("Invalid input!");
        return 1;
    }

    array_length = elements_short_on_supply(ui->controller, materials_data, real_quantity);
    if(array_length == 0){
        printf("No such elements.");
        return 1;
    }
    else{
        sort_elements_options(materials_data, array_length, option);

        printf("\n");
        for(int i = 0; i < array_length; i ++){
            to_str(materials_data[i], str);
            printf("%s", str);
            printf("\n");
        }
    }

    free(materials_data);
    return 0;
}

int undo_ui(UserInterface* ui){
    int response;
    response = undo(ui->undo_controller, ui->controller->repository);

    if(response == -1){
        printf("No undos left.");
    }
    return 0;
}

int redo_ui(UserInterface* ui){
    int response;
    response = redo(ui->undo_controller, ui->controller->repository);

    if(response == -1){
        printf("No more redos left.");
    }
    return 0;
}

void start(UserInterface* ui){

    print_menu();
    int done = 0, command;
    char cmd_str[10];
    record(ui->undo_controller, ui->controller->repository);

    while(!done){
        printf("\nEnter your command: ");
        scanf("%s", cmd_str);
        command = validate_command(cmd_str);
        if(command == 1)
            add_material_ui(ui);
        else if(command == 2)
            delete_material_ui(ui);
        else if(command == 3)
            update_material_ui(ui);
        else if(command == 4)
            // display_past_expiration_date(ui);
            display_sorted(ui);
        else if(command == 5)
            display_all_materials(ui);
        else if(command == 6)
            display_short_in_supply(ui);
        else if(command == 7)
            undo_ui(ui);
        else if(command == 8)
            redo_ui(ui);
        else if(command == 0)
            done = 1;
        else
            printf("Bad command.");
    }
}

