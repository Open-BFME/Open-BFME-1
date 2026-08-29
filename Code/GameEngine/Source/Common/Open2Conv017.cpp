// Two bodies from the 0x006xxxxx run.  Identity is not recovered.

// ---------------------------------------------------------------------------
// 0x006094E0 -- walk a count that is re-asked every turn, releasing each item.
//
// The count comes back from slot 0x6C and is called AGAIN at the bottom of
// every iteration rather than being hoisted, so the loop condition really does
// re-evaluate it.  The flag argument reaches the item inverted (`sete` on a
// zero test), and the release is `dec [item+4] / jne`, a plain zero test
// rather than the signed `<= 0` some other counters in this binary use.

class Open26094E0Item
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
	virtual void slot170();
	virtual void slot174();
	virtual void slot178();
	virtual void slot17C();
	virtual void slot180();
	virtual void slot184();
	virtual void slot188();
	virtual void slot18C();
	virtual void slot190( int inverted );

	int m_refs;
};

class Open26094E0Owner
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
	virtual int slot6C();
	virtual void slot70();
	virtual Open26094E0Item *slot74( int index );
};

// @?Rva006094E0@@YGXPAVOpen26094E0Owner@@D@Z 0x006094E0
void __stdcall Rva006094E0( Open26094E0Owner *owner, char flag )
{
	for( int index = 0; index < owner->slot6C(); ++index )
	{
		Open26094E0Item *item = owner->slot74( index );
		if( item != 0 )
		{
			item->slot190( flag == 0 );
			if( --item->m_refs == 0 )
				item->slot00();
		}
	}
}

