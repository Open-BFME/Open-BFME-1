// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME: the input-device state reset at 0x005A3FD0.

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

typedef unsigned char UnsignedByte;

struct Rva005A41F0InputEvent
{
	UnsignedByte m_code;
	UnsignedByte m_state;
	unsigned short m_flags;
	int m_counter;
};

struct Rva005A41F0State
{
	UnsignedByte m_code;
	UnsignedByte m_state;
	unsigned short m_flags;
	int m_counter;
};

class Rva005A41F0
{
public:
	virtual void slot00(void);
	virtual void slot01(void);
	virtual void slot02(void);
	virtual void slot03(void);
	virtual void slot04(void);
	virtual void slot05(void);
	virtual void slot06(void);
	virtual void slot07(void);
	virtual void slot08(void);
	virtual void slot09(void);
	virtual void slot10(void);
	virtual void readEvent(Rva005A41F0InputEvent *event);
	void publish(void);
	void reset(void);

private:
	char m_unknown[8];
	_STL::vector<Rva005A41F0InputEvent> m_events;
	Rva005A41F0State m_states[256];
	char m_pad[0x600];
	int m_counter;
};

// ?reset@Rva005A41F0@@QAEXXZ
void Rva005A41F0::reset(void)
{
	_STL::vector<Rva005A41F0InputEvent>& events = m_events;
	m_states[15].m_flags = 1;
	m_states[15].m_state = 1;
	m_states[15].m_counter = m_counter;
	events.clear();

	for (int i = 0; i < 256; ++i)
	{
		if (i == 15 || !(m_states[i].m_flags & 2))
			continue;

		Rva005A41F0InputEvent event;
		event.m_code = (UnsignedByte)i;
		event.m_flags = 1;
		event.m_state = 0;
		event.m_counter = m_counter;
		events.push_back(event);
	}

	if (events.begin() != events.end())
	{
		publish();
		slot10();
	}
}
