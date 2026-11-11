// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// ??1Rva0077CDE0ArrElem@@QAE@XZ, retail 0x00141CC0 (5 bytes).
//
// ThingTemplate's constructor hands the eh vector constructor iterator the
// element constructor/destructor ILT pair 0x0002FB80 / 0x0000E746 for its
// two-element array at +0x134. 0x0002FB80 jumps to 0x00143B20, the 0x14-byte
// set-group constructor (??0BfmeList950B@@QAE@XZ: allocates the 0x14-byte
// tree header node, count +0x0C = 0, flag +0x10 = 1); 0x0000E746 jumps to
// 0x00141CC0. That body is a single padded `jmp 0x00015D7A`, the ILT of the
// pointer-set tree destructor 0x00140950
// (??1?$_Rb_tree@PAURva001408C0Target@@...), so the element destructor does
// nothing but destroy the set at +0x00: the 0x14-byte group of
// AssetRegistryKeySet009EF7D0.cpp (set, count, active flag).
//
// The class keeps the address-derived name its consumers already call; the
// element type is the same group other TUs view as BfmeList950B.

#include <set>

struct Rva001408C0Target;

class Rva0077CDE0ArrElem
{
public:
	~Rva0077CDE0ArrElem();

private:
	_STL::set<Rva001408C0Target *> m_set;
	unsigned int m_count;
	bool m_active;
	unsigned char m_padding[3];
};

Rva0077CDE0ArrElem::~Rva0077CDE0ArrElem()
{
}
