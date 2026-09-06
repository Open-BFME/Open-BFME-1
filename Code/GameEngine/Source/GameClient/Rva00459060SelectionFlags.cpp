class InGameUI
{
public:
	virtual void *slot00();
	virtual void *slot04();
	virtual void *slot08();
	virtual void *slot0C();
	virtual void *slot10();
	virtual void *slot14();
	virtual void *slot18();
	virtual void *slot1C();
	virtual void *slot20();
	virtual void *slot24();
	virtual void *slot28();
	virtual void *slot2C();
	virtual void *slot30();
	virtual void *slot34();
	virtual void *slot38();
	virtual void *slot3C();
	virtual void *slot40();
	virtual void *slot44();
	virtual void *slot48();
	virtual void *slot4C();
	virtual void *slot50();
	virtual void *slot54();
	virtual void *slot58();
	virtual void *slot5C();
	virtual void *slot60();
	virtual void *slot64();
	virtual void *slot68();
	virtual void *slot6C();
	virtual void *slot70();
	virtual void *slot74();
	virtual void *slot78();
	virtual void *slot7C();
	virtual void *slot80();
	virtual void *slot84();
	virtual void *slot88();
	virtual void *slot8C();
	virtual void *slot90();
	virtual void *slot94();
	virtual void *slot98();
	virtual void *slot9C();
	virtual void *slotA0();
	virtual void *slotA4();
	virtual void *slotA8();
	virtual void *slotAC();
	virtual void *slotB0();
	virtual void *slotB4();
	virtual void *slotB8();
	virtual void *slotBC();
};

class Rva00459060SelectionState
{
public:
	unsigned char m_padding00[0x18];
	unsigned int m_flags;
};

extern InGameUI *TheInGameUI;
extern "C" int Rva00458FC0(bool mode);

int Rva00459060(bool mode)
{
	int flags = 0x44;
	if (mode)
	{
		flags = 0x64;
	}
	Rva00459060SelectionState *state =
		(Rva00459060SelectionState *)TheInGameUI->slotBC();
	if (state != 0)
	{
		if ((state->m_flags & 0x10) != 0)
		{
			flags |= 8;
		}
		if ((state->m_flags & 0x200000) != 0)
		{
			flags |= 0x200;
		}
	}
	else
	{
		flags |= Rva00458FC0(mode);
	}
	return flags;
}
