// ?_M_lower_bound@?$_Rb_tree@UGen_t_00632450_m12cd@@U1@U?$_Identity@UGen_t_00632450_m12cd@@@_STL@@U?$less@UGen_t_00632450_m12cd@@@3@V?$allocator@UGen_t_00632450_m12cd@@@3@@_STL@@ABEPAU?$_Rb_tree_node@UGen_t_00632450_m12cd@@@2@ABUGen_t_00632450_m12cd@@@Z
// partial score=0.4 date=2026-09-05
// cl: /DNDEBUG /MD /EHsc
// stlport

// Open-BFME: STLport _Rb_tree<Gen_t_00632450_m12cd,...>::_M_lower_bound and
// _Rb_tree<Gen_t_00632e80_m12cd,...>::_M_lower_bound, retail 0x00631C70
// (144 bytes). Both instantiations fold to one identical body: the value
// type is a 12-byte key whose only live field is a StringBase<char> at
// offset 0 (an AsciiString-shaped ref-counted string); the trailing 8 bytes
// are never touched by the comparator and are left uninitialised on copy.
//
// The compare functor lives embedded in the tree object at this+8 and is
// called as a member operator() taking BOTH operands BY VALUE -- MSVC's
// non-trivial-by-value-parameter ABI makes the CALLEE (retail 0x00631350,
// reached through the 0x0000B4B0 five-byte thunk already matched in
// Code/gen_small/thunks_005.cpp) responsible for destroying the two copies,
// which is why this body never emits any releaseBuffer/dtor calls of its
// own after the compare call. The copy ctor called to build each temporary
// (retail 0x00887B60) is ICF-aliased with GameSpyGroupRoom's copy ctor and
// with StringBase<char>::StringBase(const StringBase&); it moves only the
// string field, exactly matching the single-call, no-extra-mov pattern in
// the retail dump.

template <typename T>
class StringBase
{
public:
	StringBase(const StringBase<T> &src);	// retail 0x00887B60
private:
	void *m_data;
};

struct Gen_t_00632450_m12cd
{
	Gen_t_00632450_m12cd(const Gen_t_00632450_m12cd &o) : m_string(o.m_string) {}
	~Gen_t_00632450_m12cd() {}

	StringBase<char> m_string;	// +0x00
	int m_field4;			// +0x04 (unused by the comparator)
	int m_field8;			// +0x08 (unused by the comparator)
};

struct Gen_t_00632450_m12cd_Node
{
	int color;
	Gen_t_00632450_m12cd_Node *parent;
	Gen_t_00632450_m12cd_Node *left;
	Gen_t_00632450_m12cd_Node *right;
	Gen_t_00632450_m12cd value;
};

// Dummy class matching the compare functor's shape purely so we can form a
// pointer-to-member-function cast to the pinned retail body -- same idiom as
// Code/GameEngine/Source/Common/Rva006A8210IndexedEntryDispatch.cpp.
class Gen_t_00632450_m12cd_CompareThunk
{
public:
	bool call(Gen_t_00632450_m12cd a, Gen_t_00632450_m12cd b);
};

typedef bool (Gen_t_00632450_m12cd_CompareThunk::*Gen_t_00632450_m12cd_CompareFn)(
	Gen_t_00632450_m12cd, Gen_t_00632450_m12cd);

extern void b_00631350();	// pinned retail body reached via j_0000b4b0

class Gen_t_00632450_m12cd_Tree
{
public:
	Gen_t_00632450_m12cd_Node *_M_lower_bound(const Gen_t_00632450_m12cd &key) const;

private:
	Gen_t_00632450_m12cd_Node *m_header;
	void *m_unused4;
};

Gen_t_00632450_m12cd_Node *
Gen_t_00632450_m12cd_Tree::_M_lower_bound(const Gen_t_00632450_m12cd &key) const
{
	Gen_t_00632450_m12cd_Node *y = m_header;
	Gen_t_00632450_m12cd_Node *x = y->parent;

	union
	{
		void *asVoid;
		Gen_t_00632450_m12cd_CompareFn asMember;
	} compareCast;
	compareCast.asVoid = (void *)&b_00631350;

	while (x)
	{
		if (!((((Gen_t_00632450_m12cd_CompareThunk *)((char *)this + 8))->*compareCast.asMember)(x->value, key)))
		{
			y = x;
			x = x->left;
		}
		else
		{
			x = x->right;
		}
	}
	return y;
}
