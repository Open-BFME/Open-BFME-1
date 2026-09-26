// cl: /DNDEBUG /MD /GX- /O2 /Ob2

class V3HostRva005E76E0
{
public:
	char m_pad00[ 0x0c ];
	unsigned int m_values[ 7 ];
};

class Rva005FFAC0OwnerBase
{
public:
	Rva005FFAC0OwnerBase( void *owner ) : m_owner( owner ) {}
	virtual void ownerSlot();

private:
	void *m_owner;
};

class Rva005FFAC0InterfaceBase
{
public:
	virtual void interfaceSlot();
};

class Rva005FFAC0ValuesVtableBase
{
public:
	virtual void valuesSlot();
};

class Rva005FFAC0ValuesBase : public Rva005FFAC0ValuesVtableBase
{
public:
	Rva005FFAC0ValuesBase()
		: m_trailingValue( 1 )
	{
		m_values[ 0 ] = 0;
		m_values[ 1 ] = 0;
		m_values[ 2 ] = 0;
		m_values[ 3 ] = 0;
		m_values[ 4 ] = 0;
		m_values[ 5 ] = 0;
	}
protected:
	unsigned int m_values[ 6 ];
	unsigned int m_trailingValue;
};

class Rva005FFAC0
	: public Rva005FFAC0OwnerBase,
	  public Rva005FFAC0InterfaceBase,
	  public Rva005FFAC0ValuesBase
{
public:
	Rva005FFAC0( void *owner, V3HostRva005E76E0 *source );
	virtual void stateSlot();
};

Rva005FFAC0::Rva005FFAC0( void *owner, V3HostRva005E76E0 *source )
	: Rva005FFAC0OwnerBase( owner )
{
	m_values[ 0 ] = source->m_values[ 0 ];
	m_values[ 1 ] = source->m_values[ 1 ];
	m_values[ 2 ] = source->m_values[ 2 ];
	m_values[ 3 ] = source->m_values[ 3 ];
	m_values[ 4 ] = source->m_values[ 4 ];
	m_values[ 5 ] = source->m_values[ 5 ];
	m_trailingValue = source->m_values[ 6 ];
}
