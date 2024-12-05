#include "endianness_codec.h"


CodecBuffer::CodecBuffer()
{
	data_ = NULL;
	head_ = NULL;
	tail_ = NULL;
	end_ = NULL;
}

CodecBuffer::~CodecBuffer()
{
	if (data_ != NULL)
		free(data_);
	data_ = NULL;
	head_ = NULL;
	tail_ = NULL;
	end_ = NULL;
}

void CodecBuffer::MallocBuffer(uint32_t length)
{
	if (data_ == NULL)
	{
		data_ = (uint8_t*)malloc(length);
	}
	else if (Get_Buffer_Size() < length)
	{
		free(data_);
		data_ = (uint8_t*)malloc(length);
	}
	ResetBuffer(data_, length);
}

void CodecBuffer::RiseBuffer()
{
	int size = Get_Buffer_Size();
	int used_size = Get_Buffer_Used();

	uint8_t* mBuffer = (uint8_t*)malloc(2 * size);
	memcpy(mBuffer, data_, used_size);
	free(data_);

	data_ = mBuffer;
	head_ = data_;
	tail_ = data_ + used_size;
	end_ = data_ + size * 2;
}

void CodecBuffer::ResetBuffer(uint8_t* bytes, int length)
{
	head_ = bytes;
	tail_ = bytes;
	end_ = bytes + length;
}

void CodecBuffer::CopyTo(uint8_t* buffer)
{
	int bufferSize = Get_Buffer_Used();
	memcpy(buffer, data_, bufferSize);
}

void CodecBuffer::PrintBuffer()
{
	// end_换成了tail_
	std::cout << "----Buffer中Byte数目为：" << std::dec << end_ - head_ << "个。----" << std::endl;
	for (uint8_t* i = head_; i < end_; i++)
		std::cout << std::hex << (int)*i << " ";
	std::cout << std::endl;
}

uint32_t CodecBuffer::IsBufferEmpty()
{
	return (uint32_t)(head_ >= tail_);
}

uint32_t CodecBuffer::Get_Buffer_Left()
{
	uint32_t ret = (uint32_t)(end_ - tail_);
	return ret;
}

uint32_t CodecBuffer::Get_Buffer_Size()
{
	uint32_t ret = (uint32_t)(end_ - tail_);
	return ret;

}

uint32_t CodecBuffer::Get_Buffer_Used()
{
	uint32_t ret = (uint32_t)(end_ - tail_);
	return ret;
}

EndiannessCodec::EndiannessCodec(void)
{
  
}

EndiannessCodec::~EndiannessCodec(void)
{
}

void EndiannessCodec::InitDecoder(uint8_t* bytes,int length)
{
	buffer.ResetBuffer(bytes,length);
}

void EndiannessCodec::InitEncoder(uint8_t* bytes,int length)
{
  buffer.ResetBuffer(bytes,length);
}

void EndiannessCodec::InitEncoder(int32_t length)
{  
	buffer.MallocBuffer(length);
}

void EndiannessCodec::EncodeInt8(int8_t value)
{
	*buffer.tail_ ++ = value;
}

void EndiannessCodec::EncodeInt16(int16_t value)
{
  int16_t temp = Endianness::swap_int16(value);
  memcpy(buffer.tail_,&temp,sizeof(int16_t));
  buffer.tail_ += sizeof(int16_t);
}

void EndiannessCodec::EncodeUInt16(uint16_t value)
{
  uint16_t temp = Endianness::swap_uint16(value);
  memcpy(buffer.tail_,&temp,sizeof(uint16_t));
  buffer.tail_ += sizeof(uint16_t);
}

void EndiannessCodec::EncodeInt32(int32_t value)
{
  int32_t temp = Endianness::swap_int32(value);
	memcpy(buffer.tail_,&temp,sizeof(value));
	buffer.tail_ += sizeof(value);
}

void EndiannessCodec::EncodeUInt32(uint32_t value)
{
  uint32_t temp = Endianness::swap_uint32(value);
  memcpy(buffer.tail_,&temp,sizeof(value));
  //memcpy(buffer.tail_,&value,sizeof(value));
  buffer.tail_ += sizeof(value);
}

void EndiannessCodec::EncodeInt64(int64_t value)
{
  int64_t temp = Endianness::swap_int64(value);
  memcpy(buffer.tail_,&temp,sizeof(value));
	buffer.tail_ += sizeof(value);
}

void EndiannessCodec::EncodeUInt64(uint64_t value)
{
  uint64_t temp = Endianness::swap_uint64(value);
  memcpy(buffer.tail_,&temp,sizeof(value));
  buffer.tail_ += sizeof(value);
}

void EndiannessCodec::EncodeDouble(double value)
{
  uint64_t temp = Endianness::swap_uint64((uint64_t)value);
  memcpy(buffer.tail_,&temp,sizeof(value));
	buffer.tail_ += sizeof(value);
}

void EndiannessCodec::EncodeBytes(uint8_t* src,int length)
{
	memcpy(buffer.tail_,src,length);
	buffer.tail_ += length;
}

int8_t EndiannessCodec::DecodeInt8()
{
  return*buffer.tail_++;
}

uint8_t EndiannessCodec::DecodeUInt8()
{
  return*buffer.tail_++;
}

int16_t EndiannessCodec::DecodeInt16()
{
  int16_t value;
  memcpy(&value,buffer.tail_,sizeof(int16_t));
  buffer.tail_+=sizeof(int16_t);
  value = Endianness::swap_int16(value);
  return value;
}

uint16_t EndiannessCodec::DecodeUInt16()
{
  uint16_t value;
  memcpy(&value,buffer.tail_,sizeof(uint16_t));
  buffer.tail_+=sizeof(uint16_t);
  value = Endianness::swap_uint16(value);
  return value;
}

int32_t EndiannessCodec::DecodeInt32()
{
	int32_t value;
	memcpy(&value,buffer.tail_,sizeof(value));
	buffer.tail_+=sizeof(value);
  value = Endianness::swap_int32(value);
	return value;
}

uint32_t EndiannessCodec::DecodeUInt32()
{
  uint32_t value;
  memcpy(&value,buffer.tail_,sizeof(value));
  buffer.tail_+=sizeof(value);
  value = Endianness::swap_uint32(value);
  return value;
}

int64_t EndiannessCodec::DecodeInt64()
{
	int64_t value;
	memcpy(&value,buffer.tail_,sizeof(value));
	buffer.tail_+=sizeof(value);
  value = Endianness::swap_int64(value);
	return value;
}

uint64_t EndiannessCodec::DecodeUInt64()
{
  uint64_t value;
  memcpy(&value,buffer.tail_,sizeof(value));
  buffer.tail_+=sizeof(value);
  value = Endianness::swap_uint64(value);
  return value;
}

double EndiannessCodec::DecodeDouble()
{
	double value;
	memcpy(&value,buffer.tail_,sizeof(value));
	buffer.tail_+=sizeof(value);
	value = (double)(Endianness::swap_uint64((uint64_t)value));
	return value;
}

void EndiannessCodec::DecodeBytes(uint8_t* dst,int length)
{
	memcpy(dst,buffer.tail_,length);
	buffer.tail_+=length;
}

int EndiannessCodec::Check_Msg_Avail ()
{
  if (buffer.Get_Buffer_Left () < 102400)
    buffer.RiseBuffer();
  return 0;
}

void EndiannessCodec::MoveForward(int32_t offset)
{
  buffer.tail_= buffer.tail_+offset;
}

uint32_t EndiannessCodec::CheckSum()
{
  uint32_t idx;
  uint32_t cks =0;
  uint8_t* buff = buffer.Data();
  uint32_t buffsize = buffer.Get_Buffer_Used();
  for (idx=0,cks=0;idx<buffsize;cks+=(uint32_t)buff[idx++]);
  return (cks%256);
}

uint32_t EndiannessCodec::CheckSumSsel1()
{
  uint32_t idx;
  uint8_t cks = 0;
  uint8_t* buff = buffer.Data();
  uint32_t buffsize = buffer.Get_Buffer_Used();
  for (idx = 0, cks = 0; idx < buffsize; cks += (uint8_t)buff[idx++]);
  return (uint8_t)cks;
}
