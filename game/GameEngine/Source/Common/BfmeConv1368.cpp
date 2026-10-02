// cl: /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WW3D2
// Open-BFME5 conversions.

#include "chunkio.h"

extern "C" void *memset(void *d, int c, unsigned n);
#pragma intrinsic(memset)

// Address-derived stand-in for retail's ChunkLoadClass, kept because the
// matched body's own mangled name embeds this spelling. The read goes through
// the real ChunkLoadClass declaration from chunkio.h.
class BfmeChunkVHT
{
public:
	bool bfmeOpenVHT();
	unsigned bfmeCurIdVHT();
	void bfmeCloseVHT();
};

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
	if (c->bfmeOpenVHT())
	{
		if (c->bfmeCurIdVHT() == 0x503)
		{
			memset(m_bfmeData, 0, 0x14c);
			if (reinterpret_cast<ChunkLoadClass *>(c)->Read(m_bfmeData, 0x14c) == 0x14c)
				ok = 1;
			c->bfmeCloseVHT();
		}
	}
	return ok;
}
