// cl: /DNDEBUG /MD
// Open-BFME: containment dispatch body at retail RVA 0x00227B60, 103 bytes.

typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef int Int;

class Object
{
public:
	unsigned char m_padding[0x214];
	UnsignedInt m_objectField;

	void clearModelConditionState( Int flag );
};

class BfmeFinishDispatcherAGA
{
public:
	void step( Object *object, Bool flag );
};

struct Rva00227B60QueryResult
{
	UnsignedInt m_words[3];
};

class Rva00227B60ContainDispatch
{
public:
#define RVASLOT(n) virtual void *slot##n();
	RVASLOT(00) RVASLOT(01) RVASLOT(02) RVASLOT(03)
	RVASLOT(04) RVASLOT(05) RVASLOT(06) RVASLOT(07)
	RVASLOT(08) RVASLOT(09) RVASLOT(10) RVASLOT(11)
	RVASLOT(12) RVASLOT(13) RVASLOT(14) RVASLOT(15)
	RVASLOT(16) RVASLOT(17) RVASLOT(18) RVASLOT(19)
	RVASLOT(20) RVASLOT(21) RVASLOT(22) RVASLOT(23)
	RVASLOT(24) RVASLOT(25) RVASLOT(26) RVASLOT(27)
	RVASLOT(28) RVASLOT(29) RVASLOT(30) RVASLOT(31)
	RVASLOT(32) RVASLOT(33) RVASLOT(34) RVASLOT(35)
	RVASLOT(36) RVASLOT(37) RVASLOT(38)
	virtual void *query( Rva00227B60QueryResult *out, Object *object );
#undef RVASLOT

	void dispatch( Object *object, Bool flag );
};

void Rva00227B60ContainDispatch::dispatch( Object *object, Bool flag )
{
	Rva00227B60QueryResult local;
	if ( object == 0 || object->m_objectField != *(UnsignedInt *)((char *)this - 0x18) )
		return;

	void *result = query( &local, object );
	if ( ((unsigned char *)result)[0] & 2 )
	{
		result = query( &local, object );
		if ( (*(UnsignedInt *)((char *)result + 4) & 0x10000000) == 0 )
			object->clearModelConditionState( 5 );
	}
	((BfmeFinishDispatcherAGA *)((char *)this - 0x20))->step( object, flag );
}
