// ?rva00246490@Rva00246490HordeContainInterface@@QAEXPAVObject@@@Z
// partial score=0.86 date=2026-09-22
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWMath
// stlport
// Retail 0x00246490: HordeContain +0xE4 interface vtable 0x010AED58 slot 91
// (ILT 0x00033B81; the AODHordeContain table 0x010AE230 and 0x010B07E0 inherit
// it). The receiver is the +0xE4 subobject, so the UpdateModule base sits at
// this-0xE4. The module-data reads at 0x274..0x288 are the BackUp*/Cower*
// FieldParse entries of table 0x00CAF710; the random draws cite
// HordeContain.cpp lines 6845, 6850 and 6851. Method name unproven.
#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <list>
#include <map>
#include "coord.h"

Real GetGameLogicRandomValueReal(Real lo, Real hi, char *file, int line);
int GetGameLogicRandomValue(int lo, int hi, char *file, int line);

class Object
{
public:
	const Coord3D *getPosition() const { return &m_position; }
	int getID() const { return m_id; }
	bool testStatus98( unsigned bit ) const { return ( m_status98 & bit ) != 0; }

	char m_pad000[ 0x38 ];
	Coord3D m_position;							///< retail +0x38
	char m_pad044[ 0x74 - 0x44 ];
	int m_id;									///< retail +0x74
	char m_pad078[ 0x98 - 0x78 ];
	unsigned m_status98;						///< retail +0x98
};

// Offsets and INI keys from FieldParse table 0x00CAF710 (reverse/field_names.csv);
// the owning ModuleData class name is not settled, so the shim keeps the table address.
struct ModuleData00CAF710
{
	char m_pad000[ 0x274 ];
	int m_backUpMinDelayTime;					///< +0x274 BackUpMinDelayTime
	int m_backUpMaxDelayTime;					///< +0x278 BackUpMaxDelayTime
	Real m_backUpMinDistance;					///< +0x27C BackUpMinDistance
	Real m_backUpMaxDistance;					///< +0x280 BackUpMaxDistance
	Real m_backupPercentage;					///< +0x284 BackupPercentage
	Real m_cowerRadius;							///< +0x288 CowerRadius
};

enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1 };

class UpdateModule
{
	friend class Rva00246490HordeContainInterface;
protected:
	void setWakeFrame( Object *obj, UpdateSleepTime wakeDelay );
public:
	char m_pad000[ 4 ];
	const ModuleData00CAF710 *m_moduleData;	///< +0x04, read at the BackUp*/Cower* table offsets
	Object *m_object;							///< +0x08, handed to setWakeFrame
};

// key/value spellings of the landed operator[] at 0x002449E0 (Rva002449E0.cpp)
struct BfmeRva449E0Key
{
	int m_key;
};

struct BfmeRva449E0Value
{
	Coord3D m_backUpPosition;
	int m_backUpDelay;
};

namespace _STL
{
template <>
BfmeRva449E0Value &map<BfmeRva449E0Key, BfmeRva449E0Value>::operator[](
	const BfmeRva449E0Key &key );
}

class Rva00246490HordeContainInterface
{
public:
	void rva00246490( Object *obj );

	UpdateModule *updateModule() { return (UpdateModule *)( (char *)this - 0xe4 ); }
	_STL::list<Object *> &members() { return *(_STL::list<Object *> *)( (char *)this - 0xac ); }

	char m_pad000[ 0x60 ];
	_STL::map<BfmeRva449E0Key, BfmeRva449E0Value> m_backUp;		///< this+0x60
	char m_pad06c[ 0x124 - 0x6c ];
	int m_backUpFromID;												///< this+0x124
};

void Rva00246490HordeContainInterface::rva00246490( Object *obj )
{
	if ( !obj )
		return;

	Coord3D center;
	center.set( obj->getPosition() );
	const ModuleData00CAF710 *data = updateModule()->m_moduleData;
	if ( !data )
		return;

	bool always = updateModule()->m_object->testStatus98( 0x10 );
	for ( _STL::list<Object *>::iterator it = members().begin(); it != members().end(); ++it )
	{
		Object *member = *it;
		if ( !always && !( member->m_status98 & 0x10 ) && data->m_cowerRadius == 0.0f )
		{
			if ( GetGameLogicRandomValueReal( 0.0f, 1.0f, "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\HordeContain.cpp", 0x1abd ) > data->m_backupPercentage )
				continue;
		}
		{
			Real distance = GetGameLogicRandomValueReal( data->m_backUpMinDistance, data->m_backUpMaxDistance, "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\HordeContain.cpp", 0x1ac2 );
			int delay = GetGameLogicRandomValue( data->m_backUpMinDelayTime, data->m_backUpMaxDelayTime, "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\HordeContain.cpp", 0x1ac3 );
			BfmeRva449E0Key key;
			key.m_key = member->getID();
			BfmeRva449E0Value &entry = m_backUp[ key ];

			Coord3D dir;
			dir.set( member->getPosition() );
			dir.x -= center.x;
			dir.y -= center.y;
			dir.z -= center.z;
			dir.normalize();
			dir.scale( distance * 10.0f );

			Coord3D pos;
			pos.set( member->getPosition() );
			pos.add( &dir );
			entry.m_backUpDelay = delay;
			entry.m_backUpPosition = pos;
		}
	}

	m_backUpFromID = obj->getID();
	updateModule()->setWakeFrame( updateModule()->m_object, UPDATE_SLEEP_NONE );
}
