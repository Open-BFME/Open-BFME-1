// Retail 0x007861E0, 208 bytes, carved with no direct caller. Takes an
// AsciiString path, finds the last '/' and the last '.', backs up over the
// digits before the dot, sscanf's them with "%d.", and returns either the whole
// path or the text after the slash. Identity unproven, so the name keeps the
// address token. Both reverseFind calls are inlined in retail.
#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

extern "C" __declspec(dllimport) int __cdecl isdigit(int c);
extern "C" __declspec(dllimport) int __cdecl sscanf(const char *buffer, const char *format, ...);

struct Rva007861E0Text
{
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		char data[1];
	};

	const char *str() const
	{
		return m_data ? &m_data->data[0] : (const char *)"";
	}

	const char *reverseFind(char c) const
	{
		const char *start = str();
		const char *p = start + (m_data ? m_data->length : 0);
		while (p != start)
		{
			--p;
			if (*p == c)
				return p;
		}
		return 0;
	}

	Header *m_data;
};

const char *parsePathNumber007861E0(const AsciiString &path, int *number, bool whole)
{
	const Rva007861E0Text &text = (const Rva007861E0Text &)path;
	const char *slash = text.reverseFind('/');
	if (slash)
	{
		const char *dot = text.reverseFind('.');
		if (dot)
		{
			const char *digits = dot;
			while (isdigit(digits[-1]))
				--digits;
			sscanf(digits, "%d.", number);
			if (whole)
				return text.str();
			return slash + 1;
		}
	}
	return 0;
}
