// cl: /O2
// ?tell@BfmeThingMI@@QAEXM@Z

class BfmeThingMIMid
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void slot50();
	virtual void plain(float unused);
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual void slot6C();
	virtual void slot70();
	virtual void slot74();
	virtual void slot78();
	virtual void slot7C();
	virtual void slot80();
	virtual void slot84();
	virtual void slot88();
	virtual void slot8C();
	virtual void slot90();
	virtual void slot94();
	virtual void slot98();
	virtual void slot9C();
	virtual void slotA0();
	virtual void slotA4();
	virtual void slotA8();
	virtual void slotAC();
	virtual void slotB0();
	virtual void slotB4();
	virtual void slotB8();
	virtual void slotBC();
	virtual void slotC0();
	virtual void slotC4();
	virtual void slotC8();
	virtual void slotCC();
	virtual void slotD0();
	virtual void slotD4();
	virtual void slotD8();
	virtual void slotDC();
	virtual void slotE0();
	virtual void slotE4();
	virtual void slotE8();
	virtual void slotEC();
	virtual void slotF0();
	virtual void slotF4();
	virtual void slotF8();
	virtual void slotFC();
	virtual void slot100();
	virtual void slot104();
	virtual void slot108();
	virtual void slot10C();
	virtual void slot110();
	virtual void slot114();
	virtual void slot118();
	virtual void slot11C();
	virtual void slot120();
	virtual void slot124();
	virtual void slot128();
	virtual void slot12C();
	virtual void slot130();
	virtual void slot134();
	virtual void slot138();
	virtual void slot13C();
	virtual void slot140();
	virtual void slot144();
	virtual void slot148();
	virtual void slot14C();
	virtual void slot150();
	virtual void slot154();
	virtual void slot158();
	virtual void slot15C();
	virtual void slot160();
	virtual void slot164();
	virtual void slot168();
	virtual void slot16C();
	virtual void scaled(float s);
};

class BfmeThingMIOwner
{
public:
	char m_pad[0x1F8];
	float m_scale;
};

class BfmeThingMI
{
public:
	void tell(float unused);

private:
	char m_pad00[8];
	BfmeThingMIOwner *m_owner;
	BfmeThingMIMid *volatile m_mid;
};

void BfmeThingMI::tell(float unused)
{
	if (m_mid == 0)
		return;
	BfmeThingMIOwner *owner = m_owner;
	BfmeThingMIMid *mid = m_mid;
	float scale = owner->m_scale;
	if (scale != 1.0f)
		mid->scaled(owner->m_scale);
	else
		mid->plain(unused);
}
