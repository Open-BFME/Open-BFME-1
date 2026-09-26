// Four __cdecl no-argument functions that hand one string literal to the same
// virtual slot of the same global object and return 1:
//
//     mov ecx,[<GLOBAL>] / mov eax,[ecx] / push offset <LITERAL>
//     call dword ptr [eax+8Ch] / mov eax,1 / ret
//
// WHAT THE BYTES SHOW.  `mov eax,1` is the five-byte full-register form, so the
// return type is INT (or an int-width typedef), not `bool` -- MSVC 7.1 writes
// `mov al,1` for a one-byte return, and that is two bytes.  The dispatch is
// through the vtable at a fixed slot 0x8C, i.e. the thirty-sixth entry, with
// one stack argument and __thiscall receiver, and the callee's return value is
// discarded.  The global is at 0x01336E5C in every row.
//
// THE FOUR LITERALS ARE READ OUT OF THE IMAGE and reproduced verbatim, so the
// build's verify_string_refs check has something to compare:
//
//     0x0107521C  "debug.fulldump +"
//     0x010752A8  "debug.add L + NETWORK_CRCDUMP"
//     0x010752CC  "debug.add L + GAMEREPORT"
//     0x010752EC  "debug.add L + PACKET_OVERFLOW"
//
// IDENTITY IS NOT RECOVERED.  The thirty-five slots ahead of the called one
// exist only to place it at 0x8C; their signatures are invented and the bytes
// say nothing about them.  The global's type and the callee's name are
// address-derived.

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
	virtual void slot6C();
	virtual void slot70();
	virtual void slot74();
	virtual void slot78();
	virtual void slot7C();
	virtual void slot80();
	virtual void slot84();
	virtual void slot88();
	virtual bool registerCommand( const char *text );
};

extern Gen001336E5C *TheGen001336E5C;

#define BFME_DEBUG_COMMAND_REGISTRAR( NAME, TEXT )                        	int NAME( void )                                                      	{                                                                     		TheGen001336E5C->registerCommand( TEXT );                         		return 1;                                                         	}

// @?Rva00061000@@YAHXZ 0x00061000
BFME_DEBUG_COMMAND_REGISTRAR( Rva00061000, "debug.fulldump +" )
// @?Rva000614F0@@YAHXZ 0x000614F0
BFME_DEBUG_COMMAND_REGISTRAR( Rva000614F0, "debug.add L + NETWORK_CRCDUMP" )
// @?Rva00061510@@YAHXZ 0x00061510
BFME_DEBUG_COMMAND_REGISTRAR( Rva00061510, "debug.add L + GAMEREPORT" )
// @?Rva00061530@@YAHXZ 0x00061530
BFME_DEBUG_COMMAND_REGISTRAR( Rva00061530, "debug.add L + PACKET_OVERFLOW" )
