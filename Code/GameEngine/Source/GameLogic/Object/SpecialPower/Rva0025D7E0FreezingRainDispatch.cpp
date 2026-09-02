// cl: /DNDEBUG /MD /EHsc

class Rva0025D7E0Owner
{
public:
	unsigned char m_lead[ 0x1a4 ];
	int m_gate;
};

class Rva0025D7E0Subject;
class Rva0025D7E0Context;

class Rva0025D7E0Primary
{
public:
	void finish( Rva0025D7E0Subject *subject );
};

class Rva0025D7E0FreezingRainDispatch
{
public:
	void run( Rva0025D7E0Subject *subject, Rva0025D7E0Context *context );
	void apply( Rva0025D7E0Subject *subject, Rva0025D7E0Context *context );
};

void Rva0025D7E0FreezingRainDispatch::run(
	Rva0025D7E0Subject *subject, Rva0025D7E0Context *context )
{
	Rva0025D7E0Owner *owner = *(Rva0025D7E0Owner **)( (char *)this - 8 );
	if ( owner->m_gate != 0 )
		return;
	if ( subject == 0 )
		return;
	apply( subject, context );
	( (Rva0025D7E0Primary *)( (char *)this - 0x10 ) )->finish( subject );
}
