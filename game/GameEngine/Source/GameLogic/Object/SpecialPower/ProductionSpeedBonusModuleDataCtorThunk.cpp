// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Open-BFME5: ProductionSpeedBonus module-data constructor.
//
// The named friend_newModuleData factory at retail 0x00120120 allocates 0x224
// bytes and calls this constructor.  The final twelve bytes are an STLport
// vector<AsciiString>; the matched destructor confirms that it is destroyed
// before the common SpecialPower module-data base.

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

class ProductionSpeedBonusRange
{
public:
	void erase( void *first, void *last );

	void *volatile m_begin;
	void *volatile m_end;
	void *m_capacity;
};

class ProductionSpeedBonusModuleData : public BfmeSpecialPowerModuleDataBase
{
public:
	ProductionSpeedBonusModuleData();
	virtual ~ProductionSpeedBonusModuleData();

private:
	unsigned int m_bonusPercent;               // +0x210
	unsigned int m_duration;                   // +0x214
	_STL::vector<AsciiString> m_upgradeTypes;  // +0x218
};

// ??0ProductionSpeedBonusModuleData@@QAE@XZ
ProductionSpeedBonusModuleData::ProductionSpeedBonusModuleData()
{
	m_bonusPercent = 0;
	m_duration = 0;
	ProductionSpeedBonusRange *range =
		reinterpret_cast<ProductionSpeedBonusRange *>( &m_upgradeTypes );
	void *last = range->m_end;
	void *first = range->m_begin;
	range->erase( first, last );
}
