class AsciiString;
struct Rva001366A0Value;
struct Rva001366A0ExtractKey;
enum Rva001360E0Mapped { Rva001360E0MappedZero = 0 };
class BfmeOwnerYQ;
namespace rts { template <class Key> struct hash; }
namespace _STL
{
template <class First, class Second> struct pair;
template <class Key> struct equal_to;
template <class Value> class allocator;
template <class Value> struct _Hashtable_node;
template <class Value, class Key, class Hash, class Extract, class Equal, class Alloc>
class hashtable
{
    friend class ::BfmeOwnerYQ;
    template <class Lookup>
    _Hashtable_node<Value> *_M_find(const Lookup &) const;
};
template <class Key, class Mapped, class Hash, class Equal, class Alloc>
class hash_map
{
public:
    Mapped &operator[](const Key &);
};
}

class BfmeItemYQ;

struct BfmeKeyYQ
{
	unsigned char m_bfmeBytesYQ[4];
};

class BfmeItemYQ
{
public:
	unsigned char m_bfmeHeadYQ[0x20];
	BfmeKeyYQ m_bfmeKeyYQ;
	unsigned char m_bfmeMidYQ[0x368];
	BfmeItemYQ *m_bfmeNextYQ;
};

class BfmeMapYQ
{
public:
};

class BfmeOwnerYQ
{
public:
	void bfmeAddYQ(BfmeItemYQ *item);

	unsigned char m_bfmeHeadYQ[8];
	BfmeItemYQ *m_bfmeListYQ;
	unsigned char m_bfmePadYQ[4];
	BfmeMapYQ m_bfmeMapYQ;
};

void BfmeOwnerYQ::bfmeAddYQ(BfmeItemYQ *item)
{
	reinterpret_cast<const _STL::hashtable<Rva001366A0Value,
        AsciiString, rts::hash<AsciiString>, Rva001366A0ExtractKey,
        _STL::equal_to<AsciiString>, _STL::allocator<Rva001366A0Value> > *>(&m_bfmeMapYQ)
        ->_M_find<AsciiString>(*reinterpret_cast<const AsciiString *>(&item->m_bfmeKeyYQ));

	item->m_bfmeNextYQ = m_bfmeListYQ;
	m_bfmeListYQ = item;

	reinterpret_cast<BfmeItemYQ *&>(
        (*reinterpret_cast<_STL::hash_map<AsciiString, Rva001360E0Mapped,
            rts::hash<AsciiString>, _STL::equal_to<AsciiString>,
            _STL::allocator<_STL::pair<const AsciiString, Rva001360E0Mapped> > > *>(&m_bfmeMapYQ))
            [*reinterpret_cast<const AsciiString *>(&item->m_bfmeKeyYQ)]) = item;
}
