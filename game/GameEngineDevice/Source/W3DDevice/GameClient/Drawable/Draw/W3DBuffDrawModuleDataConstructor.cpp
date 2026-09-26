// cl: /DNDEBUG /MD /EHsc

// W3DBuffDrawModuleData's constructor, retail 0x00750410. No base constructor
// call: this class's own vftable pointer at +0x00, the base's word at +0x04 left
// alone, and two fields of its own zeroed off one cleared register.

class W3DBuffDrawModuleDataBase
{
public:
	virtual void moduleDataAnchor();

private:
	unsigned char m_unmodelled_04[4];
};

class W3DBuffDrawModuleData : public W3DBuffDrawModuleDataBase
{
public:
	W3DBuffDrawModuleData();

private:
	int m_unmodelled_08;					// +0x08
	bool m_unmodelled_0C;					// +0x0C
};

W3DBuffDrawModuleData::W3DBuffDrawModuleData()
	: m_unmodelled_08( 0 ), m_unmodelled_0C( false )
{
}
