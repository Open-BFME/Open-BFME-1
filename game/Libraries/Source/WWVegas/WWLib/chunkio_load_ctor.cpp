// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep
//
// ChunkLoadClass's constructor -- retail 0x009E1320, 91 bytes.
//
// It is the clearest statement of how far BFME's ChunkLoadClass drifted from
// the Zero Hour reference: the argument lands at +0x04, not +0x00, because BFME
// put a second stream pointer in front of WWLib's FileClass. So every field
// after it sits four bytes further along than chunkio.h says -- StackIndex at
// +0x08, PositionStack at +0x0c, HeaderStack at +0x40c, InMicroChunk at +0xc0c,
// MicroChunkPosition at +0xc10 and the micro-chunk header at +0xc14. That is
// exactly the layout chunkio.cpp's already-matched readers cast to, and this
// confirms it from the other end.
//
// It lives in its own translation unit because chunkio.cpp compiles against
// chunkio.h, whose ChunkLoadClass still has the reference layout; the readers
// there reach the real fields through a cast. A constructor cannot do that --
// the member array's element constructors and the compiler's own initialisation
// order come from the class declaration itself, so the class has to be declared
// with the retail layout.
//
// The argument is BFME's own stream interface rather than WWLib's FileClass:
// the caller in Open_W3D_File hands it what that function returns, and retail
// zeroes the FileClass slot at +0x00. BFMEChunkInput is the name chunkio.cpp
// already uses for that interface.
#include <string.h>

typedef unsigned int uint32;
typedef unsigned char uint8;

class BFMEChunkInput;
class FileClass;

// Local copies rather than chunkio.h's, which would drag in the reference
// ChunkLoadClass and collide with the one below. Both must construct exactly as
// the reference does: ChunkHeader zeroes its two words -- that is the 256-pass
// loop ahead of the constructor body -- and MicroChunkHeader does nothing.
struct ChunkHeader
{
	ChunkHeader() : ChunkType(0), ChunkSize(0) {}

	uint32 ChunkType;
	uint32 ChunkSize;
};

struct MicroChunkHeader
{
	MicroChunkHeader() {}

	uint8 ChunkType;
	uint8 ChunkSize;
};

class ChunkLoadClass
{
public:
	ChunkLoadClass( BFMEChunkInput *input );

private:
	enum { MAX_STACK_DEPTH = 256 };

	FileClass *File;							// +0x00
	BFMEChunkInput *Input;						// +0x04
	int StackIndex;								// +0x08
	uint32 PositionStack[MAX_STACK_DEPTH];		// +0x0c
	ChunkHeader HeaderStack[MAX_STACK_DEPTH];	// +0x40c
	bool InMicroChunk;							// +0xc0c
	int MicroChunkPosition;						// +0xc10
	MicroChunkHeader MCHeader;					// +0xc14
};

// ??0ChunkLoadClass@@QAE@PAVBFMEChunkInput@@@Z
// The first three go in the initialiser list, not the body: members are
// initialised in declaration order, so that is what puts their stores ahead of
// HeaderStack's two hundred and fifty six element constructors, which is where
// retail has them.
ChunkLoadClass::ChunkLoadClass( BFMEChunkInput *input ) :
	File( 0 ),
	Input( input ),
	StackIndex( 0 )
{
	InMicroChunk = false;
	MicroChunkPosition = 0;

	memset( PositionStack, 0, sizeof( PositionStack ) );
	memset( HeaderStack, 0, sizeof( HeaderStack ) );

	memset( &MCHeader, 0, sizeof( MCHeader ) );
}
