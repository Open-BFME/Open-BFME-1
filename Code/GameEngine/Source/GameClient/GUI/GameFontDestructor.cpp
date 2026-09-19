// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib

class MemoryPoolObject
{
public:
	virtual void memoryPoolAnchor();
};

#include "ascii_string.h"

class GameFont : public MemoryPoolObject
{
public:
	GameFont();

protected:
	virtual ~GameFont();

private:
	GameFont *m_next;
	AsciiString m_nameString;
};

GameFont::GameFont()
{
}

GameFont::~GameFont()
{
}
