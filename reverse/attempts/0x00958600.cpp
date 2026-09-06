// ?bfmeNextBO@BfmeOwnBO@@QAEHXZ (identity unknown)
// partial score=0.8 date=2026-09-06
// 38 bytes in retail, 40 from MSVC. Structure is certain: grow when the index
// has reached the limit, then return base + stride * index and post-increment
// the index.
// Residue: retail keeps the index in ecx and uses `inc ecx` (1 byte) before
// storing it, loading the base into edx BEFORE the multiply. MSVC computes
// `lea edx,[ecx+1]` (3 bytes) and defers the base load into ecx. Tried named
// locals for all three members in retail's load order, pre-increment folded
// into the store, and both operand orders of the add. All give the same
// two-byte-larger body.
class BfmeOwnBO
{
public:
	int bfmeNextBO(void);
	void bfmeGrowBO(void);

	unsigned char m_bfmeHeadBO[4];
	int m_bfmeStrideBO;
	int m_bfmeLimitBO;
	int m_bfmeBaseBO;
	unsigned char m_bfmePadBO[4];
	int m_bfmeIndexBO;
};

int BfmeOwnBO::bfmeNextBO(void)
{
	if (m_bfmeIndexBO >= m_bfmeLimitBO)
		bfmeGrowBO();

	int index = m_bfmeIndexBO;
	int stride = m_bfmeStrideBO;
	int origin = m_bfmeBaseBO;
	int value = stride * index;

	value += origin;
	++index;
	m_bfmeIndexBO = index;

	return value;
}
