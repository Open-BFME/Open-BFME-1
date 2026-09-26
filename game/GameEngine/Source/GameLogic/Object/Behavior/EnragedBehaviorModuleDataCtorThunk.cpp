// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Open-BFME5: EnragedBehavior module-data constructor.
//
// The named friend_newModuleData factory at retail 0x00114A40 allocates 0x2C
// bytes and calls this constructor.  The matched destructor confirms that the
// twelve-byte member at +0x08 is destroyed before the common module-data base.

#include <vector>

#include "ascii_string.h"

class EnragedBehaviorModuleDataBase
{
public:
	virtual ~EnragedBehaviorModuleDataBase() {}

private:
	unsigned int m_unmodelled_04;
};

class EnragedBehaviorRange
{
public:
	void erase( void *first, void *last );

	void *volatile m_begin;
	void *volatile m_end;
	void *m_capacity;
};

struct Rva006C9270GlobalData
{
	unsigned char m_unmodelled[ 0x1A0 ];
	unsigned int m_defaultEnragedDuration;
};

extern Rva006C9270GlobalData *TheWritableGlobalData;

class EnragedBehaviorModuleData : public EnragedBehaviorModuleDataBase
{
public:
	EnragedBehaviorModuleData();
	virtual ~EnragedBehaviorModuleData();

private:
	_STL::vector<AsciiString> m_requiredUpgrades; // +0x08
	unsigned int m_duration;                     // +0x14
	unsigned int m_unmodelled_18;
	unsigned int m_unmodelled_1C;
	unsigned int m_unmodelled_20;
	unsigned int m_unmodelled_24;
	unsigned int m_unmodelled_28;
};

// ??0EnragedBehaviorModuleData@@QAE@XZ
EnragedBehaviorModuleData::EnragedBehaviorModuleData()
{
	m_duration = TheWritableGlobalData->m_defaultEnragedDuration;
	m_unmodelled_18 = 0;
	m_unmodelled_1C = 0;
	m_unmodelled_20 = 0;
	m_unmodelled_24 = 0;
	m_unmodelled_28 = 0;

	EnragedBehaviorRange *range =
		reinterpret_cast<EnragedBehaviorRange *>( &m_requiredUpgrades );
	void *last = range->m_end;
	void *first = range->m_begin;
	range->erase( first, last );
}
