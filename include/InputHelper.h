#ifndef INPUTHELPER_H
#define INPUTHELPER_H

#include <string>
#include <vector>

// provides input and validation functions used throughout the program :)
namespace InputHelper {

    // removes extra spaces from the beginning and end of a string
    std::string Trim(const std::string& text);
    // splits a line into smaller strings using the given delimiter
    std::vector<std::string> Split(const std::string& line, char delimiter);

    // checks that the input contains only digits and is a positive integer
    // rejects signs, spaces inside the number, and values that are too large
    bool ParsePositiveInt(const std::string& text, int& value);
    // accepts resource ids like "R101", "r101", or "101" and returns 101
    bool ParseResourceId(const std::string& text, int& value);
    // checks that a date is valid MM/DD/YYYY
    bool IsValidDate(const std::string& text);
    // converts a resource ID like 101 -> "R101"
    std::string FormatResourceId(int id);

    // displays a prompt and reads a line of user input
    bool ReadLine(const std::string& prompt, std::string& out);
    // reads input and makes sure the user does not enter a empty line
    bool ReadNonEmptyLine(const std::string& prompt, std::string& out);
    // prompts the user to enter a valid positive integer
    bool ReadPositiveInt(const std::string& prompt, int& out);
    //prompts the user to enter a valid resource id
    bool ReadResourceId(const std::string& prompt, int& out);
    // prompts the user to enter a valid date
    bool ReadDate(const std::string& prompt, std::string& out);
}

#endif