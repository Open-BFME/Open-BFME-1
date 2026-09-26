// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME5: Rva005A41F0::tick, retail 0x005A40E0, 210 bytes.
// The method clears its eight-byte input queue, retries after a lost-device
// record, and appends each nonzero input record until the device returns none.

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

typedef unsigned char UnsignedByte;

struct Rva005A41F0InputEvent
{
	unsigned int m_word;
	int m_value;
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
	void reset(void);
	void tick(void);

private:
	char m_unknown[8];
	_STL::vector<Rva005A41F0InputEvent> m_events;
	char m_pad[0xe00];
	int m_counter;
};

#pragma comment(linker, "/alternatename:?reset@Rva005A41F0@@QAEXXZ=?j_0001ee93@@YAXXZ")

void Rva005A41F0::tick(void)
{
	m_events.clear();
	unsigned int eventWord;
	int eventValue;
	Rva005A41F0InputEvent *event = (Rva005A41F0InputEvent *)&eventWord;
	for (;;)
	{
		readEvent(event);
		unsigned int result = eventWord;
		while ((unsigned char)result == 0xff)
		{
			reset();
			m_events.clear();
			readEvent(event);
			result = eventWord;
		}
		if (!(unsigned char)result)
			return;
		m_events.push_back(*(Rva005A41F0InputEvent *)&eventWord);
	}
}
