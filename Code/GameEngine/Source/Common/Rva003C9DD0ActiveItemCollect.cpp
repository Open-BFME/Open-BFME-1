// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Retail 0x003C9DD0, 220 bytes through the ret 4 at +0xD9 (the 208-byte row
// stopped short of its return tail).  It clears the caller's vector and, when
// the flag at +0x10 is set, appends every item of the holder's vector at
// (+4)->+0x30 whose byte at +0xA8 is set and which the object behind
// Glo012F1028 accepts (Rva003BF540::act, ILT 0x0004AC0F); true when anything
// was collected.  Its only caller is itself unnamed, so the names keep the
// address.  Indexing items[i] afresh for each use is what gives retail's
// register copy of the element before the call.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

class Gen003BD8D0Arg;

class Rva003BF540
{
public:
	bool act(Gen003BD8D0Arg *arg);
};

class Glo012F1028Type;
extern Glo012F1028Type *Glo012F1028;

struct Rva003C9DD0Item
{
	char m_unmodelled00[0xA8];
	bool m_activeA8;
};

struct Rva003C9DD0Holder
{
	char m_unmodelled00[0x30];
	_STL::vector<Rva003C9DD0Item *> m_items;
};

class Rva003C9DD0Owner
{
public:
	bool collect(_STL::vector<Rva003C9DD0Item *> &out);

private:
	void *m_vptr;
	Rva003C9DD0Holder *m_holder;
	char m_unmodelled08[8];
	bool m_enabled10;
};

bool Rva003C9DD0Owner::collect(_STL::vector<Rva003C9DD0Item *> &out)
{
	out.clear();
	if (!m_enabled10)
		return false;

	_STL::vector<Rva003C9DD0Item *> &items = m_holder->m_items;
	for (unsigned int i = 0; i < items.size(); ++i)
	{
		if (items[i]->m_activeA8 && ((Rva003BF540 *)Glo012F1028)->act((Gen003BD8D0Arg *)items[i]))
			out.push_back(items[i]);
	}

	return out.size() > 0;
}
