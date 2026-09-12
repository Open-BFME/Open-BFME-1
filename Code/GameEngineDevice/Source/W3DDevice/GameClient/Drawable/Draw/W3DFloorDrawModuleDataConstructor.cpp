// cl: /DNDEBUG /MD /EHsc

// W3DFloorDrawModuleData's constructor, retail 0x007516C0.
//
// The base constructor is 0x00759460, which nothing in the image names; it is
// pinned here under a stand-in and runs to +0x0C, where this class's three
// flags and one dword sit.
//
// Retail writes the vftable pointer LAST, after all four fields - which is what
// MSVC does on its own once there are several independent stores to sink it
// past. Nothing in the source has to ask for that.

class W3DFloorDrawModuleDataBase
{
public:
	W3DFloorDrawModuleDataBase();
	virtual ~W3DFloorDrawModuleDataBase();

	virtual void moduleDataAnchor();

private:
	unsigned char m_unmodelled_04[8];
};

class W3DFloorDrawModuleData : public W3DFloorDrawModuleDataBase
{
public:
	W3DFloorDrawModuleData();
	virtual ~W3DFloorDrawModuleData();

private:
	bool m_unmodelled_0C;					// +0x0C
	bool m_unmodelled_0D;					// +0x0D
	bool m_unmodelled_0E;					// +0x0E
	int m_unmodelled_10;					// +0x10
};

W3DFloorDrawModuleData::W3DFloorDrawModuleData()
	: m_unmodelled_0C( false ),
	  m_unmodelled_0D( false ),
	  m_unmodelled_0E( false ),
	  m_unmodelled_10( 0 )
{
}

W3DFloorDrawModuleData::~W3DFloorDrawModuleData()
{
}
