// ?insertNode@Rva009A3290Owner@@QAEPAXPBX@Z
#include <string.h>
#pragma intrinsic(memcpy)

struct Rva009A3290Node
{
	int m_data[11];
	void **m_back;
	Rva009A3290Node *m_next;
};

struct Rva009A3290Owner
{
	Rva009A3290Node *m_buckets[0x2B7B];
	Rva009A3290Node *m_freeHead;

	void *insertNode( const void *src );
};

void *Rva009A3290Owner::insertNode( const void *src )
{
	Rva009A3290Node *node;
	if( m_freeHead )
	{
		node = m_freeHead;
		m_freeHead = node->m_next;
	}
	else
	{
		node = (Rva009A3290Node *)operator new( 0x34 );
	}
	memcpy( node, src, 0x2C );
	unsigned int h = ( *(const unsigned int *)( (const char *)src + 8 ) << 16 )
		+ *(const unsigned int *)( (const char *)src + 0xC );
	unsigned int index = h % 0x2B7B;
	Rva009A3290Node **bucket = &m_buckets[ index ];
	node->m_back = (void **)bucket;
	Rva009A3290Node *old = *bucket;
	node->m_next = old;
	if( old )
		old->m_back = (void **)&node->m_next;
	*bucket = node;
	return node;
}
