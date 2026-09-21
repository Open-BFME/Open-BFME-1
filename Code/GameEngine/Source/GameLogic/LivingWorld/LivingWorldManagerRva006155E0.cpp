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

class BfmeItemEQV
{
public:
	BfmeItemEQV(void *key);

	unsigned char m_bfmeBodyEQV[0x34];
};

class BfmeMapEQV
{
public:
	BfmeItemEQV *bfmeFindEQV(void *key);
	BfmeItemEQV **bfmeAtEQV(void *key);
};

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
	BfmeItemEQV *item = map->bfmeFindEQV(key);

	if (item != 0)
		return *map->bfmeAtEQV(key);

	item = new BfmeItemEQV(key);

	*map->bfmeAtEQV(key) = item;

	return item;
}
