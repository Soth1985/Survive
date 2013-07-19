#pragma once

#include <Survive/forward.h>

namespace Survive
{

struct StringUtilities
{
	static void ToString(float Val, char* Result, size_t BufSize);
	static void ToString(int Val, char* Result, size_t BufSize);
	static void ToString(unsigned int Val, char* Result, size_t BufSize);

	static void ToWideString(float Val, wchar_t* Result, size_t BufSize);
	static void ToWideString(int Val, wchar_t* Result, size_t BufSize);
	static void ToWideString(unsigned int Val, wchar_t* Result, size_t BufSize);

	static bool Parse(const char* Str, float& Val);
	static bool Parse(const char* Str, int& Val);
	static bool Parse(const char* Str, unsigned int& Val);

	static std::string WideStringToUtf8(const std::wstring& Str);
	static std::wstring Utf8ToWideString(const std::string& Str);
	static std::string WideStringToUtf8(const wchar_t* Str);
	static std::wstring Utf8ToWideString(const char* Str);
	static void WideStringToUtf8(const wchar_t* Str, char* Buf, size_t BufSize);
	static void Utf8ToWideString(const char* Str, wchar_t* Buf, size_t BufSize);
};

}