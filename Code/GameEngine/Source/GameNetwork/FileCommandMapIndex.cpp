// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include <stl/_config.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	AsciiString(const AsciiString &other);
	~AsciiString();

private:
	void *m_data;
};

#include <map>

typedef std::map<unsigned short, AsciiString> FileCommandMap;

template AsciiString &FileCommandMap::operator[](const unsigned short &key);
