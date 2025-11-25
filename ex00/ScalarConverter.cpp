#include "ScalarConverter.hpp"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cerrno>
#include <cmath>
#include <limits>
#include <cctype>

static bool isPseudo(const std::string &s)
{
    return (s == "nan" || s == "+inf" || s == "-inf" || s == "nanf" || s == "+inff" || s == "-inff");
}

static bool isCharLiteral(const std::string &s)
{
    return s.length() == 3 && s[0] == '\'' && s[2] == '\'';
}

void ScalarConverter::convert(const std::string &literal)
{
    std::cout << std::fixed << std::setprecision(1);

    if (isCharLiteral(literal)) // 'c' format, ifn strtod('a', ..) -> fail
    {
        char c = literal[1];

        std::cout << "char: '" << c << "'\n";
        std::cout << "int: " << static_cast<int>(c) << "\n";
        std::cout << "float: " << static_cast<float>(c) << "f\n";
        std::cout << "double: " << static_cast<double>(c) << "\n";
        return;
    }

    errno = 0;
    char *end = NULL;
    double d = std::strtod(literal.c_str(), &end);

    bool valid = (errno == 0 && (*end == '\0' || *end == 'f'));

    if (!valid && !isPseudo(literal))
    {
        std::cout << "Invalid literal: " << literal << "\n";
        return;
    }

    if (isPseudo(literal))
    {
        if (literal == "nan" || literal == "nanf")
            d = std::numeric_limits<double>::quiet_NaN();
        else if (literal == "+inf" || literal == "+inff")
            d = std::numeric_limits<double>::infinity();
        else if (literal == "-inf" || literal == "-inff")
            d = -std::numeric_limits<double>::infinity();
    }

    // Char
    if (std::isnan(d) || std::isinf(d) || d < 0 || d > 127)
        std::cout << "char: impossible\n";
    else if (!std::isprint(static_cast<char>(d)))
        std::cout << "char: Non displayable\n";
    else
        std::cout << "char: '" << static_cast<char>(d) << "'\n";

    // Int
    if (std::isnan(d) || std::isinf(d) || d < std::numeric_limits<int>::min() || d > std::numeric_limits<int>::max())
        std::cout << "int: impossible\n";
    else
        std::cout << "int: " << static_cast<int>(d) << "\n";

    // Float
    std::cout << "float: " << static_cast<float>(d) << "f\n";

    // Double
    std::cout << "double: " << d << "\n";
}
