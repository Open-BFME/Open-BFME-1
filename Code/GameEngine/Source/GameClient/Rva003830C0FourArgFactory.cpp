// Address-derived. Instruction stream is a 0.873 difflib match to the landed
// ?createAptScreenLanLobby@@YGPAXPAX@Z (Code/GameEngine/Source/GameClient/
// AptScreenFactories.cpp) -- same SEH new/test/ctor/ret skeleton -- but the
// retail bytes prove a different signature: this factory is __stdcall with
// FOUR pointer-sized parameters (ret 0x10 pops 16 bytes, not ret 4), all four
// forwarded into the constructor together with a trailing literal 1, and the
// object is 0x3C4 bytes rather than LanLobby's 0x3DC. Real screen/class name
// not recovered; the constructor body at 0x001D29A0 is still unconverted and
// is reached here only through its ILT thunk 0x00047F5A.
class Rva003830C0Screen
{
public:
	Rva003830C0Screen( void *p1, void *p2, void *p3, void *p4, int one );

private:
	char m_unmodelled[ 0x3C4 ];
};

// ?createRva003830C0@@YGPAXPAX000@Z
void * __stdcall createRva003830C0( void *p1, void *p2, void *p3, void *p4 )
{
	return new Rva003830C0Screen( p1, p2, p3, p4, 1 );
}
