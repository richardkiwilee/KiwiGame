#include "archive.h"

uint8_t ArchiveCodec::DecodeUInt8()
{
	uint8_t value;
	memcpy(&value, buffer.tail_, sizeof(value));
	buffer.tail_ += sizeof(value);
	return value;
}

uint16_t ArchiveCodec::DecodeUInt16()
{
	uint16_t value;
	memcpy(&value, buffer.tail_, sizeof(value));
	buffer.tail_ += sizeof(value);
	return value;
}

uint32_t ArchiveCodec::DecodeUInt32()
{
	uint32_t value;
	memcpy(&value, buffer.tail_, sizeof(value));
	buffer.tail_ += sizeof(value);
	return value;
}

uint64_t ArchiveCodec::DecodeUInt64()
{
	uint64_t value;
	memcpy(&value, buffer.tail_, sizeof(value));
	buffer.tail_ += sizeof(value);
	return value;
}

std::string ArchiveCodec::DecodeStock()
{ 
	char _stock[8];
	std::string _str;
	this->DecodeBytes((uint8_t*)_stock, 8);
	int i, j;
	for (i = 0; _stock[i];) {
		if (_stock[i] == '\n' || _stock[i] == '\r' || _stock[i] == '\t' || _stock[i] == 0x20) {
			for (j = i; _stock[j]; j++) {
				_stock[j] = '\0';
				_str = _stock;
				return _str;
			}
		}
		else i++;
	}
	_str = _stock;
	return _str;
};

void ArchiveCodec::trim(char * str)
{
	size_t len;
	int k, i;
	if (str == NULL)
		return;
	len = strlen(str);
	k = 0;
	for (i = 0; i<len; i++)
	{
		if ((str[i] != 0x20) && (str[i] != '\n'))
		{
			str[k] = str[i];
			k++;
		}
	}
	str[k] = '\0';
	return;
}

char * ArchiveCodec::rtrim(char * s)
{
	size_t i;
	if (s== NULL)
	{
		return (char*)NULL;
	}
	for (i = strlen(s); i > 0; i--)
	{
		if (s[i - 1] == 0x20 || s[i - 1] == '\t' || s[i - 1] == '\r' || s[i - 1] == '\n')
			s[i - 1] = '\0';
		else
			break;
	}
	return s;
}

std::string ArchiveCodec::DecodeASCII(const int size)
{
	char* _stock = new char[size];
	std::string _str;
	this->DecodeBytes((uint8_t*)_stock, size);
	int i, j;
	for (i = 0; _stock[i];) {
		if (_stock[i] == '\n' || _stock[i] == '\r' || _stock[i] == '\t' || _stock[i] == 0x20) {
			for (j = i; _stock[j]; j++) {
				_stock[j] = '\0';
				_str = _stock;
				return _str;
			}
		}
		else i++;
	}
	_str = _stock;
	return _str;
};

std::string ArchiveCodec::DecodeString(const int size)
{
	char* _stock = new char[size];
	std::string _str;
	this->DecodeBytes((uint8_t*)_stock, size);
	_str = this->rtrim(_stock);
	return _str;
}
