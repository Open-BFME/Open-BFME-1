// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
// The 0x00268120 body is an ICF-shared SpecialPower module-data constructor.
// The Rider factory at 0x001195C0 allocates 0x210 bytes and calls this body.
// The vtable at 0x010B7858 and the destructor at 0x00268A00 identify the Rider
// ledger row and confirm the four named slots, string, and filter members.
#include <bitset>

class AsciiString
{
public:
	char *m_data;
};

extern AsciiString TheBfmeCrateNameDefault;
extern const char g_Rva0107301CEmptyString[];

class BfmeNamedSlot
{
public:
	BfmeNamedSlot(const AsciiString &, int);
	~BfmeNamedSlot();

private:
	char m_body[0x70];
};

class RetailLayoutString
{
public:
	RetailLayoutString() : m_data(0) {}
	~RetailLayoutString() { releaseBuffer(); }
	void set(const char *, int);

private:
	void releaseBuffer();
	char *m_data;
};

class KindOfMask
{
	std::bitset<181> bits;
	KindOfMask() {}
	explicit KindOfMask(unsigned int bit)
		: bits(static_cast<unsigned long>(1u << bit)) {}
};

extern const KindOfMask KINDOFMASK_NONE;

class RiderChangeContainModuleDataBase
{
public:
	virtual ~RiderChangeContainModuleDataBase() {}

protected:
	unsigned char m_pad04[4];
	unsigned int m_word08;
	unsigned char m_byte0c;
	unsigned char m_byte0d;
	unsigned char m_pad0e[2];
};

class RS_Member
{
public:
	RS_Member();
	~RS_Member();

private:
	unsigned int m_handle;
};

class EmotionTrackerUpdateName : public RS_Member
{
public:
	void setPolicies(KindOfMask, KindOfMask);
};

class RiderChangeContainModuleData : public RiderChangeContainModuleDataBase
{
public:
	RiderChangeContainModuleData();
	virtual ~RiderChangeContainModuleData();
	virtual void slot();

private:
	BfmeNamedSlot m_audio0;
	BfmeNamedSlot m_audio1;
	BfmeNamedSlot m_audio2;
	BfmeNamedSlot m_audio3;
	RetailLayoutString m_exitBone;
	unsigned int m_word1d4;
	unsigned char m_byte1d8;
	unsigned char m_pad1d9[3];
	EmotionTrackerUpdateName m_filter;
	unsigned int m_word1e0;
	unsigned char m_byte1e4;
	unsigned char m_pad1e5[3];
	unsigned int m_word1e8;
	unsigned char m_byte1ec;
	unsigned char m_byte1ed;
	unsigned char m_byte1ee;
	unsigned char m_pad1ef;
	unsigned int m_word1f0;
	unsigned int m_word1f4;
	unsigned int m_word1f8;
	unsigned int m_word1fc;
	float m_real200;
	unsigned int m_word204;
	unsigned char m_byte208;
	unsigned char m_byte209;
	unsigned char m_byte20a;
	unsigned char m_byte20b;
	unsigned char m_byte20c;
	unsigned char m_byte20d;
};

RiderChangeContainModuleData::RiderChangeContainModuleData()
	: m_audio0(TheBfmeCrateNameDefault, 0)
	, m_audio1(TheBfmeCrateNameDefault, 0)
	, m_audio2(TheBfmeCrateNameDefault, 0)
	, m_audio3(TheBfmeCrateNameDefault, 0)
{
	m_word08 = 0;
	m_byte0c = 0;
	m_byte0d = 0;
	m_exitBone.set(g_Rva0107301CEmptyString, 0);
	m_word1d4 = 0;
	m_byte1d8 = 0;
	m_filter.setPolicies(KINDOFMASK_NONE, KINDOFMASK_NONE);
	m_word1e0 = 0;
	m_byte1e4 = 0;
	m_word1e8 = 0;
	m_byte1ec = 0;
	m_byte1ed = 0;
	m_word1f0 = 0;
	m_word1f4 = 0;
	m_word1f8 = 0;
	m_byte1ee = 0;
	m_word204 = 0;
	m_byte208 = 0;
	m_byte209 = 0;
	m_byte20a = 0;
	m_byte20b = 0;
	m_word1fc = 0xffffffff;
	m_real200 = 1.0f;
	m_byte20c = 1;
	m_byte20d = 1;
}
