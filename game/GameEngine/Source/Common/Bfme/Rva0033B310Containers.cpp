// 16-byte, 17-byte, 20-byte, 16-byte, 20-byte, and 17-byte container element accessors

struct Item20
{
	int  m_field0;
	int  m_field4;
	int  m_field8;
	int  m_fieldC;
	int *m_ptr10;
};

class Container0C
{
public:
	int  getField0( int index );
	int *getField8Ptr( int index );

	char    m_pad0[ 0xC ];
	Item20 *m_items;
};

int Container0C::getField0( int index )
{
	return m_items[ index ].m_field0;
}

int *Container0C::getField8Ptr( int index )
{
	return &m_items[ index ].m_field8;
}

struct RefObj
{
	int m_pad0;
	int m_index;
};

class Container38
{
public:
	int *getField8PtrByRef( RefObj *ref );
	int  getField0( int index );
	int *getPtr10Plus4( int index );
	int *getField8Ptr( int index );

	char    m_pad0[ 0x38 ];
	Item20 *m_items;
};

int *Container38::getField8PtrByRef( RefObj *ref )
{
	return &m_items[ ref->m_index ].m_field8;
}

int Container38::getField0( int index )
{
	return m_items[ index ].m_field0;
}

int *Container38::getPtr10Plus4( int index )
{
	return m_items[ index ].m_ptr10 + 1;
}

int *Container38::getField8Ptr( int index )
{
	return &m_items[ index ].m_field8;
}
