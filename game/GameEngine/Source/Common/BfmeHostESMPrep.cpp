// cl: /DNDEBUG /DWIN32 /MD /EHsc
// ?bfmePrepESM@BfmeHostESM@@QAEXPAVBfmeThingESM@@@Z
// Retail 0x00609AC0.  The ILT at 0x00044693 and the call from
// BfmeHostESM::bfmeRunESM identify this member.  Retail walks LM_01 through
// LM_12, looks up each name through the argument's +0x7c virtual slot, and
// releases each returned object after invoking its +0x190 virtual slot.

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

extern const char g_bfmeEmptyAscii[];

class BfmeThingESM
{
public:
	virtual void release() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual BfmeThingESM *lookup(const char *name, int zero) = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void slot39() = 0;
	virtual void slot40() = 0;
	virtual void slot41() = 0;
	virtual void slot42() = 0;
	virtual void slot43() = 0;
	virtual void slot44() = 0;
	virtual void slot45() = 0;
	virtual void slot46() = 0;
	virtual void slot47() = 0;
	virtual void slot48() = 0;
	virtual void slot49() = 0;
	virtual void slot50() = 0;
	virtual void slot51() = 0;
	virtual void slot52() = 0;
	virtual void slot53() = 0;
	virtual void slot54() = 0;
	virtual void slot55() = 0;
	virtual void slot56() = 0;
	virtual void slot57() = 0;
	virtual void slot58() = 0;
	virtual void slot59() = 0;
	virtual void slot60() = 0;
	virtual void slot61() = 0;
	virtual void slot62() = 0;
	virtual void slot63() = 0;
	virtual void slot64() = 0;
	virtual void slot65() = 0;
	virtual void slot66() = 0;
	virtual void slot67() = 0;
	virtual void slot68() = 0;
	virtual void slot69() = 0;
	virtual void slot70() = 0;
	virtual void slot71() = 0;
	virtual void slot72() = 0;
	virtual void slot73() = 0;
	virtual void slot74() = 0;
	virtual void slot75() = 0;
	virtual void slot76() = 0;
	virtual void slot77() = 0;
	virtual void slot78() = 0;
	virtual void slot79() = 0;
	virtual void slot80() = 0;
	virtual void slot81() = 0;
	virtual void slot82() = 0;
	virtual void slot83() = 0;
	virtual void slot84() = 0;
	virtual void slot85() = 0;
	virtual void slot86() = 0;
	virtual void slot87() = 0;
	virtual void slot88() = 0;
	virtual void slot89() = 0;
	virtual void slot90() = 0;
	virtual void slot91() = 0;
	virtual void slot92() = 0;
	virtual void slot93() = 0;
	virtual void slot94() = 0;
	virtual void slot95() = 0;
	virtual void slot96() = 0;
	virtual void slot97() = 0;
	virtual void slot98() = 0;
	virtual void slot99() = 0;
	virtual void addThing(int zero) = 0;

	int m_refCount;
};

class BfmeHostESM
{
public:
	virtual void hostSlot00() = 0;
	virtual void hostSlot01() = 0;
	virtual void hostSlot02() = 0;
	virtual void hostSlot03() = 0;
	virtual void hostSlot04() = 0;
	virtual void hostSlot05() = 0;
	virtual void hostSlot06() = 0;
	virtual void hostSlot07() = 0;
	virtual void hostSlot08() = 0;
	virtual void hostSlot09() = 0;
	virtual void hostSlot10() = 0;
	virtual void hostSlot11() = 0;
	virtual void hostSlot12() = 0;
	virtual void hostSlot13() = 0;
	virtual void hostSlot14() = 0;
	virtual void hostSlot15() = 0;
	virtual void hostSlot16() = 0;
	virtual void hostSlot17() = 0;
	virtual void hostSlot18() = 0;
	virtual void hostSlot19() = 0;
	virtual void hostSlot20() = 0;
	virtual void hostSlot21() = 0;
	virtual void hostSlot22() = 0;
	virtual void hostSlot23() = 0;
	virtual void hostSlot24() = 0;
	virtual void hostSlot25() = 0;
	virtual void hostSlot26() = 0;
	virtual void hostSlot27() = 0;
	virtual BfmeThingESM *hostSlot28() = 0;
	void bfmePrepESM(BfmeThingESM *thing);
};

void BfmeHostESM::bfmePrepESM(BfmeThingESM *thing)
{
	int index = 0;
	for (; index < 12; ++index)
	{
		AsciiString name;
		name.format(AsciiString("LM_%02d"), index + 1);

		const char *text = *(const char **)&name;
		if (text != 0)
			text += 8;
		else
			text = g_bfmeEmptyAscii;

		BfmeThingESM *result = thing->lookup(text, 0);
		if (result != 0)
		{
			result->addThing(0);
			--result->m_refCount;
			if (result->m_refCount == 0)
				result->release();
		}
	}
}
