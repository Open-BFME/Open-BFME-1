// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: HTreeClass default ctor + dtor

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/htree.h
class HTreeClass
{
public:
	HTreeClass();
	~HTreeClass();

private:
	void Free();

	unsigned char m_name0;
	unsigned char m_pad[0xf];
	void *m_pivots;
	void *m_pivotCountOrPtr;
	float m_scale;
};

void __cdecl operator delete(void *);

// ??0HTreeClass@@QAE@XZ
HTreeClass::HTreeClass()
{
	m_pivots = 0;
	m_pivotCountOrPtr = 0;
	m_scale = 1.0f;
	m_name0 = 0;
}

// ?Free@HTreeClass@@AAEXXZ
// Retail 0x00952230 sits between the ctor and Get_Bone_Index; Load_W3D calls it
// through ILT on hierarchy load failure.
void HTreeClass::Free()
{
	if (m_pivotCountOrPtr)
	{
		operator delete(m_pivotCountOrPtr);
		m_pivotCountOrPtr = 0;
	}
	m_pivots = 0;
	m_scale = 1.0f;
}

// ??1HTreeClass@@QAE@XZ
HTreeClass::~HTreeClass()
{
	if (m_pivotCountOrPtr)
	{
		operator delete(m_pivotCountOrPtr);
		m_pivotCountOrPtr = 0;
	}
	m_pivots = 0;
	m_scale = 1.0f;
}
