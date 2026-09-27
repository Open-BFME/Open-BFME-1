// cl: /DNDEBUG /MD /EHsc
// Retail 0x00127AD0 .. 0x00127B99 (202 B): the default constructor of
// RubbleRiseUpdateModuleData.
//
// Identity is witnessed, not inherited from the lift name:
//  - the MATCHED caller ?friend_newModuleData@RubbleRiseUpdate@@SAPAVModuleData@@PAV@Z
//    (0x00127BD0, game/GameEngine/Source/GameLogic/Object/Update/
//    RubbleRiseUpdateFriendNewModuleDataThunk.cpp) does `operator new(0xD4)`
//    and runs this constructor on the result, so the class and the 0xD4 size
//    are both fixed by matched code;
//  - this body installs vtable 0x0108EAF8, whose slot zero routes to the
//    MATCHED scalar deleting destructor ??_GRubbleRiseUpdateModuleData@@UAEPAXI@Z
//    at 0x00128BA0;
//  - the MATCHED buildFieldParse (0x002A4190) names the field roles below:
//    its FieldParse table (built at 0x010C2AB0) binds the INI keys
//    MinRubbleRiseDelay/MaxRubbleRiseDelay/MinBurstDelay/MaxBurstDelay/
//    RubbleRiseDamping/RubbleHeight/MaxShudder/BigBurstFrequency to offsets
//    0x34/0x38/0x3c/0x40/0x48/0x4c/0x50/0x44, and its
//    `p.add(DieMuxData::getFieldParse(), 8)` is the DieMux sub-object at +8
//    that this body constructs.

// Retail calls this ctor's DieMux-role constructor with ecx = this + 8; its
// body is the matched DieMuxData constructor at 0x002551A0, reached through
// the 5-byte thunk pinned at 0x000071E4, and it fills 0x2C bytes.
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
	unsigned long m_minRubbleRiseDelay;		// 0x34, "MinRubbleRiseDelay"
	unsigned long m_maxRubbleRiseDelay;		// 0x38, "MaxRubbleRiseDelay"
	unsigned long m_minBurstDelay;			// 0x3c, "MinBurstDelay"
	unsigned long m_maxBurstDelay;			// 0x40, "MaxBurstDelay"
	int m_bigBurstFrequency;					// 0x44, "BigBurstFrequency"
	float m_rubbleRiseDamping;				// 0x48, "RubbleRiseDamping"
	float m_rubbleHeight;					// 0x4c, "RubbleHeight"
	float m_maxShudder;						// 0x50, "MaxShudder"
	Rva00127AB0Element m_a[4];				// 0x54
	Rva00127AC0Element m_b[4];				// 0x84
	unsigned long m_dwordB4[4];				// 0xb4, initialised to 1
	unsigned long m_dwordC4[4];				// 0xc4, initialised to 1
};

// ??0RubbleRiseUpdateModuleData@@QAE@XZ
//
// The assignment order below is retail's, not the field order: 0x34, 0x38,
// 0x50, 0x48, 0x4c, 0x44, then the 0x270f at 0x3c, then the two 4-element
// runs.  The two tail runs are ONE loop over two separate arrays, which is
// what makes retail emit the pairs interleaved (0xb4, 0xc4, 0xb8, 0xc8,
// 0xbc, 0xcc, 0xc0, 0xd0) with the constant 1 materialised once in ebx;
// declared as one [4][2] array the unrolled stores come out ascending
// instead, which is the only byte difference that shape makes.
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
		m_dwordB4[i] = 1;
		m_dwordC4[i] = 1;
	}
}
