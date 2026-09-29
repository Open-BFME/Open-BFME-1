// BfmeVec60::resize(n) at 0x00880400 (59 B), the one-argument overload of the
// matched resize(n, value) at 0x00880260 (Rva00880260Resize.cpp): STLport's
// `resize(__new_size, _Tp())`. Retail builds the default element inline in the
// by-value argument slot (0, three 1.0f, four zero dwords, flag 1 at +0x20)
// and passes this straight through in ecx. That TU is /Ob0, so the default
// constructor cannot inline there; this body lives in its own TU.
//
// Building the temporary straight into the argument slot needs a copyable
// member with a user copy constructor: a trivially copyable element is built
// on the side and copied with rep movsd, and a destructor adds an unwind slot
// (mov [esp+24h], esp) that retail does not have.

struct BfmeTail60
{
	BfmeTail60() : m_p(0) {}
	BfmeTail60(const BfmeTail60 &other);
	char *m_p;
};

struct BfmeElem60
{
	BfmeElem60()
		: m_00(0), m_04(1.0f), m_08(1.0f), m_0C(1.0f), m_10(0), m_14(0), m_18(0), m_20(true)
	{
	}

	int m_00;
	float m_04;
	float m_08;
	float m_0C;
	int m_10;
	int m_14;
	int m_18;
	BfmeTail60 m_1C;
	bool m_20;
};

class BfmeVec60
{
public:
	void resize(unsigned n, BfmeElem60 value);
	void resize(unsigned n);
};

// ?resize@BfmeVec60@@QAEXI@Z
void BfmeVec60::resize(unsigned n)
{
	resize(n, BfmeElem60());
}
