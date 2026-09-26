// cl: /DNDEBUG /MD /EHsc

// Address-derived reconstruction of the ScavengerSpecialPower interface call
// between its module-name getter and module-data constructor.

class Rva00265A00Result
{
public:
	void touch();
};

class Rva00265A00Owner
{
public:
	Rva00265A00Result *lookup( int key );
};

struct Rva00265A00Record
{
	unsigned char m_lead[ 0x210 ];
	int m_key;
};

class Rva00265A00ScavengerDispatch
{
public:
	void invoke( int value );
	void forward( int value );
};

void Rva00265A00ScavengerDispatch::invoke( int value )
{
	Rva00265A00Record *record = *(Rva00265A00Record **)( (char *)this - 0x0c );
	Rva00265A00Owner *owner = *(Rva00265A00Owner **)( (char *)this - 0x08 );
	owner->lookup( record->m_key )->touch();
	forward( value );
}
