// cl: /DNDEBUG /MD /EHsc

// ReflectDamageModuleData's constructor, retail 0x002516D0. No base constructor call at
// all - the class writes its own vftable pointer at +0x00 and leaves the base's
// word at +0x04 alone, which is what an implicit base constructor looks like.
// Everything from +0x08 is this class's own.

class ReflectDamageModuleDataBase
{
public:
	virtual void moduleDataAnchor();

private:
	unsigned char m_unmodelled_04[4];
};

class ReflectDamageModuleData : public ReflectDamageModuleDataBase
{
public:
	ReflectDamageModuleData();

private:
	int m_unmodelled_08;					// +0x08
	int m_unmodelled_0C;					// +0x0C
	int m_unmodelled_10;					// +0x10
};

ReflectDamageModuleData::ReflectDamageModuleData()
	: m_unmodelled_08( 0 ),
	  m_unmodelled_0C( 0 ),
	  m_unmodelled_10( 0 )
{
}
