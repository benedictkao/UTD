#pragma once

#include <stdexcept>
#include <iterator>
#include <string.h>

namespace utd
{

    class string
    {

    private:
        char *_str_ptr;
        size_t _size;
        size_t _max_size;

        int set_up(size_t);

        int resize(size_t);

    public:
        /*
         * Constructors
         */

        // default
        string();

        // from c string
        string(char *);

        // from utd::string / Copy Constructor
        string(const string &);

        // Move Constructor
        string(string &&) noexcept;

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
        };

        /*
         * Destructor
         */
        ~string();

        /*
         * Methods
         */
        size_t size();

        const size_t size() const;

        static size_t min(size_t, size_t);

        const void cpy(char *, size_t) const;

        char &operator[](size_t idx)
        {
            if (idx < 0 || idx >= _size)
                throw std::range_error("Out of bounds");

            return _str_ptr[idx];
        }

        string &operator+=(const string &str)
        {
            size_t original_size = size();
            size_t new_size = str.size() + original_size;

            if (new_size > _max_size && resize(new_size) == -1)
                throw std::runtime_error("Error resizing");

            str.cpy(_str_ptr + original_size, str.size());

            return *this;
        }

        const bool &operator==(const string &str) const
        {
            if (size() != str.size())
                return false;

            for (int i = 0; i < size(); i++)
            {
                if (str._str_ptr[i] != _str_ptr[i])
                    return false;
            }

            return true;
        }

        // must be immutable
        const char *c_str() const;

        void move_str_ptr(char *);

        void move_size(size_t *);
    };
}
