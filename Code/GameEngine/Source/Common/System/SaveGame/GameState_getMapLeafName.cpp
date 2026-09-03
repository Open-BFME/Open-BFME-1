// cl: /DNDEBUG /MD /EHsc
// readable body of ?getMapLeafName@GameState@@QBE?AVAsciiString@@ABV2@@Z: Code/GameEngine/Source/Common/System/SaveGame/GameState.cpp

#include <string.h>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const char *text);
	AsciiString(const AsciiString &other);
	~AsciiString();

	const char *str() const
	{
		return m_data ? m_data + 8 : "";
	}

private:
	char *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameState.h
class GameState
{
public:
	AsciiString getMapLeafName(const AsciiString &path) const;
};

AsciiString GameState::getMapLeafName(const AsciiString &path) const
{
	char *separator = strrchr((char *)path.str(), '\\');
	if (separator)
	{
		++separator;
		return separator;
	}
	return path;
}
