#include <iostream>
#include"base64.h"

static const std::string base64_table =
					"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
					"abcdefghijklmnopqrstuvwxyz"
					"0123456789+/";

static bool is_base64(char c)
{
	return (isalnum(c) || c == '+' || c == '/' || c == '=');
}

std::string base64_encode(char const* ESI, unsigned int len)
{
	std::string ret;
	int i = 0;
	int j = 0;
	char array_3[3];
	char array_4[4];

	while (len--)
	{
		array_3[i++] = *(ESI++);
		if (i == 3)
		{
			array_4[0] = (array_3[0] & 0xfc) >> 2;
			array_4[1] = ((array_3[0] & 0x03) << 4) + ((array_3[1] & 0xf0) >> 4); //移位运算符小于加减
			array_4[2] = ((array_3[1] & 0x0f) << 2) + ((array_3[2] & 0xc0) >> 6);
			array_4[3] = array_3[2] & 0x3f;


			for (i = 0; i < 4; i++)
			{
				ret += base64_table[array_4[i]];
			}
			i = 0;
		}
	}

	if (i)
	{
		for (j = i; j < 3; j++)
			array_3[j] = 0;

		array_4[0] = (array_3[0] & 0xfc) >> 2;
		array_4[1] = ((array_3[0] & 0x03) << 4) + ((array_3[1] & 0xf0) >> 4); 
		array_4[2] = ((array_3[1] & 0x0f) << 2) + ((array_3[2] & 0xc0) >> 6);
		//
		for (j = 0; j < (1+i); j++)
		{
			ret += base64_table[array_4[j]];
		}
		while ((i++) < 3)		//有1个字符  2个等号  , 有两个字符 1个等号
			ret += '=';			//维持3变4
	}
	return ret;
}

std::string base64_decode(std::string const& Str)
{
	size_t Str_len = Str.size();
	int i = 0, j = 0;
	int i_ = 0;
	char array_3[3];
	char array_4[4];
	std::string ret;

	for (i = 0; i < Str_len; i++)
	{
		if (!is_base64(Str[i]) || Str_len % 4 != 0)
		{
			ret += "字符串不是base64加密后的字符串！";
			return ret;
		}
	}

	i = 0;
	while (Str_len-- && Str[i_] != '=')
	{
		array_4[i++] = Str[i_++];
		if (i == 4)
		{
			for (i = 0; i < 4; i++)
				array_4[i] = base64_table.find(array_4[i]);

			array_3[0] = (array_4[0] << 2) + ((array_4[1] & 0x30) >> 4);
			array_3[1] = ((array_4[1] & 0xf) << 4) + ((array_4[2] & 0x3c) >> 2);
			array_3[2] = ((array_4[2] & 0x3) << 6) + array_4[3];

			for (i = 0; i < 3; i++)
				ret += array_3[i];

			i = 0;
		}
	}
	if (i)
	{
		for(j = 0 ; j < i ; j++)
			array_4[j] = base64_table.find(array_4[j]);

		array_3[0] = (array_4[0] << 2) + ((array_4[1] & 0x30) >> 4);
		array_3[1] = ((array_4[1] & 0xf) << 4) + ((array_4[2] & 0x3c) >> 2);

		for (j = 0; j < i - 1; j++)
		{
			ret += array_3[j];
		}
	}
	return ret;
}
