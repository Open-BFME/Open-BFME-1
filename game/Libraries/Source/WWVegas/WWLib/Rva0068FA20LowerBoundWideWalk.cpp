// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// Open-BFME5: TWIN lane. 0x0068FA20 is a byte-twin (relocations masked, no
// REL32 calls in the body) of the wide-string _M_lower_bound at 0x0054EE40
// (game/Libraries/Source/WWVegas/WWLib/RvaTreeLowerBoundWideWalk.cpp) --
// same node layout (color/parent/left/right at +0/+4/+8/+0xc, key at +0x10)
// and the same expanded compare loop against g_bfmeEmptyUnicode (retail
// 0x0107388C, already pinned).
//
// targets/game/reverse/symbols.csv carries two _M_lower_bound pins at this address for
// Gen_t_0068ff40_m12cd / Gen_t_00690350_m12cd (game/gen_small/fam_015.cpp,
// 12-byte PODs whose operator< is declared but never defined). Neither
// explains these bytes: a call-based comparator on an undefined operator<
// cannot produce this self-contained wide-char walk, and the tree/node
// identity here is address-derived like the twin, so this body is landed
// under its own address-derived name rather than either stale pin.

extern const char g_bfmeEmptyUnicode[];

struct BfmeWideHeader
{
	int ref_count;
	unsigned short length;
	unsigned short capacity;
	unsigned short data[ 1 ];
};

struct BfmeWideString
{
	BfmeWideHeader *m_data;
};

struct Rva0068FA20Node
{
	int color;
	Rva0068FA20Node *parent;
	Rva0068FA20Node *left;
	Rva0068FA20Node *right;
	BfmeWideString key;
};

struct Rva0068FA20Tree
{
	Rva0068FA20Node *header;
	Rva0068FA20Node *_M_lower_bound( const BfmeWideString &key ) const;
};

Rva0068FA20Node *Rva0068FA20Tree::_M_lower_bound( const BfmeWideString &key ) const
{
	Rva0068FA20Node *lowerBound = header;
	Rva0068FA20Node *node = lowerBound->parent;
	if ( !node )
		return lowerBound;

	BfmeWideHeader *keyData = key.m_data;
	const unsigned short *empty =
		reinterpret_cast<const unsigned short *>( g_bfmeEmptyUnicode );
	while ( node )
	{
		int thatLen = keyData ? keyData->length : 0;
		const unsigned short *thatData = keyData ? &keyData->data[ 0 ] : empty;
		BfmeWideHeader *nodeData = node->key.m_data;
		int thisLen = nodeData ? nodeData->length : 0;
		const unsigned short *thisData = node->key.m_data ? &node->key.m_data->data[ 0 ] : empty;
		int remaining = thisLen < thatLen ? thisLen : thatLen;
		int comparison = 0;
		while ( remaining > 0 )
		{
			if ( *thisData != *thatData )
			{
				comparison = *thisData;
				comparison -= *thatData;
				break;
			}
			++thisData;
			++thatData;
			--remaining;
		}
		if ( comparison == 0 )
			comparison = thisLen - thatLen;
		if ( comparison >= 0 )
		{
			lowerBound = node;
			node = node->left;
		}
		else
			node = node->right;
	}
	return lowerBound;
}
