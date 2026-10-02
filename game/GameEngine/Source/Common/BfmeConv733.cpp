// The call at 0x0020D280 is StringBase<char>'s private copy constructor at
// 0x00887B60 (game/Libraries/Source/string/StringBase.cpp): ecx becomes the
// receiver and the owner's narrow string address is the single stack argument.
// The base copy ctor is private, which is what mangles it AAE, so - exactly as
// Bfme5MatPassCtors.cpp does - it is named through a declaration-only copy of
// the template that grants this translation unit friendship.  No body is
// redeclared here; the body stays in StringBase.cpp.

template <typename Char>
class StringBase
{
	friend class BfmeThingDNA;
	StringBase(const StringBase<Char> &src);
};

class BfmeOtherDNA
{
public:
	char m_bfmeHead[4];
};

struct BfmeOwnerDNA
{
	unsigned char m_bfmeHead[8];
	StringBase<char> m_bfmeSub;
};

struct BfmeThingDNA
{
	BfmeOtherDNA *bfmeGoDNA(BfmeOtherDNA *other);
};

BfmeOtherDNA *BfmeThingDNA::bfmeGoDNA(BfmeOtherDNA *other)
{
	volatile int tmp = 0;
	BfmeOwnerDNA *owner = *(BfmeOwnerDNA **)((char *)this - 0x1c);
	reinterpret_cast<StringBase<char> *>(other)->StringBase<char>::StringBase(
		*reinterpret_cast<const StringBase<char> *>(&owner->m_bfmeSub));
	return other;
}