// ?update006B43E0@Rva006B43E0Owner@@QAEXABUGen_t_006af670_k4@@H@Z
// partial score=0.86 date=2026-09-03
// cl: /O2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB
// stlport
// Mutex-guarded keyed-tree update in the 0x006B3C50 owner family.

namespace _STL
{
	template <class Type> class allocator {};
	template <class First, class Second> struct pair {};
	template <class Pair> struct _Select1st {};
	template <class Type> struct less {};

	struct _Rb_tree_node_base
	{
		int _M_color;
		_Rb_tree_node_base *_M_parent;
		_Rb_tree_node_base *_M_left;
		_Rb_tree_node_base *_M_right;
	};

	template <class Value>
	struct _Rb_tree_node : public _Rb_tree_node_base
	{
		Value _M_value_field;
	};

	template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	class _Rb_tree
	{
	public:
		void insert(const Key &);

	private:
		_Rb_tree_node_base *_M_header;
		unsigned int _M_node_count;
		Compare _M_key_compare;
	};
}

struct Gen_t_006af670_k4
{
	int a[1];
};

struct Gen_t_006af670_p12cd
{
	int a[3];
};

typedef _STL::pair<const Gen_t_006af670_k4, Gen_t_006af670_p12cd>
	Rva006B43E0Pair;
typedef _STL::_Rb_tree<
	Gen_t_006af670_k4,
	Rva006B43E0Pair,
	_STL::_Select1st<Rva006B43E0Pair>,
	_STL::less<Gen_t_006af670_k4>,
	_STL::allocator<Rva006B43E0Pair> > Rva006B43E0Tree;


extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
	void *handle, unsigned long milliseconds);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *handle);

class Rva006B43E0MutexGuard
{
public:
	Rva006B43E0MutexGuard(void *handle)
	{
		m_owned = 0;
		m_handle = handle;
		if (WaitForSingleObject(handle, 0xFFFFFFFF) != 0x102)
			m_owned = 1;
	}

	~Rva006B43E0MutexGuard()
	{
		if (m_owned)
			ReleaseMutex(m_handle);
	}

private:
	void *m_handle;
	char m_owned;
};

struct Rva006B43E0Entry
{
	Rva006B43E0Tree m_tree;
	char m_pad0c[0x1C4 - 0x0C];
};

class Rva006B43E0Owner
{
public:
	void update006B43E0(const Gen_t_006af670_k4 &value, int index);
	void finalize(const Gen_t_006af670_k4 &first, float second, int third);

private:
	char m_pad270[0x270];
	Rva006B43E0Entry m_entries[3];
	char m_pad7b0[0x95c - (0x270 + 3 * 0x1c4)];
	void *m_mutex;
};

void Rva006B43E0Owner::update006B43E0(
	const Gen_t_006af670_k4 &value, int index)
{
	Rva006B43E0Owner *self = this;
	void *handle = self->m_mutex;
	Rva006B43E0MutexGuard guard(handle);
	Rva006B43E0Entry *entry = &self->m_entries[index];
	entry->m_tree.insert(value);

	self->finalize(value, -1.0f, index);
}
