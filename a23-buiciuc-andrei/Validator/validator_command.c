#include "validator_command.h"
#include "validator_material.h"

int validate_command(char cmd_str[]){
    int command;
    command = convert_to_numbers(cmd_str);
    return command;
}
