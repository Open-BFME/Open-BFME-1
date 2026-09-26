// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-

struct Rva00751EC0Flags
{
	bool m_first;
	bool m_second;
};

class Rva00751EC0Target
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual bool isReady();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void setFlags( const Rva00751EC0Flags *flags );
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual bool bind( void *configuration );
};

class Rva00751EC0Owner
{
public:
	void updateTarget( Rva00751EC0Target *target );

private:
	void prepare( Rva00751EC0Target *target );
	unsigned char m_opaque[0x280];
	unsigned char m_configuration;
};

void Rva00751EC0Owner::updateTarget( Rva00751EC0Target *target )
{
	prepare( target );
	if( !target->isReady() )
	{
		target->bind( &m_configuration );
		Rva00751EC0Flags flags = { true, true };
		target->setFlags( &flags );
	}
}
