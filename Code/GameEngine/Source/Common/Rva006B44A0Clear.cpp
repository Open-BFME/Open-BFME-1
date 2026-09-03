// cl: /O2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD
// stlport
// Mutex-guarded tree clear and owner update in the 0x006B3C50 owner family.

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
	void clear()
	{
		if (_M_node_count != 0)
		{
			_M_erase((_Node *)(void *)_M_root());
			_M_leftmost() = _M_header;
			_M_root() = 0;
			_M_rightmost() = _M_header;
			_M_node_count = 0;
		}
	}

private:
	typedef _Rb_tree_node<Value> _Node;
	_Rb_tree_node_base *&_M_root() const { return _M_header->_M_parent; }
	_Rb_tree_node_base *&_M_leftmost() const { return _M_header->_M_left; }
	_Rb_tree_node_base *&_M_rightmost() const { return _M_header->_M_right; }
	void _M_erase(_Node *x);
	_Rb_tree_node_base *_M_header;
	unsigned int _M_node_count;
	Compare _M_key_compare;
};

}

struct _SBServer;
typedef _STL::pair<const int, _SBServer *> Rva006B44A0ServerPair;
typedef _STL::_Rb_tree<int,
	Rva006B44A0ServerPair,
	_STL::_Select1st<Rva006B44A0ServerPair>,
	_STL::less<int>,
	_STL::allocator<Rva006B44A0ServerPair> > Rva006B44A0ServerTree;

extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
	void *handle, unsigned long milliseconds);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *handle);
extern void j_0004412a();
extern void j_00023d21();

struct Rva006B44A0Entry
{
	Rva006B44A0ServerTree m_tree;
	char m_pad[0x1c4 - 12];
};

class Rva006B44A0MutexGuard
{
public:
	Rva006B44A0MutexGuard(void *handle)
	{
		m_owned = 0;
		m_handle = handle;
		if (WaitForSingleObject(handle, 0xFFFFFFFF) != 0x102)
			m_owned = 1;
	}

	~Rva006B44A0MutexGuard()
	{
		if (m_owned)
			ReleaseMutex(m_handle);
	}

private:
	void *m_handle;
	char m_owned;
};

class Rva006B44A0Owner
{
public:
	void clear006B44A0(int index);
	void finalize(const void *key, float scale, int index);

private:
	char m_pad270[0x270];
	Rva006B44A0Entry m_entries[3];
	char m_pad7b0[0x95c - (0x270 + 3 * 0x1c4)];
	void *m_mutex;
};

void Rva006B44A0Owner::clear006B44A0(int index)
{
	Rva006B44A0MutexGuard guard(m_mutex);
	m_entries[index].m_tree.clear();
	{
		typedef void (Rva006B44A0Owner::*Finalize)(const void *, float, int);
		union
		{
			void (__cdecl *freeFinalize)();
			Finalize memberFinalize;
		} finalize;
		finalize.freeFinalize = ::j_00023d21;
		(this->*finalize.memberFinalize)(reinterpret_cast<const void *>(0x01336E50), -1.0f, index);
	}
}
