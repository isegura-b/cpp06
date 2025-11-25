#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <string>

class ScalarConverter
{
private:
    ScalarConverter();                        // No instantiation
    ScalarConverter(const ScalarConverter &); // this class does not save any data
    ScalarConverter &operator=(const ScalarConverter &);
    //~ScalarConverter();                                   // bc no instantiation, no need for destructor

public:
    static void convert(std::string const &literal);
};

#endif
