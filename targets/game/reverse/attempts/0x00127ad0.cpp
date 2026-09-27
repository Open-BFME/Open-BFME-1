// ??0RubbleRiseUpdateModuleData@@QAE@XZ
// partial score=0.97 date=2026-09-27
// cl: /DNDEBUG /MD /EHsc
// Retail 0x00127AD0 .. 0x00127B99 (202 B): the default constructor of
// RubbleRiseUpdateModuleData, the module data RubbleRiseUpdate allocates in
// the matched friend_newModuleData (0x00127BD0, `operator new(0xD4)` then this
// ctor).  Its vtable is 0x0108EAF8, whose slot zero routes to the matched
// scalar deleting destructor 0x00128BA0, and the matched buildFieldParse
// (0x002A4190) names the INI offsets this body initialises, so the identity
// and the field roles below are witnessed, not guessed.

// Retail calls this ctor with ecx = this + 8; its body is the matched
// DieMux-role constructor at 0x002551A0, which fills 0x2C bytes.
class Rva002551A0DieMuxData
{
public:
	Rva002551A0DieMuxData();

private:
	unsigned char m_pad[0x2c];
};

// Retail fills both 4-element arrays through the EH vector constructor
// iterator, which takes one construction and one destruction proc per
// element.  Every element is 0x0C bytes.  The procs are out-of-line bodies
// with no recovered identity, so the two element types carry the address of
// their constructor: 0x00127AB0 (m_a) and 0x00127AC0 (m_b).
class Rva00127AB0Element
{
public:
	Rva00127AB0Element();
	~Rva00127AB0Element();

private:
	unsigned char m_pad[0x0c];
};

class Rva00127AC0Element
{
public:
	Rva00127AC0Element();
	~Rva00127AC0Element();

private:
	unsigned char m_pad[0x0c];
};

// The destructor at 0x00128BD0 stores 0x01073744 (??_7BfmeBase@@6B@) into
// *this before returning, so the immediate base is polymorphic and 8 bytes
// wide; its own ctor emits nothing and this one installs the vtable.
class RubbleRiseUpdateModuleDataBase
{
public:
	virtual ~RubbleRiseUpdateModuleDataBase() {}

private:
	unsigned char m_pad[4];
};

class RubbleRiseUpdateModuleData : public RubbleRiseUpdateModuleDataBase
{
public:
	RubbleRiseUpdateModuleData();
	virtual ~RubbleRiseUpdateModuleData();

private:
	Rva002551A0DieMuxData m_dieMux;			// 0x08
	unsigned long m_minRubbleRiseDelay;		// 0x34
	unsigned long m_maxRubbleRiseDelay;		// 0x38
	unsigned long m_minBurstDelay;			// 0x3c
	unsigned long m_maxBurstDelay;			// 0x40
	int m_bigBurstFrequency;					// 0x44
	float m_rubbleRiseDamping;				// 0x48
	float m_rubbleHeight;					// 0x4c
	float m_maxShudder;						// 0x50
	Rva00127AB0Element m_a[4];				// 0x54
	Rva00127AC0Element m_b[4];				// 0x84
	unsigned long m_flags[4][2];			// 0xb4
};

// ??0RubbleRiseUpdateModuleData@@QAE@XZ
RubbleRiseUpdateModuleData::RubbleRiseUpdateModuleData()
{
	m_minRubbleRiseDelay = 0;
	m_maxRubbleRiseDelay = 0;
	m_maxShudder = 0.0f;
	m_rubbleRiseDamping = 0.0f;
	m_rubbleHeight = 0.0f;
	m_bigBurstFrequency = 0;
	m_minBurstDelay = 9999;
	unsigned long i;
	for (i = 0; i < 4; i++) {
		m_flags[i][0] = 1;
		m_flags[i][1] = 1;
	}
}
