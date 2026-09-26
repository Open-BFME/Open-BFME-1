// Clean C++ conversion of the C-string hash-table lookup at retail RVA
// 0x009D76F0.  The matched caller family remains declaration-only in
// SelfPairReturners.cpp so its 28-byte hidden-return ABI stays unchanged.

struct BfmeStringNode009D76F0
{
	BfmeStringNode009D76F0 *next;
	const char *key;
};

struct BfmeStringBuckets009D76F0
{
	BfmeStringNode009D76F0 **begin;
	BfmeStringNode009D76F0 **end;

	unsigned int size( void ) const
	{
		return static_cast<unsigned int>( end - begin );
	}

	BfmeStringNode009D76F0 *&operator[]( unsigned int index )
	{
		return begin[index];
	}
};

struct BfmeStringHash009D76F0
{
	unsigned int operator()( const char *text ) const
	{
		unsigned int value = 0;
		char ch = *text;
		if( ch != 0 )
		{
			do
			{
				value = value * 5 + static_cast<signed char>( ch );
				ch = *++text;
			}
			while( ch != 0 );
		}
		return value;
	}
};

class Gen009D76F0
{
public:
	void *evaluate( void *argument );
	unsigned char pad[4];
	BfmeStringBuckets009D76F0 buckets;
};

void *Gen009D76F0::evaluate( void *argument )
{
	const char *const &key = *static_cast<const char **>( argument );
	Gen009D76F0 *table = this;
	unsigned int bucket = BfmeStringHash009D76F0()( key ) %
		table->buckets.size();
	BfmeStringNode009D76F0 *node;
	for( node = table->buckets[bucket];
		node != 0 && node->key != key;
		node = node->next )
	{
	}
	return node;
}
