// Open-BFME5 conversions.

class BfmeK1105;
struct BfmeNode1105;

// The node step at 0x0082B870 is STLport's _Rb_global<bool>::_M_increment, the
// only name defined at that address (game/Libraries/Source/WWVegas/WWLib/
// STLRbGlobalBoolIncrementThunk.cpp), so reference that mangled name: it is a
// static __cdecl member taking the node pointer, exactly the call this file makes.
// The drop at 0x0000CEA5 is the retail five-byte ILT thunk to FUN_007b9450, so
// the only name defined there is its ?j_ thunk symbol (game/gen_small/thunks_005.cpp).
extern "C" BfmeNode1105 *__cdecl __identifier(
	"?_M_increment@?$_Rb_global@_N@_STL@@SAPAU_Rb_tree_node_base@2@PAU32@@Z")(
	BfmeNode1105 *);
extern "C" void __cdecl __identifier("?j_0000cea5@@YAXXZ")();

typedef void (__fastcall *BfmeDrop1105Thunk)(BfmeK1105 *);

class BfmeK1105
{
};

struct BfmeNode1105
{
	char m_bfmePad[8];
	BfmeNode1105 *m_bfme08;
	char m_bfmePad1[4];
	int m_bfme10;
	BfmeK1105 *m_bfme14;
};

class BfmeW1105
{
public:
	void bfmeGo1105A(void);
	int *bfmeGo1105C(int n);
	BfmeNode1105 *m_bfme00;
};

void BfmeW1105::bfmeGo1105A(void)
{
	BfmeNode1105 *h = m_bfme00;
	BfmeNode1105 *p = h->m_bfme08;

	while (p != h) {
		if (p->m_bfme14)
			((BfmeDrop1105Thunk)__identifier("?j_0000cea5@@YAXXZ"))(p->m_bfme14);
		p = __identifier(
			"?_M_increment@?$_Rb_global@_N@_STL@@SAPAU_Rb_tree_node_base@2@PAU32@@Z")(p);
		h = m_bfme00;
	}
}

int *BfmeW1105::bfmeGo1105C(int n)
{
	BfmeNode1105 *h = m_bfme00;
	BfmeNode1105 *p = h->m_bfme08;

	while (p != h) {
		if (!n)
			return &p->m_bfme10;
		p = __identifier(
			"?_M_increment@?$_Rb_global@_N@_STL@@SAPAU_Rb_tree_node_base@2@PAU32@@Z")(p);
		h = m_bfme00;
		n--;
	}
	return 0;
}
