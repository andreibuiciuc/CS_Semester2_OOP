#pragma once

/// Converts and validates the user command.
/// \param cmd_str: the user command as a string
/// \return: the user command as an integer, -1 otherwise
int validate_command(char cmd_str[]);