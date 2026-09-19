// cl: /DNDEBUG /MD /EHsc

// W3DStreakDrawModuleData's constructor, retail 0x0077D450. No base constructor
// call: the class writes its own vftable pointer at +0x00 and leaves +0x04 alone.
//
// The field at +0x20 is written FIRST, before the six below it. That is the
// member-init list running before the constructor body - it is the only field
// in the list, and the rest are statements.

class W3DStreakDrawModuleDataBase
{
public:
	virtual void moduleDataAnchor();

private:
	unsigned char m_unmodelled_04[4];
};

class W3DStreakDrawModuleData : public W3DStreakDrawModuleDataBase
{
public:
	W3DStreakDrawModuleData();

private:
	float m_unmodelled_08;					// +0x08
	float m_unmodelled_0C;					// +0x0C
	float m_unmodelled_10;					// +0x10
	float m_unmodelled_14;					// +0x14
	float m_unmodelled_18;					// +0x18
	int m_unmodelled_1C;					// +0x1C
	int m_unmodelled_20;					// +0x20
};

W3DStreakDrawModuleData::W3DStreakDrawModuleData()
	: m_unmodelled_20( 0 )
{
	m_unmodelled_08 = 50.0f;
	m_unmodelled_0C = 0.5f;
	m_unmodelled_10 = 1.0f;
	m_unmodelled_14 = 1.0f;
	m_unmodelled_18 = 1.0f;
	m_unmodelled_1C = 5;
}
