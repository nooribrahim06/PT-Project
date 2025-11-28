#include "HelperFn.h"
bool IsValue(string input)
{   // checks if the input string is a double value
    // return true if it's double value, false otherwise
    // Double values can be: 12.5, -12.5, -23, -23. , -23.0 …etc.
    int idx = 0;
    if (input.empty()) {
        return false;
    }
    if (input[idx] == '+' || input[idx] == '-') {
        idx++;
        if (idx == input.length())
            return false;
    }
    bool isdig = false;
    bool isdot = false;
    for (idx; idx < input.length(); idx++)
    {
        if (isdigit(input[idx])) {
            isdig = true;
        }
        else if (input[idx] == '.') {
            if (isdot) {
                return false;
            }
            isdot = true;
        }
        else {
            return false;
        }
    }
    return isdig;
    //TODO: complete this function .done 
}
bool IsVariable(string input)
{
    // checks if the input string is a variable name
    // return true if it can be a variable name, false otherwise
    // Variable names must start with an alphabetic letter (small or capital) or an underscore (_). 
    // After the first initial letter, variable names can contain letters, numbers and underscores.  
    // No spaces or special characters, however, are allowed.
    int idx = 0;
    if (input.empty())
    {
        return false;
    }
    if (!(isalpha(input[idx]) || input[idx] == '_'))
    {
        return false;
    }
    bool valid = false;
    for (idx; idx < input.length(); idx++)
    {
        if (isalpha(input[idx]) || input[idx] == '_' || isdigit(input[idx])) {
            valid = true;
        }
        else return false;
    }
    return valid;
    //TODO: complete this function .done 
}
OpType ValueOrVariable(string input)
{// checks if the input string is a double value or a variable name
// chand returns enum "OpType" (the enum is declared in the .h)
//TODO: complete this function .done
    if (IsValue(input))
    {
        return VALUE_OP;
    }
    if (IsVariable(input))
    {
        return VARIABLE_OP;
    }
    return INVALID_OP;
}
