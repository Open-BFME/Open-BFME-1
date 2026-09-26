// cl: /O2 /MD /EHs-c- /Oy-

extern "C" __declspec(dllimport) const char* __cdecl strrchr( const char*, int );
extern void* DebugAllocMemory( unsigned int );

struct DictNode
{
	DictNode* m_next;     // 0x00
	int m_key;            // 0x04
	int m_flags;          // 0x08
	const char* m_str;    // 0x0C
	int m_value;          // 0x10
	int pad14;            // 0x14
	int pad18;            // 0x18
}; // 0x1C

class Dictionary
{
public:
	virtual ~Dictionary(); // 0
	// padding out to 0xA4 for allocStr...
	virtual void v04();
	virtual void v08();
	virtual void v0c();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual void v1c();
	virtual void v20();
	virtual void v24();
	virtual void v28();
	virtual void v2c();
	virtual void v30();
	virtual void v34();
	virtual void v38();
	virtual void v3c();
	virtual void v40();
	virtual void v44();
	virtual void v48();
	virtual void v4c();
	virtual void v50();
	virtual void v54();
	virtual void v58();
	virtual void v5c();
	virtual void v60();
	virtual void v64();
	virtual void v68();
	virtual void v6c();
	virtual void v70();
	virtual void v74();
	virtual void v78();
	virtual void v7c();
	virtual void v80();
	virtual void v84();
	virtual void v88();
	virtual void v8c();
	virtual void v90();
	virtual void v94();
	virtual void v98();
	virtual void v9c();
	virtual void vA0();
	virtual const char* allocStr( const char* str, int zero ); // 0xA4

	int pad04;
	int pad08;
	int pad0c;
	int pad10;
	int pad14;
	DictNode* m_buckets[10007]; // 0x18
	DictNode* m_freeList;       // 0x9C74
	int m_freeCount;            // 0x9C78

	DictNode* insert( int key, int flags, const char* str, int value );
};

DictNode* Dictionary::insert( int key, int flags, const char* str, int value )
{
	if ( m_freeCount == 0 )
	{
		m_freeCount = 100;
		m_freeList = (DictNode*)DebugAllocMemory( sizeof(DictNode) * 100 );
	}

	DictNode* node = m_freeList;
	m_freeCount--;
	m_freeList++; // advances by sizeof(DictNode)

	DictNode** bucket = &m_buckets[(unsigned int)key % 10007];
	
	node->m_next = *bucket;
	node->m_key = key;
	node->m_flags = flags;
	node->m_value = value;
	node->pad18 = 0;
	node->pad14 = 0;

	if ( flags & 4 )
	{
		node->m_str = allocStr( str, 0 );
	}
	else
	{
		if ( str )
		{
			node->m_str = strrchr( str, '\\' );
			if ( !node->m_str )
			{
				node->m_str = strrchr( str, '/' );
			}
			
			if ( node->m_str )
			{
				node->m_str++;
			}
			else
			{
				node->m_str = str;
			}
		}
		else
		{
			node->m_str = 0;
		}
	}

	*bucket = node;
	return node;
}
