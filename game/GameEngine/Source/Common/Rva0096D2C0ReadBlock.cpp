// cl: /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WW3D2
#include "chunkio.h"

// Address-derived stand-in for retail's ChunkLoadClass, kept because the
// matched body's own mangled name embeds this spelling. The Read call below
// goes through the real ChunkLoadClass declaration from chunkio.h.
class BfmeChunkVFC
{
};

struct Rva0096D2C0Record
{
	char m_pad00[0x78];
	int m_value78;
	char m_tail7C[12];
};

class Rva0096D2C0Owner
{
public:
	bool readBlock(BfmeChunkVFC *loader, Rva0096D2C0Record *record);

private:
	char m_pad00[0x9C];
	int *m_destination;
};

bool Rva0096D2C0Owner::readBlock(BfmeChunkVFC *loader, Rva0096D2C0Record *record)
{
	if (reinterpret_cast<ChunkLoadClass *>(loader)->Read(&record->m_value78, 16) != 16)
		return false;

	*m_destination = record->m_value78;
	return true;
}
