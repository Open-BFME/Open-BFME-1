// Retail 0x00927730 is the bucket-number half of the Gen_p12pod hash
// table: it hashes the key ((a[1] << 16) + a[0]) and mods by the live
// bucket span ((m_last - m_first) >> 2, sar form). The >>= spelling on a
// signed span is what emits retail's sar; the >> spelling on an unsigned
// span emits shr and drifts by one byte. Neighbours: the Gen_p12pod
// _M_lower_bound at 0x00927680, bfmeMakeNode at 0x00927760 and _M_find at
// 0x00927790. IDENTITY IS NOT RECOVERED: the owner keeps its address
// token.
// cl: /DNDEBUG /MD /G6 /EHsc
// stlport
#include <hash_map>
struct Rva00927730Key
{
	int a[3];
};
namespace _STL
{
template<> struct hash<Rva00927730Key>
{
	unsigned int operator()(const Rva00927730Key &k) const
	{
		return (unsigned int)k.a[1] * 0x10000 + (unsigned int)k.a[0];
	}
};
}
class Rva00927730Box
{
public:
	unsigned int bucket(const Rva00927730Key &key) const;
	unsigned int m_pad0;
	int m_first;
	int m_last;
};
unsigned int Rva00927730Box::bucket(const Rva00927730Key &key) const
{
	unsigned int h = _STL::hash<Rva00927730Key>()(key);
	int d = m_last - m_first;
	d >>= 2;
	return h % (unsigned int)d;
}
