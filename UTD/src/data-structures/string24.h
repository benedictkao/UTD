#pragma once

#include <iostream>
#include <stdint.h>

namespace utd {
  class string24 {
  private:
    static constexpr auto SMALL_STRING_MAX_SIZE{ 23 };
    static constexpr auto LARGE_STRING_FLAG{ 32 };
    static constexpr auto PADDING_4{ 4 };
    static constexpr auto PADDING_3{ 3 };
    static constexpr auto SIZE_EXLUDING_DATA{ 16 };

    typedef char*           char_ptr;
    typedef const char*     c_string;
    typedef char&           char_ref;
    typedef const char&     const_char_ref;
    typedef const string24& const_string_ref;
    typedef string24&&      string_r_value;

    class small_string {
    private:
      static constexpr auto SMALL_STRING_CAPACITY{ 24 };
      static constexpr auto REMAINING_CAPACITY_BIT_MASK{ 31 };

      char _data[SMALL_STRING_CAPACITY];

      void initEmpty();

      void init(c_string, size_t);

      size_t size() const noexcept;

      void size(uint8_t);

      c_string c_str() const noexcept;

      uint8_t remainingCapacity() const noexcept;

      char_ref charAt(size_t);

      const_char_ref charAt(size_t) const noexcept;

      friend class string24;
    };

    char_ptr _data;
    uint32_t _size;
    uint8_t  _first_padding[PADDING_4];
    uint32_t _capacity;
    uint8_t  _second_padding[PADDING_3];
    uint8_t  _flags;

  public:
    string24();

    string24(c_string);

    string24(const_string_ref);

    string24(string_r_value);

    string24& operator=(const_string_ref);

    string24& operator=(string_r_value);

    ~string24();

    size_t size() const noexcept;

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