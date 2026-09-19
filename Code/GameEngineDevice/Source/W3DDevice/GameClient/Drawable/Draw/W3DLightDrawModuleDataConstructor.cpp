// cl: /DNDEBUG /MD /EHsc

// W3DLightDrawModuleData's constructor, retail 0x00758780. No base constructor
// call: the class writes its own vftable pointer at +0x00 and leaves +0x04 alone.
//
// Two things the store order says. The field at +0x44 is written first, which
// is the member-init list running ahead of the body - it is the only field in
// the list. And the first nine fields come out in DESCENDING order in groups of
// three: +0x10, +0x0C, +0x08, then +0x1C, +0x18, +0x14, then +0x28, +0x24,
// +0x20. That is chained assignment - `a = b = c = 0' assigns right to left -
// not nine statements, which would come out ascending.

class W3DLightDrawModuleDataBase
{
public:
	virtual void moduleDataAnchor();

private:
	unsigned char m_unmodelled_04[4];
};

class W3DLightDrawModuleData : public W3DLightDrawModuleDataBase
{
public:
	W3DLightDrawModuleData();

private:
	float m_unmodelled_08;					// +0x08
	float m_unmodelled_0C;					// +0x0C
	float m_unmodelled_10;					// +0x10
	float m_unmodelled_14;					// +0x14
	float m_unmodelled_18;					// +0x18
	float m_unmodelled_1C;					// +0x1C
	float m_unmodelled_20;					// +0x20
	float m_unmodelled_24;					// +0x24
	float m_unmodelled_28;					// +0x28
	float m_unmodelled_2C;					// +0x2C
	float m_unmodelled_30;					// +0x30
	int m_unmodelled_34;					// +0x34
	int m_unmodelled_38;					// +0x38
	int m_unmodelled_3C;					// +0x3C
	int m_unmodelled_40;					// +0x40
	int m_unmodelled_44;					// +0x44
};

W3DLightDrawModuleData::W3DLightDrawModuleData()
	: m_unmodelled_44( 0 )
{
	m_unmodelled_08 = m_unmodelled_0C = m_unmodelled_10 = 0;
	m_unmodelled_14 = m_unmodelled_18 = m_unmodelled_1C = 0;
	m_unmodelled_20 = m_unmodelled_24 = m_unmodelled_28 = 0;

	m_unmodelled_2C = 20.0f;
	m_unmodelled_30 = 1.0f;

	m_unmodelled_34 = 0;
	m_unmodelled_38 = 0;
	m_unmodelled_3C = 0;
	m_unmodelled_40 = 0;
}
