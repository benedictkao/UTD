#pragma once

#include <stdexcept>
#include <iterator>
#include <string.h>

size_t MinStringSize = 64;

namespace utd
{

    class string
    {

    private:
        char *_str_ptr;
        size_t _size;
        size_t _max_size;

        void set_up(size_t size)
        {
            _max_size = size + 1;
            _size = size; 
            _str_ptr = (char *)malloc(_max_size * sizeof(char));
        }

    public:
        /*
         * Constructors
         */

        // default
        string()
        {
            set_up(0);
        }

        // from c string
        string(char *c_str)
        {
            size_t count = 0;
            while (*(c_str + count) != '\0')
                count++;

            set_up(count);

            for (int i = 0; i < count; i++)
                _str_ptr[i] = c_str[i];
        }

        // from utd::string / Copy Constructor
        string(const string &str)
        {
            // copy constructor called
            set_up(str.size());
            str.cpy(_str_ptr, _size);
        }

        // Move Constructor
        string(string &&str) noexcept
        {
            // TODO: steal resource from str
        }

        // from iterator
        template <class InputIterator>
        string(InputIterator first, InputIterator last)
        {
            auto distance = std::distance(first, last);
            set_up(distance);
            size_t count = 0;
            while (first != last)
            {
                _str_ptr[count] = *first;
                first++;
                count++;
            }
        }

        /*
         * Destructor
         */
        ~string()
        {
            free(_str_ptr);
        }

        /*
         * Methods
         */
        size_t size()
        {
            return _size;
        }

        const size_t size() const
        {
            return _size;
        }

        static size_t min(size_t a, size_t b)
        {
            if (a < b)
                return a;
            return b;
        }

        const void cpy(char *str, size_t str_size) const
        {
            memcpy(str, _str_ptr, min(str_size, _size) * sizeof(char));
        }

        char &operator[](size_t idx)
        {
            if (idx < 0 || idx >= _size)
                throw std::range_error("Out of bounds");
            
            return _str_ptr[idx];
        }

        // must be immutable
        const char *c_str() const
        {
            _str_ptr[_size] = '\n';
            return _str_ptr;
        }
    };
}
