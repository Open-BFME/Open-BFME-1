// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
#include "ascii_string.h"

class Gen_003C6340Vector
{
public:
	// ?erase@Gen_003C6340Vector@@QAEXPAVAsciiString@@@Z absent-from-retail
	__forceinline void erase(AsciiString *position)
	{
		AsciiString *next = position + 1;
		if (next != m_finish)
		{
			int count = (int)(m_finish - next);
			AsciiString *source = next;
			if (count > 0)
			{
				AsciiString *result = position;
				while (count > 0)
				{
					result->set(*source);
					++source;
					++result;
					--count;
				}
			}
		}

		--m_finish;
		m_finish->~AsciiString();
	}

	AsciiString *m_start;
	AsciiString *m_finish;
	AsciiString *m_endOfStorage;
};

class Gen_003C6340Target
{
public:
	void bfmeForward(void *a0);		// retail 0x0000600F

private:
	char m_bfmeHead[0xD4];
	Gen_003C6340Vector m_bfmeValues;
};

// ?bfmeForward@Gen_003C6340Target@@QAEXPAX@Z
// Ported from Open BFME 2 Code/GameEngine/Source/GameClient/VideoPlayerRemoveVideo.cpp.
void Gen_003C6340Target::bfmeForward(void *a0)
{
	AsciiString *value = static_cast<AsciiString *>(a0);
	Gen_003C6340Vector &values = m_bfmeValues;
	AsciiString *current = values.m_start;
	while (current != values.m_finish)
	{
		if (current->compare(*value) == 0)
		{
			values.erase(current);
		}
		else
			++current;
	}
}
