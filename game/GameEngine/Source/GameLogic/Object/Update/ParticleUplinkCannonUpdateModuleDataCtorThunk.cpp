// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME5: ParticleUplinkCannonUpdate module-data constructor.
// The unique factory constructor/destructor chain fixes this identity. The
// matched 0x002A26C0 destructor fixes members at +08/+A0/+AC/+B0.

#include <map>
#include <string.h>

class ParticleUplinkCannonUpdateModuleDataMemberA
{
public:
	ParticleUplinkCannonUpdateModuleDataMemberA();
	~ParticleUplinkCannonUpdateModuleDataMemberA();
private:
	unsigned int m_value;
};

struct ParticleUplinkTenWordsA
{
	ParticleUplinkTenWordsA()
	{
		memset(m_words, 0, sizeof(m_words));
	}
	unsigned int m_words[10];
};

struct ParticleUplinkTenWordsB
{
	ParticleUplinkTenWordsB()
	{
		memset(m_words, 0, sizeof(m_words));
	}
	unsigned int m_words[10];
};

struct ParticleUplinkTenWordsC
{
	ParticleUplinkTenWordsC()
	{
		memset(m_words, 0, sizeof(m_words));
	}
	unsigned int m_words[10];
};

struct ParticleUplinkMapValue { unsigned int m_words[4]; };

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString() : m_data(0) {}
	~BFMERetailAsciiString();
private:
	char *m_data;
};

class __declspec(novtable) ParticleUplinkCannonUpdateModuleDataBase
{
public:
	virtual ~ParticleUplinkCannonUpdateModuleDataBase();
protected:
	unsigned int m_moduleData;
};

class ParticleUplinkCannonUpdateModuleData
	: public ParticleUplinkCannonUpdateModuleDataBase
{
public:
	ParticleUplinkCannonUpdateModuleData();
	virtual ~ParticleUplinkCannonUpdateModuleData();
private:
	ParticleUplinkCannonUpdateModuleDataMemberA m_handle;
	ParticleUplinkTenWordsA m_values0C;
	ParticleUplinkTenWordsB m_values34;
	ParticleUplinkTenWordsC m_values5C;
	unsigned int m_values84[6];
	unsigned char m_flag9C;
	unsigned char m_pad9D[3];
	std::map<unsigned int, ParticleUplinkMapValue> m_ownedValues;
	BFMERetailAsciiString m_nameAC;
	BFMERetailAsciiString m_nameB0;
};

// ??0ParticleUplinkCannonUpdateModuleData@@QAE@XZ
ParticleUplinkCannonUpdateModuleData::ParticleUplinkCannonUpdateModuleData()
{
	m_values84[0] = 0;
	m_values84[1] = 0;
	m_values84[2] = 0;
	m_values84[3] = 0;
	m_values84[4] = 0;
	m_values84[5] = 0;
	m_flag9C = 0;
}
