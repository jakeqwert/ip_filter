#include "ip_filter.h"

const char* ip_parser_error::what() const noexcept
{
    return "Error during parsing ip address";
}

ip_address parse_ip(const std::string& str)
{
    ip_address addr;
    const char sep = '.';

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(sep);
    for (size_t i = 0; i < 4; i++)
    {
        addr[i] = static_cast<uint8_t>(stoul(str.substr(start, stop - start)));
        start = stop + 1;
        stop = str.find_first_of(sep, start);

        if (stop == std::string::npos && i != 2)  // i=2 нашли последнюю точку
            throw ip_parser_error();
    }

    return addr;
}

ip_vector filter(const ip_vector& ip_pool, uint8_t value)
{
    ip_vector pool;
    for (const auto& ip : ip_pool)
        if (ip[0] == value)
            pool.push_back(ip);

    return pool;
}

ip_vector filter(const ip_vector& ip_pool, uint8_t value1, uint8_t value2)
{
    ip_vector pool;
    for (const auto& ip : ip_pool)
        if (ip[0] == value1 && ip[1] == value2)
            pool.push_back(ip);

    return pool;
}

ip_vector filter_any(const ip_vector& ip_pool, uint8_t value)
{
    ip_vector pool;
    for (const auto& ip : ip_pool)
        if (std::any_of(ip.begin(), ip.end(), [value](uint8_t byte){ return byte == value; }))
            pool.push_back(ip);

    return pool;
}

void print_ip_pool(const ip_vector& ip_pool) noexcept
{
    for(const auto& ip : ip_pool)
    {
        for(const auto& byte : ip)
        {
            std::cout << unsigned(byte);

            if (&byte != &ip.back())
                std::cout << ".";
        }
        std::cout << std::endl;
    }
}


