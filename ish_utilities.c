#include "ish_utilities.h"

char *ish_replace_first_character_in_cstring(
          char *string,
          char character,
          char replacement
      )
{
    for (char *cursor = string; *cursor; ++cursor) {
        if (*cursor == character) {
            *cursor =
                replacement;

            break;
        }
    }

    return string;
}

int ish_is_space(int character)
{
    int result =
        character == ' ' ||
            (unsigned int) character - '\t' < 5;

    return result;
}

int ish_is_digit(int character)
{
    int result =
        (unsigned int) character - '0' < 10;

    return result;
}

int ish_is_path_separator(int character)
{
    int result =
        character ==
            ISH_Path_Separator;

    return result;
}

int ish_is_lowercase(int character)
{
    int result =
        (unsigned int) character - 'a' < 26;

    return result;
}

int ish_is_uppercase(int character)
{
    int result =
        (unsigned int) character - 'A' < 26;

    return result;
}

int ish_convert_to_lowercase(int character)
{
    static const int Distance =
        'a' - 'A';

    if (ish_is_uppercase(character)) {
        character +=
            Distance;
    }

    return character;
}

int ish_convert_to_uppercase(int character)
{
    static const int Distance =
        'a' - 'A';

    if (ish_is_lowercase(character)) {
        character -=
            Distance;
    }

    return character;
}

char* ish_carve_token_in_cstring(
          char *string,
          int (*is_separator)(int character),
          char **cursor_after_token
      )
{
    char *result = 0;

    while (*string && is_separator(*string)) {
        ++string;
    }

    if (*string) {
        result =
            string;
    }

    while (*string && !is_separator(*string)) {
        ++string;
    }

    if (cursor_after_token) {
        *cursor_after_token = 0;
    }

    if (*string) {
        *(string++) = '\0';

        if (*string && cursor_after_token) {
            *cursor_after_token =
                string;
        }
    }

    return result;
}

char* ish_get_token_in_cstring(
          char *string,
          int (*is_separator)(int character),
          char **cursor_after_token
      )
{
    char *result = 0;

    while (*string && is_separator(*string)) {
        ++string;
    }

    if (*string) {
        result =
            string;
    }

    while (*string && !is_separator(*string)) {
        ++string;
    }

    if (cursor_after_token) {
        *cursor_after_token = 0;

        if (*string) {
            *cursor_after_token =
                string;
        }
    }

    return result;
}

int ish_cstring_starts_with(
        const char *prefix,
        const char *string
    )
{
    ish_check(prefix && string);

    while (*prefix) {
        if (*prefix++ != *string++) {
            return 0;
        };
    }

    return 1;
}

int ish_cstring_starts_with_ignoring_case(
        const char *prefix,
        const char *string
    )
{
    ish_check(prefix && string);

    while (*prefix) {
        if (ish_convert_to_lowercase(*prefix++) !=
                ish_convert_to_lowercase(*string++)) {
            return 0;
        };
    }

    return 1;
}

int ish_are_cstrings_equal(
        const char *string,
        const char *another_string
    )
{
    ish_check(string && another_string);

    while (*string && *string == *another_string) {
        ++string; ++another_string;
    }

    int result =
        *string == *another_string;

    return result;
}

int ish_are_cstrings_equal_ignoring_case(
        const char *string,
        const char *another_string
    )
{
    ish_check(string && another_string);

    while (*string &&
               ish_convert_to_lowercase(*string) ==
                   ish_convert_to_lowercase(*another_string)) {
        ++string; ++another_string;
    }

    int result =
        ish_convert_to_lowercase(*string) ==
            ish_convert_to_lowercase(*another_string);

    return result;
}

int ish_get_integer_from_cstring(const char *string)
{
    ish_check(string);

    int result = 0;

    while (ish_is_space(*string)) {
        ++string;
    }

    int negative = 0;
    switch (*string) {
        case '-':
            negative = 1;
        case '+':
            ++string;
    }

    while (ish_is_digit(*string)) {
        result =
            result * 10 + (*string - '0');
    }

    if (negative) {
        result =
            -result;
    }

    return result;
}