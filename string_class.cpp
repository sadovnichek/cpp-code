#define _CRT_SECURE_NO_WARNINGS

#include <cstddef>
#include <cstring>
#include <iostream>

struct String {

	explicit String(const char* str = "")
	{
		size = strlen(str);
		this->str = new char[size+1];
		strcpy(this->str, str);
	}

	String(size_t n, char c)
	{
		size = n;
		this->str = new char[size + 1];
		for (int i = 0; i < n; i++)
		{
			this->str[i] = c;
		}
		this->str[n] = '\0';
	}

	String(const String& other)
		: size(other.size), str(new char[other.size + 1])
	{
		for (int i = 0; i < size; i++) {
			str[i] = other.str[i];
		}
		str[size] = '\0';
	}

	String& operator=(const String& other) {
		if (this != &other)
		{
			delete[] str;
			size = other.size;
			str = new char[size + 1];
			for (int i = 0; i < size; i++) {
				str[i] = other.str[i];
			}
			str[size] = '\0';
		}
		return *this;
	}

	~String()
	{
		delete[] str;
	}

	void append(String& other)
	{
		size_t new_size = size + other.size;
		char* new_str = new char[new_size + 1];
		for (int i = 0; i < size; i++)
		{
			new_str[i] = str[i];
		}
		for (int i = size; i < size + other.size; i++)
		{
			new_str[i] = other.str[i - size];
		}
		new_str[new_size] = '\0';
		delete[] str;
		size = new_size;
		str = new_str;
	}

private:
	size_t size;
	char* str;
};
