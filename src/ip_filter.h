#pragma once   // #pragma once используется в качестве header guards, но имеет дополнительные преимущества — она короче и менее подвержена ошибкам.
               // Однако, #pragma once не является официальной частью языка C++, и не все
               // компиляторы её поддерживают (хотя большинство современных компиляторов поддерживают).
               // Я же рекомендую использовать header guards, чтобы сохранить максимальную совместимость вашего кода.
               /*
               Все ваши заголовочные файлы должны иметь header guards.
                'math.h'
               #ifndef MATH_H
               #define MATH_H

               int getSquareSides()
               {
                   return 4;
               }

               #endif
               */

// старые программы с
//#include <iostream.h> не нужно было переписывать, а новые программы уже могли использовать
//#include <iostream>
//Когда вы подключаете заголовочный файл из Стандартной библиотеки C++,
//убедитесь, что вы используете версию без .h (если она существует). В противном
//случае, вы будете использовать устаревшую версию заголовочного файла, который уже больше не поддерживается.
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <algorithm>
#include <tuple>

#include <cstddef>


// uint8_t  -  std::byte
using ip_address = std::array<uint8_t, 4>;
using ip_vector = std::vector<ip_address>;

class ip_parser_error : public std::exception
{
public:
    ip_parser_error() = default;
    ~ip_parser_error() override = default;
    const char* what() const noexcept override;
};

ip_address parse_ip(const std::string& str);

ip_vector filter(const ip_vector& ip_pool, uint8_t value);

ip_vector filter(const ip_vector& ip_pool, uint8_t value1, uint8_t value2);

ip_vector filter_any(const ip_vector& ip_pool, uint8_t value);

void print_ip_pool(const ip_vector& ip_pool) noexcept;
