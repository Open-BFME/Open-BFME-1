// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport

#include "../../../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"
#include "../../../../../../Libraries/Source/WWVegas/WWLib/unicode_string.h"
#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include <string.h>
#include <vector>
#pragma intrinsic(memcpy)

struct Z1Elem0013BF00
{
	UnicodeString m_text;
	unsigned char m_byte4;
	unsigned int m_dword8;
	unsigned int m_dwordC;
	unsigned int m_dword10;
	unsigned int m_dword14;
	unsigned int m_dword18;
	unsigned int m_dword1C;
	unsigned char m_byte20;
	~Z1Elem0013BF00();
};

class Open2Elem771DF0
{
public:
	Open2Elem771DF0(const Open2Elem771DF0 &other);
	~Open2Elem771DF0();
	char m_storage[20];
};

class Rva0013B8F0RefCountView
{
public:
	virtual void deleteThroughSlot0(int freeIt);
	void addRef() { ++m_referenceCount; }
	void releaseRef()
	{
		--m_referenceCount;
		if (m_referenceCount <= 0)
			deleteThroughSlot0(1);
	}
	int m_referenceCount;
};

class Rva0013B8F0TargetView
{
public:
	char m_unknown00[0x24];
	Rva0013B8F0RefCountView m_refCount24;
};

class Rva0013B8F0ReferenceView
{
public:
	Rva0013B8F0ReferenceView(const Rva0013B8F0ReferenceView &other)
		: m_target(other.m_target)
	{
		if (m_target)
			m_target->m_refCount24.addRef();
	}
	Rva0013B8F0ReferenceView &operator=(const Rva0013B8F0ReferenceView &other)
	{
		if (this != &other)
		{
			if (other.m_target)
				other.m_target->m_refCount24.addRef();
			if (m_target)
				m_target->m_refCount24.releaseRef();
			m_target = other.m_target;
		}
		return *this;
	}
	Rva0013B8F0TargetView *m_target;
};

struct Rva0013B8F0Element
{
	int m_word00;
	int m_word04;
	int m_word08;
	AsciiString m_string0C;
	Rva0013B8F0ReferenceView m_reference10;
	~Rva0013B8F0Element();
};

struct Rva00772870Turret
{
	unsigned int m_word00;
	unsigned int m_word04;
	unsigned int m_word08;
	unsigned int m_word0C;
	unsigned int m_word10;
	unsigned int m_word14;
};

class ModelConditionInfo
{
public:
	ModelConditionInfo &operator=(const ModelConditionInfo &other);

private:
	char m_raw00[0x28];
	_STL::vector<AsciiString> m_vector28;
	AsciiString m_string34;
	unsigned char m_flag38;
	unsigned char m_pad39[3];
	AsciiString m_string3C;
	_STL::vector<AsciiString> m_vector40;
	AsciiString m_strings4C[4];
	AsciiString m_strings5C[4];
	AsciiString m_strings6C[4];
	AsciiString m_strings7C[4];
	AsciiString m_strings8C[4];
	_STL::list<Z1Elem0013BF00> m_list9C;
	_STL::vector<Open2Elem771DF0> m_vectorA0;
	_STL::vector<Rva0013B8F0Element> m_vectorAC;
	unsigned short m_wordB8;
	unsigned char m_padBA[2];
	AsciiString m_stringBC;
	unsigned int m_wordsC0[11];
	unsigned char m_bytesEC[4];
	Rva00772870Turret m_turrets[2];
	unsigned int m_pad120;
	unsigned char m_flag124;
	unsigned char m_pad125[3];
};

ModelConditionInfo &ModelConditionInfo::operator=(const ModelConditionInfo &other)
{
	if (this == &other)
		return *this;

	memcpy(this, &other, 0x28);

	m_string3C = other.m_string3C;
	m_string34 = other.m_string34;
	m_vector40 = other.m_vector40;
	m_list9C = other.m_list9C;
	m_vectorA0 = other.m_vectorA0;
	m_vectorAC = other.m_vectorAC;
	m_flag38 = other.m_flag38;

	for (unsigned int i = 0; i < 4; ++i)
	{
		m_strings4C[i] = other.m_strings4C[i];
		m_strings5C[i] = other.m_strings5C[i];
		m_strings6C[i] = other.m_strings6C[i];
		m_strings7C[i] = other.m_strings7C[i];
		m_strings8C[i] = other.m_strings8C[i];
	}

	for (unsigned int turretSlot = 0; turretSlot < 2; ++turretSlot)
	{
		m_turrets[turretSlot].m_word00 = other.m_turrets[turretSlot].m_word00;
		m_turrets[turretSlot].m_word04 = other.m_turrets[turretSlot].m_word04;
		m_turrets[turretSlot].m_word08 = other.m_turrets[turretSlot].m_word08;
		m_turrets[turretSlot].m_word0C = other.m_turrets[turretSlot].m_word0C;
		m_turrets[turretSlot].m_word10 = other.m_turrets[turretSlot].m_word10;
		m_turrets[turretSlot].m_word14 = other.m_turrets[turretSlot].m_word14;
	}
	m_flag124 = other.m_flag124;

	m_vector28.clear();
	int sourceBytes = (const char *)other.m_vector28.end() -
		(const char *)other.m_vector28.begin();
	int itemIndex = 0;
	if ((sourceBytes & ~3) <= 0)
		goto vectorCopied;
	do
	{
		m_vector28.push_back(other.m_vector28.begin()[itemIndex]);
		++itemIndex;
	}
	while (itemIndex < (int)other.m_vector28.size());

vectorCopied:
	m_stringBC = other.m_stringBC;
	m_wordB8 = other.m_wordB8;

	m_wordsC0[0] = other.m_wordsC0[0];
	m_wordsC0[1] = other.m_wordsC0[1];
	m_wordsC0[2] = other.m_wordsC0[2];
	m_wordsC0[3] = other.m_wordsC0[3];
	m_wordsC0[4] = other.m_wordsC0[4];
	m_wordsC0[5] = other.m_wordsC0[5];
	m_wordsC0[6] = other.m_wordsC0[6];
	m_wordsC0[7] = other.m_wordsC0[7];
	m_wordsC0[8] = other.m_wordsC0[8];
	m_wordsC0[9] = other.m_wordsC0[9];
	m_wordsC0[10] = other.m_wordsC0[10];
	m_bytesEC[0] = other.m_bytesEC[0];
	m_bytesEC[1] = other.m_bytesEC[1];
	m_bytesEC[2] = other.m_bytesEC[2];

	return *this;
}
