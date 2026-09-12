// lane 25 scratch only: HorseHordeContainModuleData destructor reconstruction.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include <list>
#include <set>
#include <vector>

class BFMERetailAsciiString
{
public:
	~BFMERetailAsciiString() { releaseBuffer(); }

	void releaseBuffer();
	void set(const BFMERetailAsciiString &);

private:
	void *m_004;
};

#pragma comment(linker, "/alternatename:?set@BFMERetailAsciiString@@QAEXABV1@@Z=?set@?$StringBase@D@@QAEXABV1@@Z")

class AsciiString
{
public:
	~AsciiString() { ((BFMERetailAsciiString *)this)->releaseBuffer(); }
	AsciiString &operator=(const AsciiString &that)
	{
		((BFMERetailAsciiString *)this)->set(*(const BFMERetailAsciiString *)&that);
		return *this;
	}

private:
	void *m_data;
};

class BfmeHordeContainSplitResultList
{
public:
	virtual void slot0();
	~BfmeHordeContainSplitResultList();
};

#pragma comment(linker, "/alternatename:??1BfmeHordeContainSplitResultList@@QAE@XZ=?j_00017657@@YAXXZ")

class AudioEventRTS
{
public:
	~AudioEventRTS();

private:
	unsigned char m_data[0x70];
};

#pragma comment(linker, "/alternatename:??1AudioEventRTS@@QAE@XZ=?j_00026f35@@YAXXZ")

// The destructor only proves member layouts.  These names deliberately carry
// the target RVA until a source or field witness gives the records identities.
class Rva002469D0AudioEntry
{
public:
	~Rva002469D0AudioEntry() {}

private:
	BFMERetailAsciiString m_00;
	BFMERetailAsciiString m_04;
	AudioEventRTS m_08;
	AudioEventRTS m_78;
};

class Rva002469D0TwoAsciiEntry
{
public:
	~Rva002469D0TwoAsciiEntry() {}

private:
	BFMERetailAsciiString m_00;
	BFMERetailAsciiString m_04;
};

class Rva002469D0OneAsciiEntry
{
public:
	~Rva002469D0OneAsciiEntry() {}

private:
	BFMERetailAsciiString m_00;
};

struct Gen_t_002360c0_k4
{
	int m_00[1];
};

bool operator==(const Gen_t_002360c0_k4 &, const Gen_t_002360c0_k4 &);
bool operator<(const Gen_t_002360c0_k4 &, const Gen_t_002360c0_k4 &);
typedef _STL::_Rb_tree<Gen_t_002360c0_k4, Gen_t_002360c0_k4,
	_STL::_Identity<Gen_t_002360c0_k4>, _STL::less<Gen_t_002360c0_k4>,
	_STL::allocator<Gen_t_002360c0_k4> > Rva002469D0TreeK4;

class HordeSiegeEngineContainModuleDataBase
{
public:
	virtual ~HordeSiegeEngineContainModuleDataBase();

private:
	unsigned char m_004_to_223[0x220];
};

class HorseHordeContainModuleData
	: public HordeSiegeEngineContainModuleDataBase
{
public:
	virtual ~HorseHordeContainModuleData();

private:
	std::vector<BfmeHordeContainSplitResultList *> m_224;
	std::vector<Rva002469D0AudioEntry *> m_230;
	std::vector<Rva002469D0TwoAsciiEntry *> m_23c;
	AsciiString m_248;
	std::list<int> m_24c;
	Rva002469D0TreeK4 m_250;
	Rva002469D0TreeK4 m_25c;
	unsigned char m_pad268[0x24];
	std::vector<AsciiString> m_28c;
	unsigned char m_pad298[0xc];
	std::vector<Rva002469D0OneAsciiEntry *> m_2a4;
	std::vector<AsciiString> m_2b0;
	std::vector<AsciiString> m_2bc;
	unsigned char m_pad2c8[0xc];
	AsciiString m_2d4;
	unsigned char m_tail_2d8_to_2f3[0x1c];
};

typedef char Rva002469D0SizeCheck[(sizeof(HorseHordeContainModuleData) == 0x2f4) ? 1 : -1];

// ??1HorseHordeContainModuleData@@UAE@XZ
HorseHordeContainModuleData::~HorseHordeContainModuleData()
{
	for (unsigned int i = 0; i < m_224.size(); ++i)
	{
		delete m_224[i];
	}
	m_224.clear();

	for (unsigned int i = 0; i < m_230.size(); ++i)
	{
		delete m_230[i];
	}
	m_230.clear();

	for (unsigned int i = 0; i < m_23c.size(); ++i)
	{
		delete m_23c[i];
	}
	m_23c.clear();

	m_24c.clear();
	m_250.clear();
	m_25c.clear();
	m_28c.clear();
	m_2b0.clear();

	for (unsigned int i = 0; i < m_2a4.size(); ++i)
	{
		delete m_2a4[i];
	}
	m_2a4.clear();
	m_2bc.clear();
}
