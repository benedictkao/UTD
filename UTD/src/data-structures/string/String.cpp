
#include "String.h"

int utd::string::set_up(size_t size)
{
    _max_size = size + 1;
    _size = size;

    if (NULL == (_str_ptr = (char *)malloc(_max_size * sizeof(char))))
    {
        printf("Error malloc");
        return -1;
    }
    return 1;
}

int utd::string::resize(size_t size)
{
    _max_size = size + 1;
    _size = size;
    if (NULL == realloc(_str_ptr, _max_size * sizeof(char)))
    {
        printf("Error realloc");
        return -1;
    }
    return 1;
}

utd::string::string()
{
    set_up(0);
}

// from c string
utd::string::string(char *c_str)
{
    size_t count = 0;
    while (*(c_str + count) != '\0')
        count++;

    set_up(count);

    for (int i = 0; i < count; i++)
        _str_ptr[i] = c_str[i];
}

// from utd::string / Copy Constructor
utd::string::string(const string &str)
{
    // copy constructor called
    set_up(str.size());
    str.cpy(_str_ptr, _size);
}

// Move Constructor
utd::string::string(string &&str) noexcept
{
    // TODO: how to not expose
    str.move_str_ptr(_str_ptr);
    str.move_size(&_size);
}

/*
 * Destructor
 */
utd::string::~string()
{
    free(_str_ptr);
}

/*
 * Methods
 */
size_t utd::string::size()
{
    return _size;
}

const size_t utd::string::size() const
{
    return _size;
}

size_t utd::string::min(size_t a, size_t b)
{
    if (a < b)
        return a;
    return b;
}

const void utd::string::cpy(char *str, size_t str_size) const
{
    memcpy(str, _str_ptr, min(str_size, _size) * sizeof(char));
}

// must be immutable
const char *utd::string::c_str() const
{
    _str_ptr[_size] = '\0';
    return _str_ptr;
}

void utd::string::move_str_ptr(char *str_ptr)
{
    str_ptr = _str_ptr;
    _str_ptr = nullptr;
}

void utd::string::move_size(size_t *size)
{
    // do we need to null this ?
    *size = _size;
}
