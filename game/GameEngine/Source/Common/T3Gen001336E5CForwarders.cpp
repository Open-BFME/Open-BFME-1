// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME-1: four more __cdecl forwarders into the global at 0x01336E5C.
//
// Same object and the same idiom as
// game/GameEngine/Source/Common/S2DebugCommandRegistrars.cpp, which already
// pins the vtable slot at 0x8C as registerCommand: load the global, load its
// vptr, push the wrapper's own arguments unchanged and dispatch through a fixed
// slot. The class and the global keep the names that file gave them so the two
// translation units agree on what [0x01336E5C] is.
//
// Three new slots appear here -- 0x6C with two arguments, 0x90 with none (it is
// the one body that tail-jumps, because it has nothing to push), and 0xA0 with
// one -- so the slot list is extended from 0x8C out to 0xA0. slot6C is declared
// with two parameters where the sibling file declares it empty; the arity is
// read off the two pushes at 0x0005BBB0 and only the slot INDEX has to agree
// between the two files.
//
// None of these return: retail has no `mov eax,1` before the ret, which is what
// separates them from the registrar family.
//
// Two siblings in the same family are NOT claimed here. 0x0005BBA0 (jmp slot60)
// and 0x0005BBD0 (jmp slot74) are 11 bytes of which four are the copied DIR32 of
// the global, leaving seven concrete bytes -- below MIN_LIB_CONCRETE, so the
// comparison would prove nothing.
//
// Identity is address-derived; the slots ahead of the called ones exist only to
// place them, and their signatures are invented.

class Gen001336E5C
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
	virtual void slot6C( void *a, void *b );
	virtual void slot70();
	virtual void slot74();
	virtual void slot78();
	virtual void slot7C();
	virtual void slot80();
	virtual void slot84();
	virtual void slot88();
	virtual bool registerCommand( const char *text );
	virtual void slot90();
	virtual void slot94();
	virtual void slot98();
	virtual void slot9C();
	virtual void slotA0( void *a );
};

extern Gen001336E5C *TheGen001336E5C;					///< retail [0x01336E5C]

// ?Rva0005BBB0@@YAXPAX0@Z
void Rva0005BBB0( void *a, void *b )
{
	TheGen001336E5C->slot6C( a, b );
}

// ?Rva0005BBE0@@YAXPAX@Z
void Rva0005BBE0( void *a )
{
	TheGen001336E5C->slotA0( a );
}

// ?Rva00060820@@YAXPBD@Z
void Rva00060820( const char *text )
{
	TheGen001336E5C->registerCommand( text );
}

// ?Rva0006B050@@YAXXZ
void Rva0006B050( void )
{
	TheGen001336E5C->slot90();
}
