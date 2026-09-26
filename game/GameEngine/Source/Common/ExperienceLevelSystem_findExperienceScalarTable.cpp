// ?findExperienceScalarTable@ExperienceLevelSystem@@QAEPAUBfmeVec@@ABVAsciiString@@@Z
// Retail 0x0037F5B0/218.  BfmeThingEFE's matched constructor names this
// lookup through ILT 0x00021797; the scalar-table vector and default pointer
// are established by the matched ExperienceLevelSystem destructor.
//
// The table record is the 0x18-byte ExperienceScalarTable from
// INI_ExperienceScalarTable.cpp.  Its first member is the 12-byte Real-vector
// prefix used by parseExperienceScalarTableScalars; the name is at +0x0c.
// ExperienceLevelSystem's vector begins at +0x20 and its default level is at
// +0x2c.  Keep the vendor STLport vector spelling here: the retail loop is
// the ordinary index/size form, without a separate empty-vector branch.
// cl: /O2 /Ob1 /DNDEBUG /MD /EHsc-
// stlport

extern "C" int __cdecl memcmp(const void *, const void *, unsigned int);
#pragma intrinsic(memcmp)

#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <vector>

class AsciiString
{
public:
	int compare(const AsciiString &other) const
	{
		int otherLength = other.m_data ?
			*(const unsigned short *)(other.m_data + 4) : 0;
		const char *otherText = other.m_data ? other.m_data + 8 : "";
		int thisLength = m_data ?
			*(const unsigned short *)(m_data + 4) : 0;
		const char *thisText = m_data ? m_data + 8 : "";
		int length = thisLength < otherLength ? thisLength : otherLength;
		int result = memcmp(thisText, otherText, length);
		if (result != 0)
			return result;
		return thisLength - otherLength;
	}

	bool operator==(const AsciiString &other) const
	{
		return compare(other) == 0;
	}

private:
	char *m_data;
};

struct BfmeVec
{
	float *start;
	float *end;
	float *endOfStorage;
};

class ExperienceScalarTable
{
public:
	BfmeVec *getValues()
	{
		return &m_values;
	}

	const AsciiString &getName() const
	{
		return m_name;
	}

private:
	BfmeVec m_values;
	AsciiString m_name;
};

class ExperienceLevelSystem
{
public:
	BfmeVec *findExperienceScalarTable(const AsciiString &name);

private:
	unsigned char m_unmodelled_00[0x20];
	std::vector<ExperienceScalarTable *> m_scalarTables;
	BfmeVec *m_defaultTableValues;
};

BfmeVec *ExperienceLevelSystem::findExperienceScalarTable(
	const AsciiString &name)
{
	for (int index = 0; index < m_scalarTables.size(); ++index)
	{
		ExperienceScalarTable *table = m_scalarTables[index];
		if (table->getName() == name)
			return table->getValues();
	}
	return m_defaultTableValues;
}
