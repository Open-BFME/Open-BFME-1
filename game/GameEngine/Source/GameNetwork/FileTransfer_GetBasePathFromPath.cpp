// cl: /GX /Igame/Libraries/Source/WWVegas/WWLib

#include "ascii_string.h"
extern "C" void *memcpy(void *destination, const void *source, unsigned int count);
template<> inline const char *StringBase<char>::reverseFind(char match) const
{
    const char *first = m_data ? &m_data->data[0] : "";
    const char *p = first + (m_data ? m_data->length : 0);
    while (p != first) {
        --p;
        if (*p == match) return p;
    }
    return 0;
}

AsciiString GetBasePathFromPath(AsciiString path)
{
	const char *separator = path.StringBase<char>::reverseFind('\\');
	if (separator)
	{
		int prefixLength = separator - path.str();
		AsciiString base;
		char *buffer = base.getBufferForRead(prefixLength);
		memcpy(buffer, path.str(), prefixLength);
		buffer[prefixLength] = 0;
		return buffer;
	}
	return AsciiString::TheEmptyString;
}
