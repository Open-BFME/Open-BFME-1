// Open-BFME5: retail RVA 0x006155E0, 150 bytes.
//
// Receiver proven: the sole caller 0x0061C410 (an INI field parser: it calls
// INI::getNextToken, builds an AsciiString from the token, then) loads
// g_bfmeGameCW from 0x012F706C into ECX and calls the ILT thunk 0x0001BB67,
// which jumps to 0x006155E0.  That is the same singleton and the same
// this+0x194 STLport AsciiString hashtable as the landed sibling
// BfmeLivingWorldManager::rva006157c0 (0x006157C0), so this body is a method
// on that class.
//
// Behaviour: get-or-create.  The key is the AsciiString the caller just built
// (the find helper at 0x00613AE0 is _M_find<AsciiString>); the mapped object is
// a 0x34-byte LivingWorldSound, since the constructor reached through the ILT
// thunk 0x0002F289 is ??0LivingWorldSound@@QAE@ABVAsciiString@@@Z at 0x0061BF00.
// The map helpers are reached only through pinned thunks and their public
// spelling is not recovered, so key, map and item stay address/pin-derived.
//
// Shape note for the next reader: the three callee-saved values rotate unless
// the *find result and the new item share one variable*.  Ten earlier passes
// kept them separate (`if (find(key) != 0) ... BfmeItemEQV *item = new ...`),
// which hands EBX to the map and pushes the key out to EDI, and leaves the
// null temp materialised late (`test eax,eax` instead of retail's
// `xor edi,edi` / `cmp eax,edi`).  Declaring `item` as the find result extends
// its live range across the guard and reproduces retail exactly.

class BfmeItemEQV;
class AsciiString;

// ILT 0x0002F289 reaches the verified LivingWorldSound constructor.
class LivingWorldSound
{
public:
	LivingWorldSound(const AsciiString &name);

private:
	unsigned char m_layout0061BF00[0x34];
};

// Exact declarations of the matched native subscript and private const
// lookup; do not import their template bodies into this caller.
class BfmeLivingWorldManager;
struct Rva00613AE0Value;
struct Rva00613AE0ExtractKey;
namespace rts { template <class T> struct hash; }
namespace _STL
{
template <class T> class allocator;
template <class T> struct equal_to;
template <class A, class B> struct pair;
template <class V> struct _Hashtable_node;
template <class V, class K, class Hash, class Extract, class Equal, class Alloc>
class hashtable
{
	template <class Key> _Hashtable_node<V> *_M_find(const Key &) const;
	friend class ::BfmeLivingWorldManager;
};
template <class K, class V, class Hash, class Equal, class Alloc>
class hash_map
{
public:
	V &operator[](const K &);
};
}

class BfmeMapEQV {};

class BfmeLivingWorldManager
{
public:
	BfmeItemEQV *rva006155e0(void *key);

private:
	unsigned char m_prefix[0x194];
	BfmeMapEQV m_objects;
};

BfmeItemEQV *BfmeLivingWorldManager::rva006155e0(void *key)
{
	BfmeMapEQV *map = &m_objects;
	BfmeItemEQV *item = reinterpret_cast<BfmeItemEQV *>(
		reinterpret_cast<const _STL::hashtable<Rva00613AE0Value, AsciiString, rts::hash<AsciiString>, Rva00613AE0ExtractKey, _STL::equal_to<AsciiString>, _STL::allocator<Rva00613AE0Value> > *>(map)->_M_find<AsciiString>(
			*static_cast<const AsciiString *>(key)));

	if (item != 0)
		return reinterpret_cast<BfmeItemEQV *>((*reinterpret_cast<_STL::hash_map<AsciiString, LivingWorldSound *, rts::hash<AsciiString>, _STL::equal_to<AsciiString>, _STL::allocator<_STL::pair<const AsciiString, LivingWorldSound *> > > *>(map))[
			*static_cast<const AsciiString *>(key)]);

	item = reinterpret_cast<BfmeItemEQV *>(
		new LivingWorldSound(*static_cast<const AsciiString *>(key)));

	(*reinterpret_cast<_STL::hash_map<AsciiString, LivingWorldSound *, rts::hash<AsciiString>, _STL::equal_to<AsciiString>, _STL::allocator<_STL::pair<const AsciiString, LivingWorldSound *> > > *>(map))[*static_cast<const AsciiString *>(key)] =
		reinterpret_cast<LivingWorldSound *>(item);

	return item;
}
