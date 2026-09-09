// cl: /DNDEBUG /MD /EHsc

// The destructor at retail 0x0060EBB0 tears down the same 0x188-byte cloud/sky
// settings record its constructor at 0x0060E8A0 builds (BfmeConv2153.cpp).
// Twenty-nine destructible members unwind in reverse declaration order: twenty
// six AsciiStrings released through 0x00887940 and the three ThingRef handles
// at +0xE4/+0xE8/+0xEC released inline through InterlockedDecrement.
//
// The constructor's twenty-two EH states stop at the "bordercloud" string at
// +0x11C because nothing after it can throw, which is why it models +0x120,
// +0x15C, +0x160 and +0x17C..+0x184 as zeroed words. This body's twenty-eight
// states prove they are strings: their releaseBuffer calls are here.

extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long volatile *lpAddend);

class AsciiString
{
public:
	~AsciiString();												///< pinned 0x00887940

	char *m_data;
};

class BfmeThingEQ
{
public:
	virtual ~BfmeThingEQ();

	void Release_Ref(void)
	{
		if (InterlockedDecrement(&m_refCount) <= 0)
			delete this;
	}

	long m_refCount;
};

class BfmeThingRefEQ
{
public:
	~BfmeThingRefEQ()
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}

	BfmeThingEQ *m_ptr;
};

class BfmeCloudSetEQ
{
public:
	~BfmeCloudSetEQ();

	AsciiString m_s000;
	unsigned int m_at004;
	unsigned int m_at008;
	unsigned int m_at00C;
	unsigned int m_at010;
	unsigned int m_at014;
	unsigned int m_at018;
	unsigned int m_at01C;
	AsciiString m_s020;
	unsigned int m_at024[18];		// +0x024..+0x068
	AsciiString m_s06C;
	AsciiString m_s070;
	AsciiString m_s074;
	AsciiString m_s078;
	AsciiString m_s07C;
	AsciiString m_s080;
	AsciiString m_s084;
	AsciiString m_s088;
	AsciiString m_s08C;
	AsciiString m_s090;
	AsciiString m_s094;
	AsciiString m_s098;
	unsigned int m_at09C[6];		// +0x09C..+0x0B0
	AsciiString m_s0B4;
	AsciiString m_s0B8;
	unsigned int m_at0BC[10];		// +0x0BC..+0x0E0
	BfmeThingRefEQ m_r0E4;
	BfmeThingRefEQ m_r0E8;
	BfmeThingRefEQ m_r0EC;
	AsciiString m_s0F0;
	AsciiString m_s0F4;
	unsigned int m_at0F8[8];		// +0x0F8..+0x114
	AsciiString m_s118;
	AsciiString m_s11C;
	AsciiString m_s120;
	unsigned int m_at124[14];		// +0x124..+0x158
	AsciiString m_s15C;
	AsciiString m_s160;
	unsigned int m_at164[6];		// +0x164..+0x178
	AsciiString m_s17C;
	AsciiString m_s180;
	AsciiString m_s184;
};

// ??1BfmeCloudSetEQ@@QAE@XZ
BfmeCloudSetEQ::~BfmeCloudSetEQ()
{
}
