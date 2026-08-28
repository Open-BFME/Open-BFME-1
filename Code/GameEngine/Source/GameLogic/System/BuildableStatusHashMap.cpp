// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const AsciiString &that);
	~AsciiString();

private:
	void *m_data;
};

enum BuildableStatus
{
	BUILDABLE_STATUS_PLACEHOLDER
};

namespace rts
{
	template <class T> struct hash;
	template <class T> struct equal_to;

	template <> struct hash<AsciiString>
	{
		unsigned int operator()(AsciiString value) const;
	};

	template <> struct equal_to<AsciiString>
	{
		int operator()(const AsciiString &left, const AsciiString &right) const;
	};
}

#include <hash_map>

typedef std::hash_map<AsciiString, BuildableStatus, rts::hash<AsciiString>, rts::equal_to<AsciiString> > BuildableStatusMap;

template BuildableStatus &BuildableStatusMap::operator[](const AsciiString &key);
