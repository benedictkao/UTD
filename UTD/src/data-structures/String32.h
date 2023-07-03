#pragma once

#include <stdint.h>

namespace utd {
	class string32 {
	private:
		char* _data;
		uint64_t _size;
		uint64_t _capacity;
		uint64_t _unused = 0;

		enum STRING_TYPE { SMALL = '\0', LARGE };

		uint8_t& getStringTypeFlag();

		uint8_t& getStringTypeFlag() const;

		bool isLargeString() const;

		void setType(STRING_TYPE type);

	public:

		string32(const char*);

		~string32();

		uint64_t size() const;
	};
}