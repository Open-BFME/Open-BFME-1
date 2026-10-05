// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// stlport
// Two masked table reads and a search that clears the matching entry.

#include "Common/BitFlags.h"
extern "C" const char *__identifier("?s_bitNameList@?$BitFlags@$0HE@@@0PAPBDA")[];

class Gen_001C6300
{
public:
	int bfmeLookup(unsigned int index) const;

private:
	unsigned int m_bfmeWords[8];				// +0x00
};

// ?bfmeLookup@Gen_001C6300@@QBEHI@Z
int Gen_001C6300::bfmeLookup(unsigned int index) const
{
	if (m_bfmeWords[index >> 5] & (1 << (index & 31)))
		return (int)BitFlags<86>::getBitNames()[index];

	return 0;
}

class Gen_001C6390
{
public:
	int bfmeLookup(unsigned int index) const;

private:
	unsigned int m_bfmeWords[8];				// +0x00
};

// ?bfmeLookup@Gen_001C6390@@QBEHI@Z
int Gen_001C6390::bfmeLookup(unsigned int index) const
{
	if (m_bfmeWords[index >> 5] & (1 << (index & 31)))
		return reinterpret_cast<int>(__identifier("?s_bitNameList@?$BitFlags@$0HE@@@0PAPBDA")[index]);

	return 0;
}

class BfmePairEN
{
public:
	int m_bfmeTag;						// +0x00
	void *m_bfmeKey;					// +0x04
};

class Gen_00339940
{
public:
	void bfmeForget(void *key);

private:
	char m_bfmeHead[0x1709C];				// +0x00000
	BfmePairEN *m_bfmeStart;				// +0x1709C
	BfmePairEN *m_bfmeFinish;				// +0x170A0
};

// ?bfmeForget@Gen_00339940@@QAEXPAX@Z
void Gen_00339940::bfmeForget(void *key)
{
	BfmePairEN *entry = m_bfmeStart;
	BfmePairEN *finish = m_bfmeFinish;

	while (entry != finish)
	{
		if (key == entry->m_bfmeKey)
		{
			entry->m_bfmeKey = 0;

			return;
		}

		++entry;
	}
}
