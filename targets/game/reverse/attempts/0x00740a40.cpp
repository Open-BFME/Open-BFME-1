// ?bfmeCopyDD@BfmeHostDD@@QAEPAV1@PAVBfmeSrcDD@@@Z (identity unknown)
// partial score=0.98 date=2026-09-07
// 123/123 at exact size, TWO instructions transposed. Retail emits
//   lea ecx,[esi+0xc] / push eax        (receiver first)
// and MSVC
//   push eax / lea ecx,[esi+0xc]
// Everything else matches: the by-value string returned through an sret into
// the dead parameter slot, the set call, the temp's destructor, the 12-byte
// memberwise copy through ecx/edx and the trailing flag store.
// NOTE the receiver-local lever from [[name-the-receiver-in-a-local]] does NOT
// apply here and makes it worse: `UnicodeString *dst = &m_bfmeTextDD;` forces
// an extra callee-saved register and goes to 127 bytes. It worked on
// 0x00387060 because the argument there was a by-value parameter already in a
// slot; here the argument is an sret call result, so naming the receiver
// lengthens its live range across that call.
class UnicodeString
{
public:
	void set(const UnicodeString &other);

	~UnicodeString() { releaseBufferDD(); }

	void releaseBufferDD();

	void *m_bfmeBufDD;
};

struct BfmeBoxDD
{
	int m_bfmeADD;
	int m_bfmeBDD;
	int m_bfmeCDD;
};

class BfmeSrcDD
{
public:
	UnicodeString bfmeNameDD();

	unsigned char m_bfmeHeadDD[4];
	int m_bfmeFlagDD;
	unsigned char m_bfmePadDD[4];
	BfmeBoxDD m_bfmeBoxDD;
};

class BfmeHostDD
{
public:
	BfmeHostDD *bfmeCopyDD(BfmeSrcDD *src);

	BfmeBoxDD m_bfmeBoxDD;
	UnicodeString m_bfmeTextDD;
	int m_bfmeFlagDD;
};

BfmeHostDD *BfmeHostDD::bfmeCopyDD(BfmeSrcDD *src)
{
	m_bfmeTextDD.set(src->bfmeNameDD());

	m_bfmeBoxDD = src->m_bfmeBoxDD;
	m_bfmeFlagDD = src->m_bfmeFlagDD;

	return this;
}
