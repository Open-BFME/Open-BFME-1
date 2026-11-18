// cl: /DNDEBUG /MD /EHsc

#include "../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"


class RecorderClass
{
public:
	RecorderClass();
	// Retail's destructor is virtual: ??1RecorderClass@@UAE@XZ at 0x00099070 (ILT 0x0001F55F).
	virtual ~RecorderClass();
	bool testVersionPlayback(AsciiString filename);

private:
	char m_pad[0x2B0];
};

class Rva56E070StateOwner
{
public:
	char m_pad0[0x258];
	int m_state;
	AsciiString *m_text;

	void finishState14();
};

void Rva56E070StateOwner::finishState14()
{
	if (m_text != 0)
	{
		RecorderClass rec;
		if (rec.testVersionPlayback(*m_text))
			m_state = 13;
		else
			m_state = m_text != 0 ? 3 : 1;
	}
	else
		m_state = 1;
}
