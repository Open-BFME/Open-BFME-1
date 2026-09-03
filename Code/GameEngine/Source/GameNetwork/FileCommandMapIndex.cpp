// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include <stl/_config.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
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
