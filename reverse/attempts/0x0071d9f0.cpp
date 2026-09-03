// ?updateTopplingTree@W3DTreeBuffer@@IAEXH@Z
// partial score=0.7 date=2026-09-03
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x0071D9F0 (193 bytes). Update one toppling tree by index.

void Rva00739900Forward(void *, float);
void j_00015f7d(void);
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

struct TopplingTreeView
{
	char m_pad00[0x40];
	int m_treeType;
	char m_pad44[0x50];
	int m_sinkFrames;
	int m_toppleState;
	int m_pushAside;
	char m_padA0[4];
};

struct TopplingTypeView
{
	char m_pad00[0x4c];
	int m_toppleFrames;
};

class W3DTreeBuffer
{
protected:
	void updateTopplingTree(int treeIndex);
	void removeTreeAtIndex(int treeIndex);

private:
	char m_pad00[0x1548];
	TopplingTreeView m_trees[12000];
	int m_numTrees;
	char m_padAfterCount[0x28];
};

void W3DTreeBuffer::updateTopplingTree(int treeIndex)
{
	int treeType = m_trees[treeIndex].m_treeType;
	char *treeBytes = reinterpret_cast<char *>(this) + treeIndex * 0xa4;
	if (treeIndex >= m_numTrees || treeType < 0)
		return;

	int &sinkFrames = *(int *)(treeBytes + 0x15dc);
	--sinkFrames;
	float progress = (float)sinkFrames;
	if (sinkFrames < 0)
		progress += 0.5f;

	char *typeData = *reinterpret_cast<char **>(
		reinterpret_cast<char *>(this) + (treeType + 0x53cb) * 0x5c);
	int toppleFrames = *(int *)(typeData + 0x4c);
	float total = (float)toppleFrames;
	if (toppleFrames < 0)
		total += 0.5f;
	progress /= total;

	int toppleState = *(int *)(treeBytes + 0x15e0);
	if (toppleState)
		Rva00739900Forward((void *)toppleState, progress);

	int pushAside = *(int *)(treeBytes + 0x15e4);
	if (pushAside)
		Rva00739900Forward((void *)pushAside, 1.0f - progress);

	if (sinkFrames == 0)
		removeTreeAtIndex(treeIndex);
}
