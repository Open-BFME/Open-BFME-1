// Open-BFME5 conversions.

// Retail reaches the node-finaliser at 0x000097BE and the unlink helper at
// 0x00014FE7 through their own incremental-link thunks, both named
// ?j_<rva>@@YAXXZ in the ledger and defined under that name by the
// gen-thunk TUs.  A thiscall member call can never carry a cdecl thunk's
// symbol, so each is invoked through a typed member-function pointer (the
// convention MapMetaData_assign.cpp already uses) which keeps the retail
// ECX/stack ABI and the call target address unchanged.
extern void j_000097be(void);
extern void j_00014fe7(void);

// The list node's key object; retail never names its type here.
class BfmeK1111
{
public:
};

class BfmeE1111
{
public:
	virtual void bfmeSlot1111E_0(int a);
};

struct BfmeNode1111
{
	char m_bfmePad[8];
	BfmeNode1111 *m_bfme08;
	char m_bfmePad1[8];
	BfmeK1111 *m_bfme14;
};

// Retail 0x0082B870 is STLport's _STL::_Rb_global<bool>::_M_increment, defined
// under its real mangled name in WWLib/STLRbGlobalBoolIncrementThunk.cpp.
namespace _STL
{

struct _Rb_tree_node_base
{
};

template <class T>
struct _Rb_global
{
	static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base *);
};

}

// Retail 0x00881EB0 is the game's global single-object operator delete, as
// defined in WWLib/mem_ops.cpp.
extern void __cdecl operator delete(void *p);

struct BfmeVt1111
{
	char m_bfmePad[0x28];
	void (__stdcall *m_bfme28)(BfmeE1111 *e);
};

class BfmeW1111
{
public:
	void bfmeGo1111A(void);
	BfmeVt1111 *m_bfmeVt;
	char m_bfmePad0[4];
	BfmeE1111 *m_bfme08;
	char m_bfmePad1[0x10];
	BfmeNode1111 *m_bfme1c;
};

void BfmeW1111::bfmeGo1111A(void)
{
	BfmeNode1111 *h = m_bfme1c;
	BfmeNode1111 *p = h->m_bfme08;
	BfmeE1111 *e;

	while (p != h) {
		BfmeK1111 *k = p->m_bfme14;

		if (k) {
			typedef void (BfmeK1111::*EndFunction)(void);
			union {
				void (*raw)(void);
				EndFunction member;
			} fnEnd;

			fnEnd.raw = j_000097be;
			(k->*fnEnd.member)();
			::operator delete(k);
		}
		p = (BfmeNode1111 *)_STL::_Rb_global<bool>::_M_increment(
			(_STL::_Rb_tree_node_base *)p);
		h = m_bfme1c;
	}
	e = m_bfme08;
	while (e) {
		typedef void (BfmeW1111::*UnlinkFunction)(BfmeE1111 *e);
		union {
			void (*raw)(void);
			UnlinkFunction member;
		} fnUnlink;

		fnUnlink.raw = j_00014fe7;
		(this->*fnUnlink.member)(e);
		m_bfmeVt->m_bfme28(e);
		if (e)
			e->bfmeSlot1111E_0(1);
		e = m_bfme08;
	}
}