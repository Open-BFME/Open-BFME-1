// cl: /O2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Mutex-guarded tree clear and owner update in the 0x006B3C50 owner family.

// retail's inlined clear() reaches the tree's subtree erase out of line, at
// RVA 0x0004412A -- the matched 5-byte ILT thunk ?j_0004412a@@YAXXZ
// (functions.csv row ?j_0004412a@@YAXXZ, game/gen_small/thunks_032.cpp,
// gen-thunk, target 0x0005C5DF0). Calling it through the STLport member
// declaration instead left this object referencing
// ?_M_erase@?$_Rb_tree@HU?$pair@$$CBHPAU_SBServer@@... , which only a
// symbols.csv pin covers at that same address and no TU defines, so the object
// never linked. The call is written inside clear() in the same
// union-of-pointer-to-member shape this file already uses for finalize, so the
// defined thunk is named, no _M_erase body is defined here, and no ledger row
// is needed.
extern void j_0004412a();

// These receiver views belong only to this owner body.  Keeping them local
// prevents a manually modeled clear() from competing with STLport's tree.
namespace {
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

// Receiver view for the thunk forwarder: the erase body is reached with the
// tree itself in ECX, so the call is devirtualised through this empty facade
// rather than through a real (and undefined) _M_erase instantiation.
class EraseClass
{
};

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
class _Rb_tree
{
public:
	void clear()
	{
		if (_M_node_count != 0)
		{
			// Retail reaches the subtree erase out of line through the matched
			// 5-byte ILT thunk ?j_0004412a@@YAXXZ at RVA 0x0004412A, with the
			// tree in ECX and the subtree root pushed. Naming the STLport
			// member instead left the object referencing
			// ?_M_erase@?$_Rb_tree<HU?$pair@$$CBHPAU_SBServer@@...>, which only
			// a symbols.csv pin covers and no TU defines, so this TU could not
			// link. The call is written here, in the same union-of-PMF shape
			// this file already uses for finalize, so no _M_erase body is
			// defined here and nothing is left unresolved.
			typedef void (EraseClass::*Erase)(_Rb_tree_node_base *);
			union { void (*raw)(void); Erase member; } fn;
			fn.raw = j_0004412a;
			(reinterpret_cast<EraseClass *>(this)->*fn.member)(_M_root());

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

} // anonymous namespace

extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
	void *handle, unsigned long milliseconds);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *handle);
extern void j_00023d21();

// AsciiString::TheEmptyString is the real exported datum (VA 0x01336E50,
// ?TheEmptyString@AsciiString@@2V1@B); the file-scope `TheEmptyString` TU view
// spelled an address nothing defines.
#include "ascii_string.h"

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
		(this->*finalize.memberFinalize)(reinterpret_cast<const void *>(&AsciiString::TheEmptyString), -1.0f, index);
	}
}
