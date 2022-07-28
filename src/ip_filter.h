#pragma once

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
