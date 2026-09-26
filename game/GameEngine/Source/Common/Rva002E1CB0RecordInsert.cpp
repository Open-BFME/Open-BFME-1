// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#include "ascii_string.h"
#include <vector>

struct Gen_t_002e19c0_p12cd
{
	int m_key;
	AsciiString m_text;
	unsigned char m_state;
};

class Rva002E1CB0Records
{
public:
	void insert(const Gen_t_002e19c0_p12cd &entry);

	char m_pad00[4];
	unsigned char m_changed;
	char m_pad05[3];
	_STL::vector<Gen_t_002e19c0_p12cd> m_records;
};

void Rva002E1CB0Records::insert(const Gen_t_002e19c0_p12cd &entry)
{
	for (unsigned int i = 0; i < m_records.size(); ++i)
	{
		if (m_records[i].m_key == entry.m_key)
		{
			((StringBase<char> *)&m_records[i].m_text)->set(
				*(const StringBase<char> *)&entry.m_text);
			return;
		}
	}
	m_records.push_back(entry);
	m_changed = 0;
}
