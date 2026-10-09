// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport

// Team::bfmeCall2440, retail 0x000F75B0 (86 bytes).
// Team's constructor initializes the 20-byte hash member at +0x1C through
// +0x2C.  This local view preserves that embedded storage and its ABI.
// The operation removes an existing key for mode zero and inserts byte one
// for an absent key in mode one.

#define _STLP_NO_EXCEPTIONS 1

#include "ascii_string.h"

class Team;
class Rva000F6B50Mapped;
struct Rva000F2010Value;
struct Rva000F2010ExtractKey;
namespace rts { template<class T> struct hash; template<class T> struct equal_to; }
namespace _STL {
 template<class T> class allocator;
 template<class A,class B> struct pair;
 template<class T> struct _Select1st;
 template<class T> struct _Const_traits;
 template<class T> struct equal_to;
 template<class V,class Tr,class K,class H,class E,class C,class A> struct _Ht_iterator;
 template<class T> struct _Hashtable_node;
 template<class V,class K,class H,class E,class C,class A> class hashtable {
  template<class Q> _Hashtable_node<V> *_M_find(const Q &) const;
  friend class ::Team;
 public: void erase(const _Ht_iterator<V, _Const_traits<V>, K, H, E, C, A> &);
 };
 template<class K,class V,class H,class C,class A> class hash_map { public: V &operator[](const K &); };
}

class BfmeTeamCall2440Iterator
{
public:
	void *m_cur;
	void *m_ht;
};

// The +0x1C Team member is an embedded 20-byte AsciiString hash object.  Its
// lookup returns a neutral node pointer; the actual mapped value is exposed
// only by operator[] below.
class Rva000F75B0HashMember
{
public:

private:
    unsigned char m_opaque[0x14];
};

class Team
{
public:
    void bfmeCall2440(const AsciiString &key, unsigned char mode);
};

// ?bfmeCall2440@Team@@QAEXABVAsciiString@@E@Z
void Team::bfmeCall2440(const AsciiString &key, unsigned char mode)
{
    Rva000F75B0HashMember *values =
        (Rva000F75B0HashMember *)((char *)this + 0x1c);
    void *found = reinterpret_cast<const _STL::hashtable<Rva000F2010Value, AsciiString, rts::hash<AsciiString>, Rva000F2010ExtractKey, _STL::equal_to<AsciiString>, _STL::allocator<Rva000F2010Value> > *>(values)->_M_find<AsciiString>(key);
    if (found != 0)
    {
        if (mode == 0)
        {
            BfmeTeamCall2440Iterator it;
            it.m_cur = found;
            it.m_ht = values;
            reinterpret_cast<_STL::hashtable<_STL::pair<const AsciiString, Rva000F6B50Mapped *>, AsciiString, rts::hash<AsciiString>, _STL::_Select1st<_STL::pair<const AsciiString, Rva000F6B50Mapped *> >, _STL::equal_to<AsciiString>, _STL::allocator<_STL::pair<const AsciiString, Rva000F6B50Mapped *> > > *>(values)->erase(*reinterpret_cast<const _STL::_Ht_iterator<_STL::pair<const AsciiString, Rva000F6B50Mapped *>, _STL::_Const_traits<_STL::pair<const AsciiString, Rva000F6B50Mapped *> >, AsciiString, rts::hash<AsciiString>, _STL::_Select1st<_STL::pair<const AsciiString, Rva000F6B50Mapped *> >, _STL::equal_to<AsciiString>, _STL::allocator<_STL::pair<const AsciiString, Rva000F6B50Mapped *> > > *>(&it));
        }
    }
    else if (mode == 1)
    {
        (*reinterpret_cast<_STL::hash_map<AsciiString, unsigned char, rts::hash<AsciiString>, rts::equal_to<AsciiString>, _STL::allocator<_STL::pair<const AsciiString, unsigned char> > > *>(values))[key] = 1;
    }
}
