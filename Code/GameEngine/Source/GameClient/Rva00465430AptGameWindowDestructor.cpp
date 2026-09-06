// cl: /DNDEBUG /MD /EHsc

// Address-derived: 0.853 difflib match to the landed
// ??1W3DTerrainVisualBase@@UAE@XZ (Code/GameEngineDevice/Source/W3DDevice/
// GameClient/W3DTerrainVisualBaseDestructor.cpp). Same two-vtable-install
// shape (own vtable at +0, a second base's vtable at +0x218, a string
// member released via releaseBuffer), but this body's second base has a
// real out-of-line destructor (called through ILT thunk 0x00021FC1, pinned
// elsewhere as ??1Gen_dtor_004654c0@@UAE@XZ, still a dump) instead of a
// plain vtable-constant reset, and the chain finishes with an explicit call
// to GameWindow's own destructor (ILT thunk 0x0002C98F, pinned elsewhere as
// ??1GameWindow@@UAE@XZ, still a dump) rather than a Snapshot-style literal
// vtable store -- GameWindow is this class's primary (offset-0) base.
// Installs vtables 0x010F711C (own) and 0x010F7118 (second base). Symbol
// name taken from the lane brief's pin ??1_bfme_AptGameWindow@@UAE@XZ; real
// field layout beyond the two known offsets (+0x218 second base, +0x24C
// filename string) is unmodelled padding.

class GameWindow
{
public:
	virtual ~GameWindow();

private:
	unsigned char m_pad[ 0x218 - 4 ];
};

class Gen_dtor_004654c0Base
{
public:
	virtual ~Gen_dtor_004654c0Base();

private:
	unsigned char m_pad[ 0x24C - 0x218 - 4 ];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	~AsciiString();

private:
	char *m_data;
};

class _bfme_AptGameWindow : public GameWindow, public Gen_dtor_004654c0Base
{
public:
	virtual ~_bfme_AptGameWindow();

private:
	AsciiString m_filenameString;
};

// ??1_bfme_AptGameWindow@@UAE@XZ
_bfme_AptGameWindow::~_bfme_AptGameWindow()
{
}
