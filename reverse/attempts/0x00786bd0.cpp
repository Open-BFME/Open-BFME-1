// ?d_00786bd0@@YAXXZ
// partial score=0.77 date=2026-08-29
// ---------------------------------------------------------------------------
// 0x00786BD0 -- hash lookup over a bucket vector.
//
//     mov esi,[ecx+0xc] / mov edi,[ecx+0x10] / sub edi,esi / sar edi,2
//     div edi / mov eax,[ecx+0xc] / mov edx,[eax+edx*4]
//     <walk the chain> ... mov eax,[edx+8]
//
// `div` is unsigned and the bucket count is a pointer difference over four, so
// the buckets are a dword vector.  The chain walk exits through TWO tests of
// the same register -- one leaving the loop, one guarding the read -- which is
// a `while` followed by an `if`, not a single test.

class Open2HashNode
{
public:
	Open2HashNode *m_next;
	unsigned int m_key;
	void *m_value;
};

class Rva00786BD0
{
public:
	void *find( unsigned int key ) const;

	char m_pad[ 0xc ];
	Open2HashNode **m_bucketBegin;
	Open2HashNode **m_bucketEnd;
};

// @?find@Rva00786BD0@@QBEPAXI@Z 0x00786BD0
void *Rva00786BD0::find( unsigned int key ) const
{
	unsigned int buckets = (unsigned int)( m_bucketEnd - m_bucketBegin );
	Open2HashNode *node = m_bucketBegin[ key % buckets ];

	while( node != 0 && node->m_key != key )
		node = node->m_next;

	if( node != 0 )
		return node->m_value;
	return 0;
}

