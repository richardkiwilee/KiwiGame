#ifndef ENDIANNESS_CODEC_H
#define ENDIANNESS_CODEC_H
#include <cstring>
#include <iostream>
#include <cstdint>
#include <string>

#define INITIAL_MSG_SIZE  4194304	//4M

class CodecBuffer
{
public:
	CodecBuffer(void);
	virtual ~CodecBuffer(void);

	void MallocBuffer(int length = INITIAL_MSG_SIZE);
	void ResetBuffer(uint8_t* bytes, int length);
	void RiseBuffer();

	int		Get_Buffer_Used();
	int		Get_Buffer_Left();
	int		Get_Buffer_Size();
	int		IsBufferEmpty();
	void	CopyTo(uint8_t* buffer);
	uint8_t* Data() { return data_; }
	void  PrintBuffer();

	uint8_t* head_;
	uint8_t* tail_;
	uint8_t* end_;
private:

	uint8_t* data_;
};

class Endianness
{

public:
    //! Byte swap unsigned short
    static uint16_t swap_uint16(uint16_t val)
    {
        return (val << 8) | (val >> 8);
    }

    //! Byte swap short
    static int16_t swap_int16(int16_t val)
    {
        return (val << 8) | ((val >> 8) & 0xFF);
    }

    //! Byte swap unsigned int
    static uint32_t swap_uint32(uint32_t val)
    {
        val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
        return (val << 16) | (val >> 16);
    }

    //! Byte swap int
    static int32_t swap_int32(int32_t val)
    {
        val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
        return (val << 16) | ((val >> 16) & 0xFFFF);
    }

    static int64_t swap_int64(int64_t val)
    {
        val = ((val << 8) & 0xFF00FF00FF00FF00ULL) | ((val >> 8) & 0x00FF00FF00FF00FFULL);
        val = ((val << 16) & 0xFFFF0000FFFF0000ULL) | ((val >> 16) & 0x0000FFFF0000FFFFULL);
        return (val << 32) | ((val >> 32) & 0xFFFFFFFFULL);
    }

    static uint64_t swap_uint64(uint64_t val)
    {
        val = ((val << 8) & 0xFF00FF00FF00FF00ULL) | ((val >> 8) & 0x00FF00FF00FF00FFULL);
        val = ((val << 16) & 0xFFFF0000FFFF0000ULL) | ((val >> 16) & 0x0000FFFF0000FFFFULL);
        return (val << 32) | (val >> 32);
    }
};

class EndiannessCodec
{
public:
	EndiannessCodec(void);
	virtual ~EndiannessCodec(void);
 
	CodecBuffer buffer;
	void InitEncoder(int32_t length=INITIAL_MSG_SIZE);
	void InitEncoder(uint8_t* bytes,int length);
	void EncodeInt8(int8_t value);
	void EncodeInt16(int16_t value);
	void EncodeUInt16(uint16_t value);
	void EncodeInt32(int32_t value);
	void EncodeUInt32(uint32_t value);
	void EncodeInt64(int64_t value);
	void EncodeUInt64(uint64_t value);
	void EncodeBytes(uint8_t*  value,int length);
	void EncodeDouble(double value);

	void     InitDecoder(uint8_t* bytes,int length);
	int8_t   DecodeInt8();
	uint8_t  DecodeUInt8();
	int16_t  DecodeInt16();
	uint16_t DecodeUInt16();
	int32_t  DecodeInt32();
	uint32_t DecodeUInt32();
	int64_t  DecodeInt64();
	uint64_t DecodeUInt64();
	void     DecodeBytes(uint8_t* dst,int length);
	double   DecodeDouble();
	int      Check_Msg_Avail ();
	void     MoveForward(int32_t offset);
	uint8_t* GetBuff(){return buffer.Data();}
	uint8_t* GetCurPos(){return buffer.tail_;}
	int32_t  GetBuffUsed(){return buffer.Get_Buffer_Used();}
	uint32_t CheckSum();
	uint32_t CheckSumSsel1();
};

#endif
