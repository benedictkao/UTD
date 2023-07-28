#pragma once

#include <iostream>
#include <stdint.h>

namespace utd {
  class string24 {
  private:
    static constexpr auto SMALL_STRING_MAX_SIZE{ 23 };
    static constexpr auto BITS_LARGE_FLAG{ 1 };

    static constexpr auto BITS_REMAINING_CAPACITY{ 5 };
    static constexpr auto BITS_UNUSED_SMALL_STRING{ 2 };

    typedef char*       char_ptr;
    typedef const char* const_char_ptr;

    class small_string {
    private:
      char    _data[SMALL_STRING_MAX_SIZE];
      bool    _large_flag : BITS_LARGE_FLAG;
      uint8_t _rem_capacity : BITS_REMAINING_CAPACITY;
      uint8_t _unused : BITS_UNUSED_SMALL_STRING;

      void init(const_char_ptr, size_t);

      size_t size() const noexcept;

      const_char_ptr c_str() const noexcept;

      friend class string24;
    };

    static constexpr auto BUFFER_SIZE{ 7 };
    static constexpr auto BITS_UNUSED_NORMAL_STRING{ 7 };

    char_ptr _data;
    uint32_t _size;
    uint32_t _capacity;
    uint8_t  _buffer[BUFFER_SIZE];
    bool     _large_flag : BITS_LARGE_FLAG;
    uint8_t  _unused : BITS_UNUSED_NORMAL_STRING;

  public:
    string24(const_char_ptr);

    size_t size() const noexcept;

    const_char_ptr c_str() const noexcept;

  private:
    inline small_string* toSmall() noexcept;

    inline const small_string* toSmall() const noexcept;

  public:
    friend std::ostream& operator<<(std::ostream&, const string24&);
  };
} // namespace utd