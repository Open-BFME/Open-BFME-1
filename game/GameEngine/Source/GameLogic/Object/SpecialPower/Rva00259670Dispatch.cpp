// cl: /DNDEBUG /MD /EHsc
// Sibling of Rva0025D7E0FreezingRainDispatch::run with an extra this-adjusted
// call through ILT 0x00036561 to body 0x00259160 after finish.

class Rva0025D7E0Owner
{
public:
	unsigned char m_lead[ 0x1a4 ];
	int m_gate;
};

class Rva0025D7E0Subject;
class Rva0025D7E0Context;

class Rva0025D7E0FreezingRainDispatch
{
};

class Rva00259670Primary
{
};

class Rva00259160Owner
{
public:
	void applyToFilteredObjects();
};

class Rva00259670Dispatch : public Rva0025D7E0FreezingRainDispatch
{
public:
	void run( Rva0025D7E0Subject *subject, Rva0025D7E0Context *context );
};

extern void j_000170da();
extern void j_00041a4c();

void Rva00259670Dispatch::run(
	Rva0025D7E0Subject *subject, Rva0025D7E0Context *context )
{
	Rva0025D7E0Owner *owner = *(Rva0025D7E0Owner **)( (char *)this - 8 );
	if ( owner->m_gate != 0 )
		return;
	if ( subject == 0 )
		return;
	typedef void (Rva0025D7E0FreezingRainDispatch::*ApplyCall)(
		Rva0025D7E0Subject *, Rva0025D7E0Context *);
	union { void (*raw)(); ApplyCall member; } apply;
	apply.raw = j_000170da;
	(this->*apply.member)(subject, context);
	Rva00259670Primary *primary = (Rva00259670Primary *)( (char *)this - 0x10 );
	typedef void (Rva00259670Primary::*FinishCall)(Rva0025D7E0Subject *);
	union { void (*raw)(); FinishCall member; } finish;
	finish.raw = j_00041a4c;
	(primary->*finish.member)(subject);
	((Rva00259160Owner *)primary)->applyToFilteredObjects();
}
