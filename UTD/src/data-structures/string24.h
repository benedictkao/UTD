#pragma once

#include <iostream>
#include <stdint.h>

namespace utd {
  class string24 {
  private:
    static constexpr auto LARGE_STRING_FLAG{ static_cast<uint64_t>(1) << 63 };
    static constexpr auto SMALL_STRING_CAPACITY{ 22 };
    static constexpr auto SIZE_EXLUDING_DATA{ 16 };

    typedef char*           char_ptr;
    typedef const char*     c_string;
    typedef char&           char_ref;
    typedef const char&     const_char_ref;
    typedef const string24& const_string_ref;
    typedef string24&&      string_r_value;

    class small_string {
    private:
      static constexpr auto ARRAY_LENGTH{ SMALL_STRING_CAPACITY + 1 };

      char    _data[ARRAY_LENGTH];
      uint8_t _last_byte;

      void init(c_string, size_t);

      size_t size() const noexcept;

      void size(size_t);

      c_string c_str() const noexcept;

      char_ref charAt(size_t);

      const_char_ref charAt(size_t) const noexcept;

      friend class string24;
    };

    char_ptr _data;

    /*
     * For litte endian, max capacity is 2^63 - 1 since MSB has to be
     * used as flag. This means that max size is 2^63 -2.
     * 
     * TODO: fix behaviour for big endian
     */
    uint64_t _size;
    uint64_t _capacity;

  public:
    string24();

    string24(c_string);

    string24(const_string_ref);

    string24(string_r_value) noexcept;

    string24& operator=(const_string_ref);

    string24& operator=(string_r_value) noexcept;

    ~string24();

    size_t size() const noexcept;

    size_t capacity() const noexcept;

    c_string c_str() const noexcept;

  private:
    bool isLarge() const noexcept;

    void setLarge() noexcept;

    inline small_string* toSmall() noexcept;

    inline const small_string* toSmall() const noexcept;

  public:
    char_ref operator[](size_t);

    const_char_ref operator[](size_t) const noexcept;

  public:
    friend std::ostream& operator<<(std::ostream&, const string24&);
  };
} // namespace utd