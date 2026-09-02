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
	Rva0054EF10Node *y = header;
	Rva0054EF10Node *x = y->parent;
	if ( !x )
		return y;

	BfmeWideHeader *keyData = key.m_data;
	const unsigned short *empty =
		reinterpret_cast<const unsigned short *>( g_bfmeEmptyUnicode );
	while ( x )
	{
		int thatLen = keyData ? keyData->length : 0;
		const unsigned short *thatData = keyData ? &keyData->data[ 0 ] : empty;
		BfmeWideHeader *nodeData = x->key.m_data;
		int thisLen = nodeData ? nodeData->length : 0;
		const unsigned short *thisData = x->key.m_data ? &x->key.m_data->data[ 0 ] : empty;
		int n = thisLen < thatLen ? thisLen : thatLen;
		int c = 0;
		while ( n > 0 )
		{
			if ( *thisData != *thatData )
			{
				c = *thisData;
				c -= *thatData;
				break;
			}
			++thisData;
			++thatData;
			--n;
		}
		if ( c == 0 )
			c = thisLen - thatLen;
		if ( c >= 0 )
		{
			y = x;
			x = x->left;
		}
		else
			x = x->right;
	}
	return y;
}
