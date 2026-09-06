// cl: /DNDEBUG /MD /EHsc
// Open-BFME: WindowLayoutInfo's destructor at retail 0x00460540.
//
// Layout proven by the sibling landed body WindowLayoutInfoAssignmentThunk.cpp
// (WindowLayoutInfo::operator=): five scalars at +0x00..+0x10, five
// AsciiStrings at +0x14..+0x24, then the top-level-window list at +0x28.
// Zero Hour's GameWindowManager.h has only three name strings and four
// scalars; BFME widened the record by one scalar and two strings (the extra
// fields are only located, not identified, hence the _bfme_ names).
//
// The destructor body is implicit (no explicit statements): five AsciiString
// releaseBuffer() calls in reverse declaration order, then the window list's
// own destructor, which is why the only callees are releaseBuffer (x5) and
// the STL _List_base<GameWindow*> destructor (pinned in symbols.csv as the
// GameWindowManager dtor call target for 0x00040278).

class GameWindow;

namespace _STL
{
	template <class T>
	class allocator
	{
	};

	template <class Type, class Allocator>
	class _List_base
	{
	public:
		~_List_base();
	};

	template <class Type, class Allocator>
	class list : public _List_base<Type, Allocator>
	{
	public:
		~list() {}
	};
}

typedef _STL::list<GameWindow *, _STL::allocator<GameWindow *> > GameWindowList;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class BFMERetailAsciiString
{
public:
	~BFMERetailAsciiString() { releaseBuffer(); }

private:
	void releaseBuffer();	///< retail body at 0x00887940
	void *m_data;
};

typedef unsigned int UnsignedInt;
class WindowLayout;
typedef void (*WindowLayoutInitFunc)(WindowLayout *, void *);
typedef void (*WindowLayoutUpdateFunc)(WindowLayout *, void *);
typedef void (*WindowLayoutShutdownFunc)(WindowLayout *, void *);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowManager.h
class WindowLayoutInfo
{
public:
	~WindowLayoutInfo();

	UnsignedInt version;								///< retail this+0x00
	WindowLayoutInitFunc init;							///< retail this+0x04
	WindowLayoutUpdateFunc update;						///< retail this+0x08
	WindowLayoutShutdownFunc shutdown;					///< retail this+0x0C
	void *_bfme_unk_10;									///< retail this+0x10
	BFMERetailAsciiString initNameString;				///< retail this+0x14
	BFMERetailAsciiString updateNameString;			///< retail this+0x18
	BFMERetailAsciiString shutdownNameString;			///< retail this+0x1C
	BFMERetailAsciiString _bfme_unk_20;					///< retail this+0x20
	BFMERetailAsciiString _bfme_unk_24;					///< retail this+0x24
	GameWindowList windows;								///< retail this+0x28
};

// ??1WindowLayoutInfo@@QAEXXZ (candidate; identity unproven beyond layout match)
WindowLayoutInfo::~WindowLayoutInfo()
{
}
