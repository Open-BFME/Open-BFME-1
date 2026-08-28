// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// Lift the WindowLayoutInfo::operator= naked dump to clean C++.
//
// There is no hand-written body here: retail copies every member in
// declaration order -- five scalars inline, then five AsciiString assignments,
// then the window list -- which is exactly the compiler-generated copy
// assignment. So the source is the class definition, and the only trick is
// forcing MSVC to emit the implicit operator out of line, which taking its
// address does.
//
// BFME widens ZH's record. Zero Hour's GameWindowManager.h has four scalars and
// three name strings; retail has five scalars at +0x00 through +0x10 and five
// AsciiStrings at +0x14 through +0x24, with the window list at +0x28. The three
// ZH names are kept for the members whose positions match; the two extra
// strings and the extra scalar are only located, not identified, so they carry
// _bfme_ names rather than invented ones.

typedef unsigned int UnsignedInt;

class GameWindow;
class WindowLayout;

typedef void (*WindowLayoutInitFunc)(WindowLayout *, void *);
typedef void (*WindowLayoutUpdateFunc)(WindowLayout *, void *);
typedef void (*WindowLayoutShutdownFunc)(WindowLayout *, void *);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString &operator=(const AsciiString &other);	///< retail body at 0x00887C90

private:
	void *m_data;
};

// std::list<GameWindow *>; only its assignment is reached from here.
class GameWindowList
{
public:
	GameWindowList &operator=(const GameWindowList &other);	///< ILT thunk at 0x00036C69

private:
	unsigned char m_unreconstructed_00[12];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowManager.h
class WindowLayoutInfo
{
public:
	UnsignedInt version;								///< retail this+0x00
	WindowLayoutInitFunc init;							///< retail this+0x04
	WindowLayoutUpdateFunc update;						///< retail this+0x08
	WindowLayoutShutdownFunc shutdown;					///< retail this+0x0C
	void *_bfme_unk_10;									///< retail this+0x10
	AsciiString initNameString;							///< retail this+0x14
	AsciiString updateNameString;						///< retail this+0x18
	AsciiString shutdownNameString;						///< retail this+0x1C
	AsciiString _bfme_unk_20;							///< retail this+0x20
	AsciiString _bfme_unk_24;							///< retail this+0x24
	GameWindowList windows;								///< retail this+0x28
};

// ??4WindowLayoutInfo@@QAEAAV0@ABV0@@Z
// Taking the address is what makes MSVC emit the implicit operator out of line
// instead of inlining it at each use.
WindowLayoutInfo &(WindowLayoutInfo::*_bfme_emit_WindowLayoutInfo_assign)(const WindowLayoutInfo &) =
		&WindowLayoutInfo::operator=;
