#pragma once

#include <string>

#include <iostream>
#include <stdint.h>

namespace utd {

  class string24 {
  public:
  private:
    /*
     * Since last character of a string is always null (0), the last byte is
     * guaranteed to either be unused or have value of zero. This leaves us with
     * one byte (8 bits) of memory to use for boolean flags. However, all flag
     * values have to be false when data is stored in-situ otherwise the last
     * byte cannot be used as a null terminator if the small string capacity is
     * full
     */


    uint8_t _small_size = 0;     // 1 byte
    char    _data[7]    = { 0 }; // 7 bytes
    size_t  _size;               // 8 bytes ( 64 bit sys )
    char*   _ptr = nullptr;      // 8 bytes ( 64 bit sys )

    static constexpr uint8_t SMALL_STRING_MAX_LENGTH{ 7 + sizeof(size_t) +
                                                      sizeof(char*) };


    bool isLargeString() const;

    void setLargeString();

    void pointToInSituMemory();

    const char* data() const;

  public:
    string24();

    string24(const char*);

    string24(const string24&);

    string24(string24&&) noexcept;

    string24& operator=(const string24&);

    string24& operator=(string24&&) noexcept;

    ~string24();

    uint64_t size() const;

    bool empty() const;

    uint64_t capacity() const;

    const char* c_str() const;

    void reserve(uint64_t);

    char& operator[](uint64_t);

    const char& operator[](uint64_t) const;

    string24 operator+(const string24&) const;

    string24& operator+=(const string24&);

    string24 operator+(char) const;

    string24& operator+=(char);

    friend bool operator==(const string24&, const char*);

    friend bool operator==(const string24&, const string24&);

    friend std::ostream& operator<<(std::ostream&, const string24&);
  };
} // namespace utd
