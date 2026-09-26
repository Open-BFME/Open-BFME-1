// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// ?rva0049B9B0@CommandButton@@QBE?AV?$BitFlags@$0MA@@@XZ
// Retail 0x0049B9B0, 160 bytes. Owner CommandButton: the retail CommandButton
// FieldParse table at 0x00CFA3B8 puts the INI key "BuildUpgrades" at +0x28, and
// the CommandButton constructor at 0x0049BBF0 zeroes that vector's three words at
// +0x28/+0x2C/+0x30. The body resolves each name through
// UpgradeCenter::findUpgrade (0x0010B0E0) and sets the template's +0x20 bit in a
// 192-bit UpgradeMaskType returned by value (retail keeps the hidden return
// pointer in EAX). No caller or vtable names the method, so it stays
// address-derived; the only caller is Rva004BC8A0.

#include <bitset>

#include "ascii_string.h"

typedef unsigned int UnsignedInt;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
template <unsigned int NUMBITS>
class BitFlags
{
public:
	void set(UnsignedInt bit)
	{
		reinterpret_cast<UnsignedInt *>(&m_bits)[bit >> 5] |= 1 << (bit & 31);
	}

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<192> UpgradeMaskType;

class UpgradeTemplate
{
public:
	unsigned char m_unmodelled00[0x20];
	UnsignedInt m_value20;	// bit index into UpgradeMaskType
};

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};

extern UpgradeCenter *TheUpgradeCenter;

class CommandButton
{
public:
	UpgradeMaskType rva0049B9B0() const;

private:
	unsigned char m_unmodelled00[0x28];
	AsciiString *m_buildUpgradesBegin;	// +0x28 INI "BuildUpgrades"
	AsciiString *m_buildUpgradesEnd;	// +0x2C
};

UpgradeMaskType CommandButton::rva0049B9B0() const
{
	UpgradeMaskType mask;
	for (const AsciiString *it = m_buildUpgradesBegin; it != m_buildUpgradesEnd; ++it)
	{
		const UpgradeTemplate *upgrade = TheUpgradeCenter->findUpgrade(*it);
		if (upgrade != 0)
			mask.set(upgrade->m_value20);
	}
	return mask;
}
