// cl: /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WW3D2
// Open-BFME5 conversions.

#include "chunkio.h"

extern "C" void *memset(void *d, int c, unsigned n);
#pragma intrinsic(memset)

// Address-derived stand-in for retail's ChunkLoadClass, kept because the
// matched body's own mangled name embeds this spelling. Every call goes
// through the real ChunkLoadClass declaration from chunkio.h: retail ILT
// targets 0x009E1380/0x009E1440/0x009E13E0 are the matched Open_Chunk,
// Cur_Chunk_ID and Close_Chunk.
class BfmeChunkVHT;

class BfmeThingVHT
{
public:
	char bfmeLoadVHT(BfmeChunkVHT *c);
	char m_bfmePad[0x18];
	char m_bfmeData[0x14c];
};

char BfmeThingVHT::bfmeLoadVHT(BfmeChunkVHT *c)
{
	char ok = 0;
	ChunkLoadClass *chunk = reinterpret_cast<ChunkLoadClass *>(c);
	if (chunk->Open_Chunk())
	{
		if (chunk->Cur_Chunk_ID() == 0x503)
		{
			memset(m_bfmeData, 0, 0x14c);
			if (chunk->Read(m_bfmeData, 0x14c) == 0x14c)
				ok = 1;
			chunk->Close_Chunk();
		}
	}
	return ok;
}
