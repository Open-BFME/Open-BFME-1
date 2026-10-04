// Open-BFME5 conversions.

class BfmeOwnVLL;

bool bfmeCheckVLL(BfmeOwnVLL *p);

// Retail 0x0083E8F0 is STLport 4.5.3's ios_base::_M_throw_failure, owned by
// game/Libraries/Source/WWVegas/WWLib/stlport_ios_base_throw_failure.cpp, and
// 0x00030B11 is a 5-byte ILT thunk owned by game/gen_small/thunks_023.cpp
// (j_00030b11).  Both bfmeNotifyVLL/bfmeKickVLL were pins for those addresses,
// not definitions, so reference the owners and cast at the calls.
namespace _STL {
// STLport 4.5.3 declares _M_throw_failure protected; the mangled owner is
// ?_M_throw_failure@ios_base@_STL@@IAEXXZ.  The checker is a friend so the
// call site stays a plain thiscall member call.
class ios_base
{
protected:
	void _M_throw_failure();

	friend bool ::bfmeCheckVLL(BfmeOwnVLL *);
};
}

extern void j_00030b11();

typedef void (__fastcall *Rva00030B11Kick)(void *self);

class BfmeCtlVLL
{
public:
	int m_bfme00;
	int m_bfme04;
	int m_bfme08;
	int m_bfme0c;
	int m_bfme10;
	int m_bfme14;
	char m_bfmePad18[0x40];
	void *m_bfme58;
	void *m_bfme5c;
};

struct BfmeVbVLL
{
	int m_bfme00;
	int m_bfme04;
};

class BfmeOwnVLL
{
public:
	BfmeVbVLL *m_bfme00;
};

static BfmeCtlVLL *bfmeBaseVLL(BfmeOwnVLL *p)
{
	return (BfmeCtlVLL *)((char *)p + p->m_bfme00->m_bfme04);
}

bool bfmeCheckVLL(BfmeOwnVLL *p)
{
	if (bfmeBaseVLL(p)->m_bfme08 == 0)
	{
	if (bfmeBaseVLL(p)->m_bfme58 == 0)
	{
		BfmeCtlVLL *b = bfmeBaseVLL(p);
		int f = b->m_bfme08 | 1;
		if (b->m_bfme58 == 0)
			f |= 1;
		b->m_bfme08 = f;
		if ((b->m_bfme14 & f) != 0)
			((_STL::ios_base *)b)->_M_throw_failure();
	}
	if (bfmeBaseVLL(p)->m_bfme5c != 0)
		(reinterpret_cast<Rva00030B11Kick>(j_00030b11))(bfmeBaseVLL(p)->m_bfme5c);
	return bfmeBaseVLL(p)->m_bfme08 == 0;
	}
	return false;
}
