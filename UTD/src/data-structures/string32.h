#pragma once

#include <stdint.h>
#include <iostream>

namespace utd {

	class string32 {
	public:
   
	private:

          /*
		  * Since last character of a string is always null (0), the last byte is guaranteed to either be unused or have value of zero.
		  * This leaves us with one byte (8 bits) of memory to use for boolean flags. However, all flag values have to be false when data is stored in-situ
		  * otherwise the last byte cannot be used as a null terminator if the small string capacity is full
		  */
          char*            _data;
          size_t           _size;
          size_t           _capacity;
          char             _char_buffer[7] = { 0 };
          uint8_t          _flags;
		  
		  bool isLargeString() const;
		  
		  void setLargeString();
		  
		  void pointToInSituMemory();

	public:

		string32();

		string32(const char*);

		string32(const string32&);
		
		string32(string32&&) noexcept;
		
		string32& operator=(const string32&);

		string32& operator=(string32&&) noexcept;

		~string32();

		size_t size() const;

		bool empty() const;

		size_t capacity() const;

		const char* c_str() const;

		void reserve(size_t);

		char& operator[](size_t);

        const char& operator[](size_t) const;

		string32 operator+(const string32&) const;

		string32& operator+=(const string32&);

		string32 operator+(char) const;

		string32& operator+=(char);

		friend bool operator==(const string32&, const char*);

		friend bool operator==(const string32&, const string32&);

		friend std::ostream& operator<<(std::ostream&, const string32&);
	};
}

#include "string32.cpp"