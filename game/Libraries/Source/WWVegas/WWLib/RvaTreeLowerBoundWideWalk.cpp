// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// Open-BFME5: the wide-string _M_lower_bound at 0x0054EE40.  STLport's
// template member will not accept the compare loop (MSVC 7.1 will not
// inline a looping functor into the descent), so the walk is written
// with the comparison expanded at the one site retail inlines it.

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

struct Rva0054EF10Node
{
	int color;
	Rva0054EF10Node *parent;
	Rva0054EF10Node *left;
	Rva0054EF10Node *right;
	BfmeWideString key;
};

struct Rva0054EF10Tree
{
	Rva0054EF10Node *header;
	Rva0054EF10Node *_M_lower_bound( const BfmeWideString &key ) const;
};

Rva0054EF10Node *Rva0054EF10Tree::_M_lower_bound( const BfmeWideString &key ) const
{
	Rva0054EF10Node *lowerBound = header;
	Rva0054EF10Node *node = lowerBound->parent;
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
