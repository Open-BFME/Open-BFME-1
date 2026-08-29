// Four bodies from the 0x0078xxxx run.  Identity is not recovered; names are
// address-derived and the padding virtuals exist only to place the one slot
// each body calls.

// ---------------------------------------------------------------------------
// 0x007896C0 -- publish a changed (int, int) pair, one of them as a float.
//
//     ... fild [esp+0xc] / push edx / push ecx / mov [eax+8],edx
//     fstp dword ptr [esp] / mov [eax+0xc],edi / push esi / call [eax+0xb0]
//
// `push ecx` reserves the slot the `fstp` then overwrites, so the middle
// argument is a float built from the FIRST parameter while the third is the
// second parameter unchanged.  Nothing happens unless one of the two members
// actually differs, which is the pair of compares at the top.

class Open2Target;

class Open2Owner
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
	virtual void slot54();
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
	virtual void slotB0( Open2Target *target, float scaled, int raw );
};

class Rva007896C0
{
public:
	void publish( int first, int second );

	Open2Owner *m_owner;
	Open2Target *m_target;
	int m_second;
	int m_first;
};

// @?publish@Rva007896C0@@QAEXHH@Z 0x007896C0
void Rva007896C0::publish( int first, int second )
{
	Open2Owner *owner = m_owner;
	if( owner == 0 )
		return;

	Open2Target *target = m_target;
	if( target == 0 )
		return;

	if( m_first == first && m_second == second )
		return;

	m_second = second;
	m_first = first;
	owner->slotB0( target, (float)first, second );
}
