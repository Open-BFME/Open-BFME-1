// cl: /DNDEBUG /MD /G6 /EHsc
//
// Retail 0x0096DC80 checks a chunk's length against 12x the stride at
// this+0x24: it triples the stride (lea esi,[eax+eax*2]), quadruples it,
// compares against Cur_Chunk_Length at 0x009E1450, and on equality seeks to
// the width through Seek at 0x009E1500. The positive-guard spelling (`==`
// with the seek inside the arm) is what emits retail's `jne miss / push /
// call Seek / ... / mov al,1 / ... / xor al,al` tails; the early-return
// spelling inverts the first branch and merges the miss tail. Both callees
// are matched real-source bodies in chunkio.cpp, so no new pin is needed.
// IDENTITY IS NOT RECOVERED: the owner keeps its address token.
class ChunkLoadClass
{
public:
	unsigned long Cur_Chunk_Length();
	unsigned long Seek(unsigned long count);
};

class Rva0096DC80Box
{
public:
	unsigned char checkLen(ChunkLoadClass *loader, unsigned long tag);
	int m_pad[9];
	int m_stride;
};

unsigned char Rva0096DC80Box::checkLen(ChunkLoadClass *loader, unsigned long tag)
{
	(void)tag;
	int n = m_stride;
	int wide = n + n * 2;
	wide <<= 2;
	if (loader->Cur_Chunk_Length() == (unsigned long)wide)
	{
		loader->Seek((unsigned long)wide);
		return 1;
	}
	return 0;
}
