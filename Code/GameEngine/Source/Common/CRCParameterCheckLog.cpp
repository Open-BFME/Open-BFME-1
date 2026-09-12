// cl: /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <stdarg.h>
#include <vector>

extern "C" __declspec(dllimport) int __cdecl _vsnprintf(
	char *, unsigned int, const char *, va_list);

template <typename T>
class StringBase
{
	friend class AsciiString;

public:
	StringBase(const StringBase<T> &source);

private:
	void releaseBuffer();

	void *m_data;
};

class AsciiString
{
public:
	AsciiString(const char *text);
	AsciiString(const AsciiString &source) : m_data(source.m_data) {}
	~AsciiString() { m_data.releaseBuffer(); }

private:
	StringBase<char> m_data;
};

class CRCParameterCheck
{
public:
	std::vector<AsciiString> m_parameters;

private:
	virtual ~CRCParameterCheck();
};

extern "C" void __cdecl bfmeRetailCritterDesyncLog(
	CRCParameterCheck *check, const char *format, ...)
{
	if (format == 0)
		return;

	char buffer[1000];
	va_list args;

	va_start(args, format);
	_vsnprintf(buffer, sizeof(buffer), format, args);
	va_end(args);

	AsciiString value(buffer);
	check->m_parameters.push_back(value);
}
