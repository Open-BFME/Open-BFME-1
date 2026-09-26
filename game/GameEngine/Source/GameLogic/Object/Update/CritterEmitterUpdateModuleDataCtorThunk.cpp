// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME5: CritterEmitterUpdate module-data constructor. The matched
// friend_newModuleData factory allocates this class, while the independently
// matched destructor fixes the owned strings and vectors at +A4 through +C0.

#include <string.h>
#include <bitset>
#include <vector>

class CritterEmitterUpdateModuleDataInner
{
public:
	CritterEmitterUpdateModuleDataInner();
	~CritterEmitterUpdateModuleDataInner();
private:
	unsigned char m_storage[0x68];
};

class CritterEmitterMask
{
public:
	CritterEmitterMask() {}
	void clear() { m_bits.reset(); }
	void flip() { m_bits.flip(); }
private:
	std::bitset<181> m_bits;
};

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString() : m_data(0) {}
	~BFMERetailAsciiString();
	void releaseBuffer();
private:
	char *m_data;
};

class UnicodeString
{
public:
	UnicodeString() : m_data(0) {}
	~UnicodeString();
	void set(const UnicodeString &other);
private:
	wchar_t *m_data;
};

extern const UnicodeString TheEmptyUnicodeString;

struct CritterEmitterPair { unsigned int m_words[2]; };

class __declspec(novtable) CritterEmitterUpdateModuleDataBase
{
public:
	virtual ~CritterEmitterUpdateModuleDataBase();
protected:
	void *m_unknown04;
	CritterEmitterUpdateModuleDataInner m_inner; // +08
};

class CritterEmitterUpdateModuleData
	: public CritterEmitterUpdateModuleDataBase
{
public:
	CritterEmitterUpdateModuleData();
	virtual ~CritterEmitterUpdateModuleData();
private:
	unsigned int m_value70;
	CritterEmitterMask m_allKinds;
	CritterEmitterMask m_excludedKinds;
	BFMERetailAsciiString m_name;
	_STL::vector<CritterEmitterPair> m_pairs;
	_STL::vector<_STL::vector<int> > m_nested;
	UnicodeString m_displayName;
	unsigned char m_flagC4;
	unsigned char m_flagC5;
	unsigned char m_padC6[2];
	int m_valueC8;
	unsigned int m_valueCC;
	unsigned int m_valueD0;
	unsigned int m_valueD4;
	float m_distance;
	unsigned int m_valueDC;
};

// ??0CritterEmitterUpdateModuleData@@QAE@XZ
CritterEmitterUpdateModuleData::CritterEmitterUpdateModuleData()
	: m_value70(0),
	  m_displayName(),
	  m_flagC4(0),
	  m_flagC5(0),
	  m_valueC8(-1),
	  m_distance(5.0f),
	  m_valueDC(0)
{
	m_displayName.set(TheEmptyUnicodeString);
	m_name.releaseBuffer();
	m_pairs.clear();
	m_allKinds.clear();
	m_allKinds.flip();
	m_excludedKinds.clear();
	m_valueCC = 0;
	m_valueD0 = 0;
	m_valueD4 = 0;
}
