// cl: /DNDEBUG /MD /EHsc

class AsciiString;
class Rva000F72B0AsciiHashOwner;
struct Rva000F2010Value;
struct Rva000F2010ExtractKey;
namespace rts { template<class T> struct hash; }
namespace _STL {
 template<class T> struct equal_to;
 template<class T> class allocator;
 template<class T> struct _Hashtable_node;
 template<class V,class K,class H,class E,class C,class A> class hashtable {
  template<class Q> _Hashtable_node<V> *_M_find(const Q &) const;
  friend class ::Rva000F72B0AsciiHashOwner;
 };
}

class Rva000F72B0AsciiHash
{
public:
};

class Rva000F72B0AsciiHashOwner
{
public:
	unsigned char contains(const AsciiString &key);

private:
	unsigned char m_unmodelled_000[0x1c];
	Rva000F72B0AsciiHash m_values;
};

unsigned char Rva000F72B0AsciiHashOwner::contains(const AsciiString &key)
{
	return reinterpret_cast<const _STL::hashtable<Rva000F2010Value, AsciiString, rts::hash<AsciiString>, Rva000F2010ExtractKey, _STL::equal_to<AsciiString>, _STL::allocator<Rva000F2010Value> > *>(&m_values)->_M_find<AsciiString>(key) != 0;
}
