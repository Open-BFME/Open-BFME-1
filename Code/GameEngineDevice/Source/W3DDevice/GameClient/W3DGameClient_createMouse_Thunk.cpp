// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: W3DGameClient::createMouse, retail 0x006FBA50,
// zh_sweep packet 006fba50.
//
// The reference body is the inline in W3DGameClient.h -- allocate a W3DMouse,
// publish it through the TheWin32Mouse global the WndProc reads, return it --
// and compiled against the vendored headers it already reproduced every byte
// but one immediate: retail allocates 0x5EAC bytes where the vendored W3DMouse
// is 0x5B44. BFME's is 872 bytes wider.
//
// A pure sizeof drift, so it moves to its own TU rather than widening the class
// under W3DGameClient.cpp's other 24 matched rows. Nothing else about W3DMouse
// is recovered here, so it is one opaque run rather than invented members.
//
// The constructor is ILT 0x0002B7B0, fronting the 233-byte body at 0x007003E0,
// which is still unclaimed. The null check with no EH cleanup around it is what
// `NEW` compiles to here: allocate, test, construct, and store zero to the
// global on failure.

class Mouse
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/Win32Device/GameClient/Win32Mouse.h
class Win32Mouse : public Mouse
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DMouse.h
class W3DMouse : public Win32Mouse
{
public:
	W3DMouse();												///< ILT 0x0002B7B0 -> 0x007003E0

private:
	unsigned char m_unreconstructed_00[0x5EAC];				///< sizeof 0x5EAC
};

extern Win32Mouse *TheWin32Mouse;							///< retail 0x012ED240

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DGameClient.h
class W3DGameClient
{
protected:
	virtual Mouse *createMouse( void );
};

// ?createMouse@W3DGameClient@@MAEPAVMouse@@XZ
Mouse *W3DGameClient::createMouse( void )
{
	//return new DirectInputMouse;
	Win32Mouse * mouse = ::new W3DMouse;
	TheWin32Mouse = mouse;   ///< global cheat for the WndProc()
	return mouse;
}
