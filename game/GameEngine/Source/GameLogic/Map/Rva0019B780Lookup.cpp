// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stringinline /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#include "StringInline.h"

class BfmeWordEL
{
public:
 BfmeWordEL(const BfmeWordEL &other) { reinterpret_cast<AsciiString *>(this)->AsciiString::AsciiString(*reinterpret_cast<const AsciiString *>(&other)); }
 ~BfmeWordEL() { reinterpret_cast<AsciiString *>(this)->~AsciiString(); }
private:
 void *m_data;
};
struct BfmePairEL { BfmeWordEL first, second; };
struct Rva00198280Value;
struct Rva00198280KeyOfValue;
class Rva0019C520Member;
namespace _STL {
 template<class A, class B> struct pair;
 template<class T> struct less;
 template<class T> class allocator;
 template<class T> struct _Rb_tree_node;
 template<class K, class V, class E, class C, class A> class _Rb_tree {
  template<class Q> _Rb_tree_node<V> *_M_find(const Q &) const throw();
  friend class ::Rva0019C520Member;
 };
}

struct Rva0019B780Node
{
	unsigned char m_data[0x1c];
};

class Rva0019B780Tree
{
private:
	unsigned char m_tree[12];
};

extern BfmePairEL __cdecl Rva00194810(const BfmeWordEL &name);

struct Rva0019B780Entry
{
	unsigned char m_data[16];
};

class Rva0019C520Member
{
public:
	int lookup( AsciiString *name, int extra );

private:
	Rva0019B780Tree m_tree;
	Rva0019B780Entry *m_entries;
};

int Rva0019C520Member::lookup( AsciiString *name, int extra )
{
	AsciiString *input;
	input = name;
	Rva0019B780Node *found;
	{
		found = reinterpret_cast<Rva0019B780Node *>(reinterpret_cast<const _STL::_Rb_tree<_STL::pair<AsciiString, AsciiString>, Rva00198280Value, Rva00198280KeyOfValue, _STL::less<_STL::pair<AsciiString, AsciiString> >, _STL::allocator<Rva00198280Value> > *>(&m_tree)->_M_find<_STL::pair<AsciiString, AsciiString> >(*reinterpret_cast<const _STL::pair<AsciiString, AsciiString> *>(&Rva00194810(*reinterpret_cast<const BfmeWordEL *>(input)))));
	}
	if (found == *(Rva0019B780Node **)&m_tree)
		return 0;
	int index = *(int *)((char *)found + 0x18);
	Rva0019B780Entry *entry = m_entries + index;
	if (extra)
		*(int *)extra = index;
	return (int)((char *)entry + 0x0c);
}
