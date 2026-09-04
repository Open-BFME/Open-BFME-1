// cl: /O2 /Ob0

class BinkVideoPlayer
{
public:
	__declspec(nothrow) BinkVideoPlayer();

private:
	char m_pad00[8];

public:
	unsigned int m_state;

private:
	char m_pad0c[9];
};

class Gen0069CBC0
{
public:
	void *evaluate( void *argument );
};

class Gen_dtor_00695260
{
public:
	virtual ~Gen_dtor_00695260();
};

struct SelfPair006A1650
{
	SelfPair006A1650( void *value, void *owner ) : m_value( value ), m_owner( owner ) { }
	void *m_value;
	void *m_owner;
};

class Rva006A1650Maker
{
public:
	SelfPair006A1650 *make( SelfPair006A1650 *result, void *argument );
};

SelfPair006A1650 *Rva006A1650Maker::make( SelfPair006A1650 *result, void *argument )
{
	BinkVideoPlayer local;
	local.m_state = (unsigned int)argument;
	argument = &local;
	result->m_value = ((Gen0069CBC0 *)this)->evaluate( &argument );
	result->m_owner = this;
	((Gen_dtor_00695260 *)&local)->Gen_dtor_00695260::~Gen_dtor_00695260();
	return result;
}
