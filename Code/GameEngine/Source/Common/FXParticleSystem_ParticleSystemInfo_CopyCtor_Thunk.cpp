// cl: /DNDEBUG /MD /EHsc
// The vtable, field offsets, and three AsciiString copy calls match retail
// constructor 0x0005EF60.

class AsciiString;

class AsciiStringCopyCtorShim
{
public:
	void construct(const AsciiString *source);
};

class AsciiString
{
public:
	AsciiString(const AsciiString &source)
	{
		((AsciiStringCopyCtorShim *)this)->construct(&source);
	}
	~AsciiString();

private:
	char *m_data;
};

struct ThreeDwords
{
	unsigned int m_0;
	unsigned int m_4;
	unsigned int m_8;
};

class Snapshot
{
public:
	virtual ~Snapshot();
};

namespace FXParticleSystem
{

class ParticleSystemInfo : public Snapshot
{
public:
	ParticleSystemInfo(const ParticleSystemInfo &source);
	virtual ~ParticleSystemInfo();

private:
	unsigned char m_byte4;
	unsigned int m_dword8;
	unsigned int m_dwordC;
	AsciiString m_string10;
	ThreeDwords m_block14;
	unsigned int m_dword20;
	unsigned int m_dword24;
	ThreeDwords m_block28;
	ThreeDwords m_block34;
	unsigned int m_dword40;
	ThreeDwords m_block44;
	ThreeDwords m_block50;
	ThreeDwords m_block5C;
	AsciiString m_string68;
	unsigned int m_dword6C;
	unsigned int m_dword70;
	unsigned int m_dword74;
	AsciiString m_string78;
	unsigned int m_dword7C;
	unsigned char m_byte80;
	unsigned char m_byte81;
	unsigned char m_byte82;
	unsigned char m_byte83;
	unsigned int m_dword84;
	unsigned int m_dword88;
	unsigned int m_dword8C;
	unsigned int m_dword90;
	unsigned int m_dword94;
};

ParticleSystemInfo::ParticleSystemInfo(const ParticleSystemInfo &source)
	: m_byte4(source.m_byte4)
	, m_dword8(source.m_dword8)
	, m_dwordC(source.m_dwordC)
	, m_string10(source.m_string10)
	, m_block14(source.m_block14)
	, m_dword20(source.m_dword20)
	, m_dword24(source.m_dword24)
	, m_block28(source.m_block28)
	, m_block34(source.m_block34)
	, m_dword40(source.m_dword40)
	, m_block44(source.m_block44)
	, m_block50(source.m_block50)
	, m_block5C(source.m_block5C)
	, m_string68(source.m_string68)
	, m_dword6C(source.m_dword6C)
	, m_dword70(source.m_dword70)
	, m_dword74(source.m_dword74)
	, m_string78(source.m_string78)
	, m_dword7C(source.m_dword7C)
	, m_byte80(source.m_byte80)
	, m_byte81(source.m_byte81)
	, m_byte82(source.m_byte82)
	, m_byte83(source.m_byte83)
	, m_dword84(source.m_dword84)
	, m_dword88(source.m_dword88)
	, m_dword8C(source.m_dword8C)
	, m_dword90(source.m_dword90)
	, m_dword94(source.m_dword94)
{
}

}
