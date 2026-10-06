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
// cl: /O2 /Ob1 /DNDEBUG /MD /EHsc- /Igame/Libraries/Source/WWVegas/WWLib
// stlport

#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <vector>

#include "ascii_string.h"

// The header-inline StringBase<char>::compare; its COMDAT is retail 0x0005FEB0.
template <> inline int StringBase<char>::compare(const StringBase<char> &str) const
{
	int otherLength = str.m_data ? str.m_data->length : 0;
	const char *otherData = str.m_data ? str.m_data->data : (const char *)"";
	int length = m_data ? m_data->length : 0;
	const char *data = m_data ? m_data->data : (const char *)"";
	int result = memcmp(data, otherData, length < otherLength ? length : otherLength);
	return result ? result : length - otherLength;
}

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
		if (table->getName().StringBase<char>::compare(name) == 0)
			return table->getValues();
	}
	return m_defaultTableValues;
}
