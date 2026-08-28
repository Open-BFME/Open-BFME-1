// cl: /DNDEBUG /MD /EHsc

// LANGameSlot::~LANGameSlot, 0x006858A0, 89 bytes.
//
// An empty body: everything in it is member and base destruction, in reverse
// declaration order, and each of the three calls is already ledgered or
// pinned. That is also what names it. The layout it destroys is exactly the
// one LANGameSlot_operator.cpp pins from the other side --
//
//   0x00  GameSlot base, 0x44 bytes, destroyed through ??1GameSlot@@QAE@XZ
//   0x44  LANPlayer m_user, destroyed through ??1LANPlayer@@QAE@XZ (0x00685830)
//   0x60  AsciiString m_serial, released in place
//   0x64  UnsignedInt m_lastHeard, trivial
//
// -- and it lands sizeof(LANGameSlot) on 0x68, which is the per-slot stride
// LANGameInfo's slot array already uses.
//
// GameSlot is modelled as an opaque 0x44-byte block rather than the
// polymorphic class it is, and that is not cosmetic: give the model a vtable
// and MSVC opens the destructor with a six-byte vptr store retail does not
// have. LANGameSlot does have its own vtable -- its copy constructor at
// 0x00686D50 installs 0x0111B6A0 -- so the store is one MSVC emits and retail
// elided, not evidence that the class is non-polymorphic. Since the base's
// fields and virtuals are untouched here, the opaque block is all this file
// needs, and it keeps the model out of LANGameSlot_operator.cpp, whose own
// matched operator= needs GameSlot's virtual to skip the vptr.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;

template <typename T>
class StringBase
{
public:
	~StringBase() { releaseBuffer(); }

private:
	void releaseBuffer();				// ?releaseBuffer@?$StringBase@D@@AAEXXZ

	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameSlot
{
public:
	~GameSlot();					// ILT thunk 0x0000B988

	UnsignedByte m_bfmeBody[0x44];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANPlayer.h
class LANPlayer
{
public:
	~LANPlayer();					// ILT thunk 0x000240FF

	UnsignedByte m_bfmeBody[0x1C];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANGameInfo.h
class LANGameSlot : public GameSlot
{
public:
	~LANGameSlot();

private:
	LANPlayer m_user;				// this+0x44
	StringBase<char> m_serial;			// this+0x60
	UnsignedInt m_lastHeard;			// this+0x64
};

// ??1LANGameSlot@@QAE@XZ
LANGameSlot::~LANGameSlot()
{
}
