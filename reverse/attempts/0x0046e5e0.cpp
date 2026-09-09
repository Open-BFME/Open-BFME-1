// ??0Rva00579160Manager@@QAE@XZ
// partial score=0.85 date=2026-09-09
// The constructor at retail 0x0046E5E0 is the singleton manager whose global
// pointer is ?Rva00579160TheManager.  Its seventeen-state unwind map (FuncInfo
// 0x01215D40) reads straight off the members: a SubsystemInterface base, eight
// reserve(100) vectors -- each contributing one state for its own inner handle
// and one for the vector itself -- and a twelve-element array built through the
// EH vector constructor iterator, which carries no state of its own.

class SubsystemInterface
{
public:
	SubsystemInterface();                                      ///< matched 0x009A1A30
	virtual ~SubsystemInterface();                             ///< matched 0x009A1A40

private:
	unsigned int m_pad04;
};

class BfmeVecHolderVNH
{
public:
	BfmeVecHolderVNH() : m_data(0) { }
	~BfmeVecHolderVNH();                                       ///< pinned 0x0001570D

	void *m_data;
};

#define BFME_VNH_VECTOR( NAME )                                           \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		NAME()                                                            \
		{                                                                 \
			m_at08 = 0;                                                   \
			m_at0C = 0;                                                   \
			m_at10 = 0;                                                   \
			reserve(100);                                                 \
		}                                                                 \
		~NAME();                                                          \
		void reserve(int count);                                          \
                                                                          \
		void * volatile m_at00;                                           \
		BfmeVecHolderVNH m_at04;                                          \
		void * volatile m_at08;                                          \
		void * volatile m_at0C;                                          \
		void * volatile m_at10;                                          \
	};

BFME_VNH_VECTOR( BfmeVecAVNH )
BFME_VNH_VECTOR( BfmeVecBVNH )
BFME_VNH_VECTOR( BfmeVecCVNH )
BFME_VNH_VECTOR( BfmeVecDVNH )
BFME_VNH_VECTOR( BfmeVecEVNH )
BFME_VNH_VECTOR( BfmeVecFVNH )
BFME_VNH_VECTOR( BfmeVecGVNH )

class BfmeSlotVNH
{
public:
	BfmeSlotVNH();                                             ///< pinned 0x0004A5DE
	~BfmeSlotVNH();                                            ///< pinned 0x00018246

private:
	unsigned int m_words[5];
};

extern "C" __declspec(dllimport) int __cdecl bfmeNowVNH() throw();

struct Rva00579160Manager;
extern Rva00579160Manager *Rva00579160TheManager;

struct Rva00579160Manager : public SubsystemInterface
{
public:
	Rva00579160Manager();

	BfmeVecAVNH m_at08;
	BfmeVecBVNH m_at1C;
	BfmeVecCVNH m_at30;
	BfmeVecDVNH m_at44;
	BfmeVecEVNH m_at58;
	BfmeVecFVNH m_at6C;
	BfmeVecAVNH m_at80;
	BfmeVecGVNH m_at94;
	BfmeSlotVNH m_atA8[12];
	unsigned int m_at198;
	unsigned int m_at19C;
	unsigned int m_at1A0;
	unsigned int m_at1A4;
	unsigned int m_at1A8;
	unsigned char m_at1AC;
	unsigned char m_at1AD;
	unsigned char m_at1AE;
	unsigned int m_at1B0;
	unsigned int m_at1B4;
	unsigned int m_at1B8;
	unsigned int m_at1BC;
	unsigned int m_at1C0;
	unsigned char m_at1C4;
};

Rva00579160Manager::Rva00579160Manager()
	: m_at198(0)
	, m_at19C(0)
	, m_at1A0(0)
{
	m_at1A8 = bfmeNowVNH();

	m_at1AC = 0;
	m_at1AD = 0;
	m_at1AE = 0;
	m_at1B0 = 0;
	m_at1B4 = 0;
	m_at1B8 = 0;
	m_at1BC = 0;
	m_at1C0 = 0xFFFFFFFF;
	m_at1C4 = 0;

	if (Rva00579160TheManager == 0)
		Rva00579160TheManager = this;
}
