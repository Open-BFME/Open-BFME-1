// ?rva00591b60@AptPalantirStore@@QAEXXZ
// partial score=0.40 date=2026-09-12
// cl: /O2 /Oy /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
//
// Same field layout as the already-landed AptPalantirStore::clear (0x005918F0):
// m_secondTree at +0x1C, m_firstTree at +0x10, flag at +4. When the guard
// fails it tail-calls the real clear() (confirmed: 0x0002F801 -> j_0002f801
// -> 0x005918F0).
//
// GUARD IDENTITY UPGRADED THIS SESSION (2026-09-12): the guard object is NOT
// an invented "Rva00591B60Guard" -- it is the real global
// ?TheLivingWorldLogic@@3PAVCampaignObject@@A at 0x012F1028 (already pinned
// in symbols.csv), confirmed independently by
// GameLogic::_bfme_isInLivingWorldCampaign (0x00382B50), which reads the
// SAME global and the SAME +0x2C byte as a bool guard
// (`mov eax,[0x12f1028]; test eax,eax; je ...; mov cl,[eax+0x2c]; test cl,cl`).
// This body additionally reads +0x2D. Use `class CampaignObject` (real name)
// with the two bool fields at +0x2C/+0x2D, not a placeholder guard struct.
//
// RULED OUT THIS SESSION: the standing theory that the byte gap was a
// cross-TU symbol-resolution problem ("redeclaring the template locally
// makes the build synthesize a fresh local out-of-line copy instead of
// reusing retail's shared instance"). Tested directly: placed this method
// INSIDE Code/GameEngine/Source/GameClient/GUI/AptPalantirStoreClear.cpp
// itself (the same TU as the already-landed, byte-exact AptPalantirStore
// ::clear(), reusing its EXACT _STL::_Rb_tree/Gen_t_00234730_m4pod/
// AptPalantirStore class verbatim, only adding a `size()` accessor and this
// new method) -- probe.py still reports ours=215, retail=170, IDENTICAL to
// the earlier standalone-TU result. Same-TU placement changes nothing, so
// this is not a symbol-resolution/COMDAT-sharing issue.
//
// REFINED DIAGNOSIS: the gap is entirely inside the erase phase of
// `m_secondTree.clear()` (the same __forceinline _Rb_tree::clear() that
// AptPalantirStore::clear() ALSO calls twice, byte-exact both times there).
// Measuring the equivalent byte range: retail's erase phase (value-clear
// loop end through the node_count/notEmpty checks) is +0x43..+0x81 = 0x3E
// (62) bytes; ours for the SAME logical code is +0x44..+0xa9 = 0x65 (101)
// bytes -- a ~39-byte inflation concentrated entirely in the erase/dealloc
// loop, not in the guard prologue (which matches retail exactly through
// +0x3d) or the final notEmpty/flag-store tail (close in size, ~30 vs 24
// bytes, a separate smaller difference). Since the IDENTICAL __forceinline
// clear() call compiles byte-exact inside AptPalantirStore::clear() but not
// here, the divergence is specific to how MSVC 7.1 schedules/expands the
// recursive _M_erase call site when the SURROUNDING function differs (a
// guard check before, a notEmpty recomputation after) -- register pressure
// or block layout from the surrounding code changes the forceinline
// expansion shape at this one call site. Not attempted: deliberately
// restructuring the surrounding guard/notEmpty code (e.g. matching clear()'s
// own local-variable footprint more closely) to see if it changes which
// expansion MSVC chooses; possible next lever but unexplored.
//
// Everything else -- guard chain shape (byte-exact through +0x2d, three
// distinct guard-fail conditions sharing one tail-call-to-clear() target
// matching retail's single 0xa2 jump target), the tail-call to clear()
// itself, and the overall method structure -- is verified correct against
// retail bytes.

void clearValue(int value);

namespace _STL
{

template <class Type> class allocator {};
template <class Type> struct _Identity {};
template <class Type> struct less {};

void nodeDeallocate(void *block, unsigned int bytes);

struct _Rb_tree_node_base
{
	int m_color;
	_Rb_tree_node_base *m_parent;
	_Rb_tree_node_base *m_left;
	_Rb_tree_node_base *m_right;
};

template <class Value>
struct _Rb_tree_node : public _Rb_tree_node_base
{
	Value m_value_field;
};

template <class Dummy>
struct _Rb_global
{
	static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base *node);
};

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
class _Rb_tree
{
public:
	typedef _Rb_tree_node<Value> Node;

	__forceinline void clear()
	{
		Node *node = (Node *)(void *)m_header->m_left;
		while (node != m_header)
		{
			clearValue(node->m_value_field.m_pod);
			node = (Node *)_Rb_global<bool>::_M_increment(node);
		}

		if (m_node_count != 0)
		{
			_M_erase((Node *)(void *)m_header->m_parent);
			m_header->m_left = m_header;
			m_header->m_parent = 0;
			m_header->m_right = m_header;
			m_node_count = 0;
		}
	}

	unsigned int size() const { return m_node_count; }

private:
	__forceinline void _M_erase(Node *node);

	_Rb_tree_node_base *m_header;
	unsigned int m_node_count;
	Compare m_key_compare;
};

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
__forceinline void _Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::_M_erase(Node *node)
{
	while (node != 0)
	{
		_M_erase((Node *)(void *)node->m_right);
		Node *left = (Node *)(void *)node->m_left;
		nodeDeallocate(node, sizeof(Node));
		node = left;
	}
}

}

struct Gen_t_00234730_m4pod
{
	int m_pod;
};

typedef _STL::_Rb_tree<
	Gen_t_00234730_m4pod,
	Gen_t_00234730_m4pod,
	_STL::_Identity<Gen_t_00234730_m4pod>,
	_STL::less<Gen_t_00234730_m4pod>,
	_STL::allocator<Gen_t_00234730_m4pod> > AptPalantirStoreTree;

// Real global (reverse/symbols.csv), confirmed by
// GameLogic::_bfme_isInLivingWorldCampaign (0x00382B50) reading the same
// +0x2C byte off the same global.
class CampaignObject
{
public:
	unsigned char m_pad[0x2c];
	bool m_flag2c;
	bool m_flag2d;
};
extern CampaignObject *TheLivingWorldLogic;

class AptPalantirStore
{
public:
	void clear();
	void rva00591b60();

private:
	unsigned int m_value00;
	bool m_flag04;
	unsigned char m_padding05[3];
	int m_value08;
	int m_value0c;
	AptPalantirStoreTree m_firstTree;
	AptPalantirStoreTree m_secondTree;
};

void AptPalantirStore::rva00591b60()
{
	if (!m_flag04)
		return;

	CampaignObject *campaign = TheLivingWorldLogic;
	if (campaign == 0 || !campaign->m_flag2c || !campaign->m_flag2d)
	{
		clear();
		return;
	}

	m_secondTree.clear();

	bool notEmpty = (m_value08 != 0) || (m_firstTree.size() != 0);
	m_flag04 = notEmpty;
	if (!notEmpty)
		m_value00 = 0;
}
