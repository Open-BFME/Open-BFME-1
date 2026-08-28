// cl: /DNDEBUG /MD /EHsc
// readable body of ?updateMouseData@Mouse@@: Code/GameEngine/Source/GameClient/Input/Mouse.cpp

// Open-BFME5: Mouse::updateMouseData, retail 0x005A42E0, 114 bytes. The body
// carried only a machine byte-dump row; the symbols.csv pin names it, and the
// reentry flag it guards itself with is pinned with this row.
//
// The drain is a virtual at slot 24 filling one 0x3C-byte event at a time out
// of the array at +0x1110. A 0xFF answer means try the same slot again and does
// not count; anything else counts and steps on, a zero ends the drain, and 256
// events is the ceiling.
//
// Afterwards the index at +0x4E00 is one below the count, or zero -- and zero
// is also what a reentrant call leaves behind, which is why the guarded exit
// and the empty-drain exit share the same store. The last copy at +0x4D98 only
// happens when something was actually read.
//
// The ceiling test is unsigned and the later one is not: retail compares the
// count against 256 with jb and against zero with jle, so the cast belongs on
// the loop bound alone.

typedef int Int;

class BfmeMouseEvent
{
public:
	char m_bfmeBody[0x3C];
};

extern bool Glo012F4C62;					// 0x012F4C62

class Mouse
{
public:
	virtual void _bfme_slot0(void) = 0;
	virtual void _bfme_slot1(void) = 0;
	virtual void _bfme_slot2(void) = 0;
	virtual void _bfme_slot3(void) = 0;
	virtual void _bfme_slot4(void) = 0;
	virtual void _bfme_slot5(void) = 0;
	virtual void _bfme_slot6(void) = 0;
	virtual void _bfme_slot7(void) = 0;
	virtual void _bfme_slot8(void) = 0;
	virtual void _bfme_slot9(void) = 0;
	virtual void _bfme_slot10(void) = 0;
	virtual void _bfme_slot11(void) = 0;
	virtual void _bfme_slot12(void) = 0;
	virtual void _bfme_slot13(void) = 0;
	virtual void _bfme_slot14(void) = 0;
	virtual void _bfme_slot15(void) = 0;
	virtual void _bfme_slot16(void) = 0;
	virtual void _bfme_slot17(void) = 0;
	virtual void _bfme_slot18(void) = 0;
	virtual void _bfme_slot19(void) = 0;
	virtual void _bfme_slot20(void) = 0;
	virtual void _bfme_slot21(void) = 0;
	virtual void _bfme_slot22(void) = 0;
	virtual void _bfme_slot23(void) = 0;
	virtual unsigned char bfmeGetEvent(BfmeMouseEvent *event, Int wait) = 0;

protected:
	void updateMouseData(void);

private:
	char m_bfmeHeadA[0x1110 - 0x04];
	BfmeMouseEvent m_bfmeEvents[256];			// +0x1110
	char m_bfmeHeadB[0x4D98 - 0x4D10];
	Int m_bfmeLast;						// +0x4D98
	Int m_bfmePrevious;					// +0x4D9C
	char m_bfmeHeadC[0x4E00 - 0x4DA0];
	Int m_bfmeCount;					// +0x4E00
};

// ?updateMouseData@Mouse@@IAEXXZ
void Mouse::updateMouseData(void)
{
	Int count = 0;

	if (!Glo012F4C62)
	{
		Glo012F4C62 = true;

		BfmeMouseEvent *event = m_bfmeEvents;

		for (;;)
		{
			unsigned char answer;

			do
				answer = bfmeGetEvent(event, 1);
			while (answer == 0xFF);

			++count;
			++event;

			if (answer == 0)
				break;

			if ((unsigned int)count >= 0x100)
				break;
		}

		Glo012F4C62 = false;
	}

	if (count > 0)
		m_bfmeCount = count - 1;
	else
		m_bfmeCount = 0;

	if (count != 0)
		m_bfmePrevious = m_bfmeLast;
}
