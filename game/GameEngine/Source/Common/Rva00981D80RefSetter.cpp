// cl: /O2 /Ob2 /DNDEBUG /MD /EHsc

class Rva00981D80Ref
{
public:
	virtual void release();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual void unused08();
	virtual void unused09();
	virtual void unused10();
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	virtual void unused14();
	virtual void unused15();
	virtual void unused16();
	virtual void unused17();
	virtual void unused18();
	virtual void unused19();
	virtual void unused20();
	virtual void unused21();
	virtual void unused22();
	virtual void unused23();
	virtual void unused24();
	virtual void unused25();
	virtual void unused26();
	virtual void unused27();
	virtual void unused28();
	virtual void unused29();
	virtual void unused30();
	virtual void unused31();
	virtual void unused32();
	virtual void unused33();
	virtual void unused34();
	virtual void unused35();
	virtual void unused36();
	virtual void unused37();
	virtual void unused38();
	virtual void unused39();
	virtual void unused40();
	virtual void unused41();
	virtual void unused42();
	virtual void unused43();
	virtual void unused44();
	virtual void unused45();
	virtual void unused46();
	virtual void unused47();
	virtual void unused48();
	virtual void unused49();
	virtual void unused50();
	virtual void unused51();
	virtual void unused52();
	virtual void unused53();
	virtual void unused54();
	virtual void unused55();
	virtual void unused56();
	virtual int validate();

	int m_referenceCount;
};

class Rva00981D80
{
public:
	void setReference( Rva00981D80Ref *reference );

private:
	char m_pad00[ 0x100 ];
	Rva00981D80Ref *m_reference;
};

void Rva00981D80::setReference( Rva00981D80Ref *reference )
{
	if ( reference != 0 && !reference->validate() )
		reference = 0;

	if ( reference == m_reference )
		return;

	if ( reference != 0 )
		++reference->m_referenceCount;

	Rva00981D80Ref *oldReference = m_reference;
	if ( oldReference != 0 && --oldReference->m_referenceCount == 0 )
		oldReference->release();

	m_reference = reference;
}
