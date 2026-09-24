// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib

// Glo012F1024Item::j_00010712, retail 0x003AE650, 243 bytes, called from
// Glo012F1024Item::bfmeEnter (0x0000BC5D) as its seventh step.
//
// The vector at +0x60 holds the 0x24-byte region reinforcement records that
// ParseRegionReinforcementBlock (0x003BABE0) builds and Rva003BABE0Owner::append
// (0x003B25D0) stores at the same +0x60.  After the call at 0x003BCA30 on the
// global at 0x012F1028, each record's fields are handed to that global's
// forwarder at 0x003BCA50, which passes the same 0x20 bytes of arguments on to
// LivingWorldRegionManager::rva003C8C60 when its +0x28 manager exists.
//
// Retail evaluates the region-name call first and spills the three flags to
// frame temporaries before any push, with the far time held in ECX: every
// argument but the reinforcement list is an inline accessor call, which the
// compiler hoists ahead of the plain operand.

#include "ascii_string.h"

class Rva0076F980Mid
{
public:
	AsciiString *m_start;
	AsciiString *m_finish;
	AsciiString *m_end;
};

class Rva003BABE0Record
{
public:
	virtual ~Rva003BABE0Record();

	AsciiString getRegionName();
	unsigned int getCloseDistanceTime() const { return m_closeDistanceTime; }
	unsigned int getMediumDistanceTime() const { return m_mediumDistanceTime; }
	unsigned int getFarDistanceTime() const { return m_farDistanceTime; }
	bool getPathFindRuleAllRegions() const { return m_pathFindRuleAllRegions; }
	bool getPathFindRulePlayerOwned() const { return m_pathFindRulePlayerOwned; }
	bool getAutoSummon() const { return m_autoSummon; }

	AsciiString m_regionName;
	Rva0076F980Mid m_addReinforcementArmy;
	unsigned int m_closeDistanceTime;
	unsigned int m_mediumDistanceTime;
	unsigned int m_farDistanceTime;
	bool m_pathFindRuleAllRegions;
	bool m_pathFindRulePlayerOwned;
	bool m_autoSummon;
};

typedef char Rva003BABE0RecordSizeMustBe24[
	sizeof( Rva003BABE0Record ) == 0x24 ? 1 : -1];

class BfmeElem36Vector
{
public:
	unsigned int bfmeSize(void) const { return m_bfmeEnd - m_bfmeBegin; }
	Rva003BABE0Record *bfmeBegin(void) const { return m_bfmeBegin; }

	Rva003BABE0Record *m_bfmeBegin;
	Rva003BABE0Record *m_bfmeEnd;
	Rva003BABE0Record *m_bfmeCapacity;
};

class Glo012F1024Item
{
public:
	void j_00010712(void);

	char m_bfmeHead[0x60];
	BfmeElem36Vector m_bfmeRecords;				// +0x60
};

class Glo012F1028Type;

extern Glo012F1028Type *Glo012F1028;				// 0x012F1028

class Rva003BCA30
{
public:
	void run(void);
};

class Rva003BCA50
{
public:
	void forward(const AsciiString &regionName,
		const Rva0076F980Mid &addReinforcementArmy,
		unsigned int closeDistanceTime,
		unsigned int mediumDistanceTime,
		unsigned int farDistanceTime,
		unsigned char pathFindRuleAllRegions,
		unsigned char pathFindRulePlayerOwned,
		unsigned char autoSummon);
};

// ?j_00010712@Glo012F1024Item@@QAEXXZ
void Glo012F1024Item::j_00010712(void)
{
	((Rva003BCA30 *)Glo012F1028)->run();

	for (unsigned int index = 0; index < m_bfmeRecords.bfmeSize(); ++index)
	{
		Rva003BABE0Record *records = m_bfmeRecords.bfmeBegin();
		Rva003BABE0Record *record = records + index;

		((Rva003BCA50 *)Glo012F1028)->forward(record->getRegionName(),
			record->m_addReinforcementArmy,
			record->getCloseDistanceTime(),
			record->getMediumDistanceTime(),
			record->getFarDistanceTime(),
			record->getPathFindRuleAllRegions(),
			record->getPathFindRulePlayerOwned(),
			record->getAutoSummon());
	}
}
