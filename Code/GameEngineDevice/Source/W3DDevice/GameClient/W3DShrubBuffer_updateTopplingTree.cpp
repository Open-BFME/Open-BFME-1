// ?updateTopplingTree@W3DShrubBuffer@@IAEXH@Z
// BFME W3DShrubBuffer indexed toppling update at retail 0x0071D9F0.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

extern Real g_bfmeDefaultBU;
extern Real g_bfmeUint32Scale;

struct TopplingTypeView
{
	char m_pad00[0x4c];
	UnsignedInt m_toppleFrames;
};

struct TopplingTreeView
{
	char m_pad00[0x40];
	Int m_treeType;
	char m_pad44[0x50];
	UnsignedInt m_sinkFrames;
	Int m_toppleState;
	Int m_pushAside;
	char m_padA0[4];
};

extern void j_00015f7d(void);
extern void j_000246a4(void);

class W3DShrubBuffer
{
protected:
	void updateTopplingTree(Int treeIndex);

private:
	char m_pad00[0x1548];
	TopplingTreeView m_trees[12000];
	Int m_numTrees;
};

void W3DShrubBuffer::updateTopplingTree(Int treeIndex)
{
	char *treeBytes = reinterpret_cast<char *>(this) + treeIndex * 0xa4;
	Int treeType = m_trees[treeIndex].m_treeType;
	if (treeIndex >= m_numTrees)
		return;
	if (treeType < 0)
		return;

	UnsignedInt &sinkFrames = *reinterpret_cast<UnsignedInt *>(treeBytes + 0x15dc);
	--sinkFrames;

	TopplingTypeView *typeData = *reinterpret_cast<TopplingTypeView **>(
		reinterpret_cast<char *>(this) + (treeType + 0x53cb) * 0x5c);
	UnsignedInt toppleFrames = typeData->m_toppleFrames;
	Real progress = static_cast<Real>(sinkFrames) / static_cast<Real>(toppleFrames);

	union
	{
		void (*function)(void);
		void (*withArguments)(void *, Real);
	} forwardCast;
	forwardCast.function = j_000246a4;
	Int toppleState = *reinterpret_cast<Int *>(treeBytes + 0x15e0);
	if (toppleState)
	{
		forwardCast.withArguments(reinterpret_cast<void *>(toppleState), progress);
	}

	Int pushAside = *reinterpret_cast<Int *>(treeBytes + 0x15e4);
	if (pushAside)
	{
		forwardCast.withArguments(reinterpret_cast<void *>(pushAside), g_bfmeDefaultBU - progress);
	}

	if (sinkFrames == 0)
	{
		union
		{
			void (*function)(void);
			void (W3DShrubBuffer::*member)(Int);
		} removeCast;
		removeCast.function = j_00015f7d;
		(this->*removeCast.member)(treeIndex);
	}
}
