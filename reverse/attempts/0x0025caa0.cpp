// ?run@Rva0025CAA0ElvenWoodDispatch@@QAEXPAVRva0025CAA0Subject@@PAVRva0025CAA0Context@@@Z
// partial score=0.97 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc

class Rva0025CAA0Owner
{
public:
	unsigned char m_lead[ 0x1a4 ];
	int m_gate;
};

struct Rva0025CAA0Token
{
	unsigned char m_lead[ 4 ];
	unsigned short m_count;
};

class Rva0025CAA0TokenSlot
{
public:
	Rva0025CAA0Token *get() { return m_token; }
private:
	Rva0025CAA0Token *m_token;
};

struct Rva0025CAA0Record
{
	Rva0025CAA0TokenSlot &tokenSlot()
	{
		return *(Rva0025CAA0TokenSlot *)( (char *)this + 0x21c );
	}
};

class Rva0025CAA0Subject;
class Rva0025CAA0Context;

class Rva0025CAA0Primary
{
public:
	void finish( Rva0025CAA0Subject *subject );
};

class Rva0025CAA0ElvenWoodDispatch
{
public:
	void run( Rva0025CAA0Subject *subject, Rva0025CAA0Context *context );
	void apply( Rva0025CAA0Subject *subject, Rva0025CAA0Context *context );
};

void Rva0025CAA0ElvenWoodDispatch::run(
	Rva0025CAA0Subject *subject, Rva0025CAA0Context *context )
{
	Rva0025CAA0Owner *owner = *(Rva0025CAA0Owner **)( (char *)this - 8 );
	if ( owner->m_gate != 0 )
		return;
	if ( subject == 0 )
		return;
	Rva0025CAA0Record *record = *(Rva0025CAA0Record **)( (char *)this - 0x0c );
	Rva0025CAA0Token *token = record->tokenSlot().get();
	if ( token == 0 || token->m_count == 0 )
		return;
	apply( subject, context );
	( (Rva0025CAA0Primary *)( (char *)this - 0x10 ) )->finish( subject );
}
