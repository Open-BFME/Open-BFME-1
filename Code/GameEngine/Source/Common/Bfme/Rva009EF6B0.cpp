// ??0Rva009EF6B0@@QAE@ABV?$_Rb_tree@UGen_t_009ee8e0_k4@@U1@U?$_Identity@UGen_t_009ee8e0_k4@@@_STL@@U?$less@UGen_t_009ee8e0_k4@@@3@V?$allocator@UGen_t_009ee8e0_k4@@@3@@_STL@@@Z
// cl: /DNDEBUG /MD /EHsc

// Retail RVA 0x009EF6B0, 30 bytes, directly after the jump table of the
// matched 0x009EF280 registry member. Nothing in the image calls or stores
// this address, so its identity is address-derived. The body is the
// out-of-line form of the 0x14-byte set wrapper the matched 0x009EF6D0 and
// 0x009EF750 copies construct inline: copy the tree through the
// 0x009EE8E0 _Rb_tree copy constructor, zero the int at +0x0C, set the
// bool at +0x10 and return this (thiscall, ret 4).

struct Gen_t_009ee8e0_k4
{
	int a[1];
	Gen_t_009ee8e0_k4();
	Gen_t_009ee8e0_k4(const Gen_t_009ee8e0_k4 &other);
	~Gen_t_009ee8e0_k4();
	Gen_t_009ee8e0_k4 &operator=(const Gen_t_009ee8e0_k4 &other);
};

namespace _STL
{
	template <class T> struct _Identity;
	template <class T> struct less;
	template <class T> class allocator;

	template <class Key, class Value, class KeyOfValue, class Compare,
		class Allocator> class _Rb_tree
	{
	public:
		_Rb_tree(const _Rb_tree &other);

	private:
		void *m_header;
		unsigned int m_node_count;
		unsigned int m_compare;
	};
}

typedef _STL::_Rb_tree<
	Gen_t_009ee8e0_k4,
	Gen_t_009ee8e0_k4,
	_STL::_Identity<Gen_t_009ee8e0_k4>,
	_STL::less<Gen_t_009ee8e0_k4>,
	_STL::allocator<Gen_t_009ee8e0_k4> > Rva009EF6B0Tree;

struct Rva009EF6B0
{
	Rva009EF6B0(const Rva009EF6B0Tree &source);

	Rva009EF6B0Tree m_tree;
	int m_value;
	bool m_active;
};

Rva009EF6B0::Rva009EF6B0(const Rva009EF6B0Tree &source) : m_tree(source)
{
	m_value = 0;
	m_active = true;
}
