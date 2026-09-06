// ?_M_lower_bound@Rva00605550Tree@@QBEPAURva00605550Node@@ABUBfmeNamedFloatKey@@@Z
// partial score=0.2 date=2026-09-05
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// Open-BFME: the name+float _M_lower_bound at 0x00605550 (166 B), one of two
// _Rb_tree<Gen_t_00605800_m12cd> / _Rb_tree<Gen_t_006058a0_m12cd> instantiations
// per fam_014.cpp (opaque `int a[3]` PODs, operator< declared only, never
// defined -- the STLport comparator wall). Same family as the wide-string
// _M_lower_bound at 0x0054EE40 (RvaTreeLowerBoundWideWalk.cpp): the template
// member will not accept a looping/functor compare, so the walk here is
// hand-written with the compare expanded at the site retail inlines it, and
// the type is spelled out address-derived (identity policy) rather than
// re-declaring the gen_small opaque blob.
//
// The body's own memory accesses show the 12-byte key is a name pointer
// (AsciiString-shaped: refcount/alloc/len header, chars at +8) at key+0x0
// followed by a float at key+0x8. The compare is AsciiString::compareNoCase
// (memicmp over the shorter length, then the length difference) exactly as
// landed at 0x004AD740 (ControlBarScheme_find.cpp), tie-broken by the float
// when the names compare fully equal.

extern "C" __declspec(dllimport) int __cdecl _memicmp(const void *buf1, const void *buf2, unsigned int count);

extern const char g_bfmeEmptyAscii[];

struct BfmeAsciiHeader
{
	int ref_count;
	unsigned short length;			// +0x04
	unsigned short capacity;
	char data[ 1 ];					// +0x08
};

struct BfmeAsciiString
{
	BfmeAsciiHeader *m_data;
};

struct BfmeNamedFloatKey
{
	BfmeAsciiString m_name;			// this+0x00
	int m_pad;						// this+0x04
	float m_value;					// this+0x08
};

struct Rva00605550Node
{
	int color;
	Rva00605550Node *parent;
	Rva00605550Node *left;
	Rva00605550Node *right;
	BfmeNamedFloatKey key;				// this+0x10
};

struct Rva00605550Tree
{
	Rva00605550Node *header;
	Rva00605550Node *_M_lower_bound( const BfmeNamedFloatKey &key ) const;
};

Rva00605550Node *Rva00605550Tree::_M_lower_bound( const BfmeNamedFloatKey &key ) const
{
	Rva00605550Node *y = header;
	Rva00605550Node *x = y->parent;
	if ( !x )
		return y;

	while ( x )
	{
		BfmeAsciiHeader *keyData = key.m_name.m_data;
		int keyLen = keyData ? keyData->length : 0;
		const char *keyChars = keyData ? &keyData->data[ 0 ] : g_bfmeEmptyAscii;

		BfmeAsciiHeader *nodeData = x->key.m_name.m_data;
		int nodeLen = nodeData ? nodeData->length : 0;
		const char *nodeChars = nodeData ? &nodeData->data[ 0 ] : g_bfmeEmptyAscii;

		int n = nodeLen < keyLen ? nodeLen : keyLen;
		int c = _memicmp( nodeChars, keyChars, n );
		if ( c == 0 )
			c = nodeLen - keyLen;

		if ( c < 0 )
		{
			x = x->right;
		}
		else if ( c > 0 )
		{
			y = x;
			x = x->left;
		}
		else if ( x->key.m_value < key.m_value )
		{
			x = x->right;
		}
		else
		{
			y = x;
			x = x->left;
		}
	}
	return y;
}
