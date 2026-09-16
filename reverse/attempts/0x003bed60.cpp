// ?bfmeVal1025@BfmeH1025@@QAEHXZ
// partial score=0.97 date=2026-09-07
// 81/81 at exact size. The circular-list walk, the per-iteration 12-byte entry
// copy (string copy ctor plus two int copies), the accumulate and the temp's
// destructor all match. The ONLY difference is the order of the two int copies:
//   retail  mov eax,[edi+4] / mov [esp+0x14],eax / mov ecx,[edi+8] / mov [esp+0x18],ecx
//   MSVC    mov ecx,[edi+8] / mov eax,[edi+4] / mov [esp+0x18],ecx / ...
// i.e. retail does load-store, load-store and MSVC interleaves both loads first.
// Writing the entry's copy constructor out by hand in field order (member-init
// for the string, then the two assignments) does NOT change the schedule.
class StringBaseG
{
public:
	StringBaseG(const StringBaseG &other);

	~StringBaseG() { releaseBuffer(); }

	void *m_bfmeBufDC;

private:
	void releaseBuffer();
};

struct BfmeEntryDC
{
	StringBaseG m_bfmeTextDC;
	int m_bfmeCountDC;
	int m_bfmeOtherDC;
};

struct BfmeNodeDC
{
	BfmeNodeDC *m_bfmeNextDC;
	BfmeNodeDC *m_bfmePrevDC;
	BfmeEntryDC m_bfmeEntryDC;
};

class BfmeH1025
{
public:
	int bfmeVal1025();

	unsigned char m_bfmeHeadDC[0xc0];
	BfmeNodeDC *m_bfmeListDC;
};

int BfmeH1025::bfmeVal1025()
{
	int total = 0;

	for (BfmeNodeDC *n = m_bfmeListDC->m_bfmeNextDC; n != m_bfmeListDC; n = n->m_bfmeNextDC)
	{
		BfmeEntryDC e = n->m_bfmeEntryDC;

		total += e.m_bfmeCountDC;
	}

	return total;
}
