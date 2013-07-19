#include <Survive/string_utilities.h>
#include <utf8cpp/utf8.h>

namespace Survive
{

void StringUtilities::ToString(float Val, char* Result, size_t BufSize)
{
	if( sprintf(Result, "%f", Val) < 0 )
		assert(0 && "Buffer is too small");
}

void StringUtilities::ToString(int Val, char* Result, size_t BufSize)
{
	if( sprintf(Result, "%d", Val) < 0 )
		assert(0 && "Buffer is too small");
}

void StringUtilities::ToString(unsigned int Val, char* Result, size_t BufSize)
{
	if( sprintf(Result, "%u", Val) < 0 )
		assert(0 && "Buffer is too small");
}

void StringUtilities::ToWideString(float Val, wchar_t* Result, size_t BufSize)
{
	if( swprintf(Result, BufSize, L"%f", Val) < 0 )
		assert(0 && "Buffer is too small");
}

void StringUtilities::ToWideString(int Val, wchar_t* Result, size_t BufSize)
{
	if( swprintf(Result, BufSize, L"%d", Val) < 0 )
		assert(0 && "Buffer is too small");
}

void StringUtilities::ToWideString(unsigned int Val, wchar_t* Result, size_t BufSize)
{
	if( swprintf(Result, BufSize, L"%u", Val) < 0 )
		assert(0 && "Buffer is too small");
}

bool StringUtilities::Parse(const char* Str, float& Val)
{
	char* End;
	double Temp = strtod(Str, &End);

	if (Str != End)
	{
		Val = (float)Temp;
		return true;
	}

	return false;
}

bool StringUtilities::Parse(const char* Str, int& Val)
{
	char* End;
	int Temp = strtol(Str, &End, 10);

	if (Str != End)
	{
		Val = Temp;
		return true;
	}

	return false;
}

bool StringUtilities::Parse(const char* Str, unsigned int& Val)
{
	char* End;
	unsigned int Temp = strtoul(Str, &End, 10);

	if (Str != End)
	{
		Val = (unsigned int)Temp;
		return true;
	}

	return false;
}

std::string StringUtilities::WideStringToUtf8(const std::wstring& Str)
{
	std::string Converted;
	utf8::utf16to8(Str.begin(), Str.end(), std::back_inserter(Converted));
	return Converted;
}

std::wstring StringUtilities::Utf8ToWideString(const std::string& Str)
{
	std::wstring Converted;
	utf8::utf8to16(Str.begin(), Str.end(), std::back_inserter(Converted));
	return Converted;
}

std::string StringUtilities::WideStringToUtf8(const wchar_t* Str)
{
	std::string Converted;
	utf8::utf16to8(Str, Str + wcslen(Str), std::back_inserter(Converted));
	return Converted;
}

std::wstring StringUtilities::Utf8ToWideString(const char* Str)
{
	std::wstring Converted;
	utf8::utf8to16(Str, Str + strlen(Str), std::back_inserter(Converted));
	return Converted;
}

void StringUtilities::WideStringToUtf8(const wchar_t* Str, char* Buf, size_t BufSize)
{
	utf8::utf16to8(Str, Str + wcslen(Str) + 1, Buf);
}

void StringUtilities::Utf8ToWideString(const char* Str, wchar_t* Buf, size_t BufSize)
{
	utf8::utf8to16(Str, Str + strlen(Str) + 1, Buf);
}

}