// cl: /DNDEBUG /MD /EHsc
// Address-derived linked GUI object destructor at retail 0x00490350.

class Rva00490350Base;
extern Rva00490350Base *Rva00490350Head;

class Rva00490350Link
{
public:
	virtual void slot0();
	virtual void detach( int token );
};

class Rva00490350Base
{
public:
	virtual ~Rva00490350Base();
	virtual void slot1();

protected:
	Rva00490350Link *m_link;
	int m_unused;
	int m_token;
};

class Rva00490350Derived : public Rva00490350Base
{
public:
	virtual ~Rva00490350Derived();
	virtual void slot1();
};

Rva00490350Base::~Rva00490350Base()
{
	if( Rva00490350Head == this )
		Rva00490350Head = (Rva00490350Base *)m_link;
}

Rva00490350Derived::~Rva00490350Derived()
{
	if( m_link )
		m_link->detach( m_token );
}
