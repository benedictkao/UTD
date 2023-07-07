#pragma once

#include <stdint.h>
#include <iostream>

namespace utd {
	class string32 {
  public:
          enum STRING_TYPE { SMALL = '\0', LARGE };

	private:
		char* _data;
		uint64_t _size;
		uint64_t _capacity;
		uint64_t _unused = 0;

		uint8_t& getStringTypeFlag();

		uint8_t& getStringTypeFlag() const;

		bool isLargeString() const;

		void setType(STRING_TYPE);

	public:

		string32();

		string32(const char*);

		string32(const string32&);
		
		string32(string32&&) noexcept;
		
		string32& operator=(const string32&);

		string32& operator=(string32&&) noexcept;

		~string32();

		uint64_t size() const;

		uint64_t capacity() const;

		const char* c_str() const;

		void reserve(uint64_t);

		char& operator [](uint64_t);

        const char& operator[](uint64_t) const;

		string32 operator+(const string32&) const;

		string32& operator+=(const string32&);

		string32 operator+(const char&) const;

		string32& operator+=(const char&);

		friend bool operator==(const string32&, const string32&);

		friend std::ostream& operator<<(std::ostream&, const string32&);
	};
}