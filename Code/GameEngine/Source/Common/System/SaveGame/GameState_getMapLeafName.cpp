// cl: /DNDEBUG /MD /EHsc

#include <string.h>

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
