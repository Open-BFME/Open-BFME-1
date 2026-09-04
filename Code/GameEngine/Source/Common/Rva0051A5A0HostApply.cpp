// cl: /O2
// thiscall @ 0x0051A5A0, 29 bytes. Calls the still-dumped setup at 0x00518FF0
// with imm 0, then the landed BfmeQ1078::bfmeGo1078A, then tail-jumps to
// Gen_00525EE0::bfmeShutdown on the subobject at +0x25C -- the same shutdown
// body Rva00579390NestedShutdown.cpp already tails to. Identity of the host
// is not recovered; the name is address-derived.

class BfmeQ1078
{
public:
	void bfmeGo1078A( void );
};

class Gen_00525EE0
{
public:
	void bfmeShutdown( void );
};

class Rva0051A5A0Host : public BfmeQ1078
{
public:
	void apply( void );
	void setup( int );

private:
	char m_lead[ 0x25C ];
	Gen_00525EE0 m_sub;
};

void Rva0051A5A0Host::apply( void )
{
	setup( 0 );
	bfmeGo1078A();
	m_sub.bfmeShutdown();
}
