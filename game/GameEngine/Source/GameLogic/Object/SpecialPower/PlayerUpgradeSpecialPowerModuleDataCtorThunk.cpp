// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Open-BFME5: PlayerUpgradeSpecialPower module-data constructor.
//
// The named friend_newModuleData factory at retail 0x00121370 allocates 0x21C
// bytes and calls this constructor.  The final twelve bytes are an STLport
// vector<AsciiString>: its destructor at 0x000658A0 walks four-byte strings
// from begin to end and frees the begin/capacity allocation afterward.

#include <vector>

#include "ascii_string.h"

class BfmeSpecialPowerModuleDataBase
{
public:
	BfmeSpecialPowerModuleDataBase();
	virtual ~BfmeSpecialPowerModuleDataBase();

private:
	unsigned char m_unmodelled_04[ 0x210 - 4 ];
};

class PlayerUpgradeRange
{
public:
	void erase( void *first, void *last );

	void *volatile m_begin;
	void *volatile m_end;
	void *m_capacity;
};

class PlayerUpgradeSpecialPowerModuleData : public BfmeSpecialPowerModuleDataBase
{
public:
	PlayerUpgradeSpecialPowerModuleData();
	virtual ~PlayerUpgradeSpecialPowerModuleData();

private:
	_STL::vector<AsciiString> m_upgrades; // +0x210
};

// ??0PlayerUpgradeSpecialPowerModuleData@@QAE@XZ
PlayerUpgradeSpecialPowerModuleData::PlayerUpgradeSpecialPowerModuleData()
{
	PlayerUpgradeRange *range =
		reinterpret_cast<PlayerUpgradeRange *>( &m_upgrades );
	void *last = range->m_end;
	void *first = range->m_begin;
	range->erase( first, last );
}
