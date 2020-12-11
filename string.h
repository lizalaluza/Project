#pragma once
#include <iostream>
#include "stdlib.h"
#include <cassert>

class String
{
private:
	int len;
	int capacity;

public:
	char* str;

	String(char* str)
	{
		int len = 0;
		while (str[len] != '\0')
			len++;
		this->len = len;
		capacity = len * 2;
		this->str = new char[capacity];
		for (int i = 0; i < len; i++)
			this->str[i] = str[i];
		this->str[len] = '\0';
	}

	String()
	{
		char c = '\0';
		capacity = 100;
		str = new char[capacity];
		str[0] = c;
		len = 0;
	}

	String(char c)
	{
		capacity = 5;
		str = new char[capacity];
		str[0] = c;
		str[1] = '\0';
		len = 1;
	}

	String(const String& sample)
	{
		capacity = sample.capacity;
		len = sample.len;
		str = new char[capacity];
		for (int i = 0; i < len; i++)
			str[i] = sample.str[i];
		str[len] = '\0';
	}

	~String()
	{
		delete[] str;
	}

	char operator[](int index)
	{
		assert(index >= 0 & index < len);
		return str[index];

	}

	int length()
	{
		return this->len;
	}

	int countChar(char c)
	{
		int count = 0;
		for (int i = 0; i < len; i++)
		{
			if (str[i] == c)
				count++;
		}
		return count;
	}

	int findFirstOf(char c)
	{
		int pos = -1;
		for (int i = 0; i < len; i++)
		{
			if (str[i] == c)
			{
				pos = i;
				break;
			}
		}
		return pos;
	}

	String* split(int index)
	{
		//assert(index >= 0 & index < len);
		String* res = new String[4];
		int i = 0;
		while (i < len)
		{
			if (i < index)
			{
				res[0] += String(str[i]);
			}
			if (i > index)
			{
				res[1] += String(str[i]);
			}
			i++;
		}
		return res;
	}

	void operator+=(String str2)
	{
		int new_len = len + str2.len;

		if (new_len >= capacity)
		{
			capacity = new_len * 2;
			char* old_str = new char[capacity];
			for (int i = 0; i < len; i++)
				old_str[i] = str[i];
			old_str[len] = '\0';
			delete[] str;
			str = old_str;
		}

		for (int i = 0; i < str2.len; i++)
		{
			str[i + len] = str2[i];
		}
		str[new_len] = '\0';

		len = new_len;
	}
};