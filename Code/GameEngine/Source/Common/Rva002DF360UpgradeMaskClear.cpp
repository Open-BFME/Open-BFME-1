// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// stlport

#include "ascii_string.h"
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

class UnicodeString
{
public:
	void set(const UnicodeString &source);
};

class UpgradeTemplate
{
public:
	unsigned int getUpgradeMask(void) const { return m_upgradeMask; }

private:
	unsigned char m_padding00[0x20];
	unsigned int m_upgradeMask;
};

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};

extern UpgradeCenter *TheUpgradeCenter;

class BFMERetailAsciiString : public AsciiString
{
public:
	~BFMERetailAsciiString();
};

class Rva002DF360
{
public:
	void clear(void);

private:
	unsigned int m_padding00;
	unsigned int m_firstMask[6];
	unsigned int m_secondMask[6];
	unsigned int m_padding34;
	_STL::vector<BFMERetailAsciiString> m_firstNames;
	_STL::vector<BFMERetailAsciiString> m_secondNames;
};

void Rva002DF360::clear(void)
{
	_STL::vector<BFMERetailAsciiString>::const_iterator first;
	for (first = m_firstNames.begin(); first != m_firstNames.end(); ++first)
	{
		const UpgradeTemplate *upgrade = TheUpgradeCenter->findUpgrade(
			*(const AsciiString *)first);
		if (upgrade != 0)
		{
			unsigned int mask = upgrade->getUpgradeMask();
			m_firstMask[mask >> 5] |= 1u << (mask & 0x1f);
		}
	}

	_STL::vector<BFMERetailAsciiString>::const_iterator second;
	for (second = m_secondNames.begin(); second != m_secondNames.end(); ++second)
	{
		const UpgradeTemplate *upgrade = TheUpgradeCenter->findUpgrade(
			*(const AsciiString *)second);
		if (upgrade != 0)
		{
			unsigned int mask = upgrade->getUpgradeMask();
			m_secondMask[mask >> 5] |= 1u << (mask & 0x1f);
		}
	}

	m_firstNames.clear();
	m_secondNames.clear();
}
