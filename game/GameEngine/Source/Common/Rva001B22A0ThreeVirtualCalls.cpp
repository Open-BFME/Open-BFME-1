struct Rva001B22A0Flags
{
	bool m_first;
	bool m_second;
};

class Rva001B22A0Interface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void setFlags( Rva001B22A0Flags *flags );
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual void setFirstValue( void *value );
	virtual void slot70();
	virtual void slot74();
	virtual void setSecondValue( void *value );
};

class Rva001B22A0Owner
{
public:
	void applyTo( Rva001B22A0Interface *target );

	char m_unmodelled_00[ 8 ];
	int m_firstValue;
	int m_secondValue;
};

void Rva001B22A0Owner::applyTo( Rva001B22A0Interface *target )
{
	Rva001B22A0Flags flags = { true, true };
	target->setFlags( &flags );
	target->setFirstValue( &m_firstValue );
	target->setSecondValue( &m_secondValue );
}
