#include "endianness_codec.h"


class EndianCodec : public EndiannessCodec
{
public:
	uint8_t DecodeUInt8();	
	uint16_t DecodeUInt16();
	uint32_t DecodeUInt32();
	uint64_t DecodeUInt64();
	std::string DecodeStock();
	std::string DecodeASCII(const int size);
	std::string DecodeString(const int size);
private:
	void trim(char* str);
	char* rtrim(char* s);
};
