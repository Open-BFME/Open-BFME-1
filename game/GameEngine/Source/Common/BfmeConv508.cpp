// Retail's +0x0E call target at 0x00887B60 is the shared StringBase<char> copy
// body (game/Libraries/Source/string/StringBase.cpp, object symbol
// ??0?$StringBase@D@@AAE@ABV0@@Z, pinned 0x00887B60). The copy ctor's object
// symbol carries the protected code, and MSVC 7.1 mangles a *private* member
// reached through a friend declaration with that same protected code, so the
// member below mirrors the real WWLib string_base.h: private copy ctor plus a
// friend declaration for this class. This TU is /Ob0, where the explicit
// copy-ctor call cannot be inlined away, and MSVC 7.1 accepts it as an ordinary
// statement with the retail argument/this sequence (push src+4; lea ecx,this+4).
// Retail's subobject is a full 8-byte StringBase<char> -- the copy body reads its
// header through this+4 -- not the 4-byte stand-in the previous source used.
class BfmeThingBPD;

template <typename T>
class StringBase
{
private:
	StringBase(const StringBase<T> &src);
	friend class BfmeThingBPD;

	void *m_data;
};

struct BfmeSrcBPD
{
	unsigned char m_bfmeKind;
	unsigned char m_bfmePad[3];
	unsigned char m_bfmeRest[4];
};

class BfmeThingBPD
{
public:
	BfmeThingBPD *bfmeGoBPD(BfmeSrcBPD *src);

private:
	unsigned char m_bfmeKind;
	unsigned char m_bfmePad[3];
	StringBase<char> m_bfmeSub;
};

BfmeThingBPD *BfmeThingBPD::bfmeGoBPD(BfmeSrcBPD *src)
{
	m_bfmeKind = src->m_bfmeKind;
	m_bfmeSub.StringBase<char>::StringBase(*(StringBase<char> *)&src->m_bfmeRest);
	return this;
}
