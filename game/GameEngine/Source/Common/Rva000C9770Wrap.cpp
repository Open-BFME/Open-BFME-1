// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

class AIPlayer
{
public:
	void buildUpgrade(const AsciiString &upgrade);
};

class Rva000C9770
{
	char m_pad[0x220];
	AIPlayer *m_inner;

public:
	void wrap(int a);
};

void Rva000C9770::wrap(int a)
{
	if (m_inner)
		m_inner->buildUpgrade(*(const AsciiString *)a);
}
