// ?bfmeAssignAU@BfmeOwnAU@@QAEXABVUnicodeString@@@Z (identity unknown)
// partial score=0.83 date=2026-09-06
// 38/46 at exact size. Both arms are byte-correct in isolation, including the
// self-store `mov [esp+4],edx` that precedes the tail jmp into
// ?set@UnicodeString@@QAEXABV1@@Z and the `add ecx,0x2d8` receiver adjust in
// each. The residue is arm ORDER: retail puts the releaseBuffer arm inline
// and jumps forward to the set arm, MSVC always emits the tail-jmp arm first.
// Tried if/else both polarities and early-return forms of each; all three
// give the identical eight-line diff, so this is the known
// MSVC-orders-arms-itself class.
// releaseBuffer is private (AAE) on BFMERetailAsciiString, so it needs its own
// public pin name at 0x00887940 rather than the retail symbol.
class BfmeStrDataAU
{
public:
	unsigned char m_bfmeHeadAU[4];
	short m_bfmeLenAU;
};

class UnicodeString
{
public:
	void set(const UnicodeString &other);
	void bfmeReleaseAU(void);

	BfmeStrDataAU *m_bfmeDataAU;
};

class BfmeOwnAU
{
public:
	void bfmeAssignAU(const UnicodeString &value);

	unsigned char m_bfmeHeadAU[0x2d8];
	UnicodeString m_bfmeTextAU;
};

void BfmeOwnAU::bfmeAssignAU(const UnicodeString &value)
{
	if (value.m_bfmeDataAU == 0 || value.m_bfmeDataAU->m_bfmeLenAU == 0)
		m_bfmeTextAU.bfmeReleaseAU();
	else
		m_bfmeTextAU.set(value);
}
