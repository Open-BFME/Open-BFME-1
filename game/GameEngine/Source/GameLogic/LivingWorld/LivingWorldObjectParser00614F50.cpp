// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/iniexception /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#define _STLP_NO_EXCEPTIONS 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <map>

#include "Common/INIException.h"
#include "Common/NameKeyGenerator.h"

// LivingWorldObject registry callback: docs/ini_schema.md identifies614F50.
// FieldParse atVA01116D18 proves ObjectType+0xC, DefaultFlashValue+0x10,
// and FlashVariation+0x14. Constructor00618630 proves24B and the override
// link/flag at+4/+8. Keep the existing neutral BfmeLivingWorldMapObject type.
// See docs/living_world_parser_boundary.md for old-claim retirement evidence.
// The one-level inline override lookup is intentional: retail passes its
// returned pointer in EAX on both branches before invoking clone0060F620.
class Overridable
{
public:
	virtual ~Overridable();
	Overridable *friend_getFinalOverride();
	Overridable *finalOverrideViaFriend()
	{
		if (m_nextOverride)
			return m_nextOverride->friend_getFinalOverride();
		return this;
	}

	Overridable *m_nextOverride;
};

class BfmeLivingWorldMapObject : public Overridable
{
public:
	BfmeLivingWorldMapObject();
	const FieldParse *getFieldParse();
	void rva006185E0();

	unsigned char m_isOverride;
	unsigned char m_pad009[3];
	int m_objectType;
	float m_defaultFlashValue;
	float m_flashVariation;
};

// Retail uses the compact INI load-type field at +8; the upstream INI
// header includes a read buffer absent from this BFME layout.
// Keep the existing integer-key map instantiation while using the real
// enum-return NameKeyGenerator declaration for its external call.
typedef _STL::map<int, BfmeLivingWorldMapObject *>
	BfmeLivingWorldNameMap;

class BfmeLivingWorldManager
{
public:
	BfmeLivingWorldMapObject *rva0060F620Clone(
		BfmeLivingWorldMapObject *base );

	unsigned char m_unmodelled000[0x27c];
	BfmeLivingWorldNameMap m_nameMap;
};

extern "C" BfmeLivingWorldManager *g_bfmeGameCW;

// ?parseLivingWorldObject00614F50@@YAXPAVINI@@@Z
void parseLivingWorldObject00614F50( INI *ini )
{
	if( g_bfmeGameCW == 0 )
		throw INIException( 3, "TheLivingWorldManager==NULL" );

	bool isOverride = false;
	int storageKey;
	int nameKey = TheNameKeyGenerator->nameToKey(
		ini->getNextToken());
	storageKey = nameKey;
	BfmeLivingWorldMapObject *object;
	BfmeLivingWorldManager *manager;
	if( nameKey != 0 )
	{
		manager = g_bfmeGameCW;
		BfmeLivingWorldNameMap *table = &manager->m_nameMap;
		BfmeLivingWorldNameMap::iterator found = table->find( storageKey );
		if( found != table->end() )
		{
			object = found->second;
			if( object != 0 )
			{
				if( reinterpret_cast<const int *>(ini)[2] == 2 )
				{
					object = manager->rva0060F620Clone(
						(BfmeLivingWorldMapObject *)object->finalOverrideViaFriend());
				}
				isOverride = true;
			}
		}
	}

	if( !isOverride )
	{
		object = new BfmeLivingWorldMapObject;
		if( reinterpret_cast<const int *>(ini)[2] == 2 )
			object->m_isOverride = 1;
	}

	ini->initFromINI( object, object->getFieldParse() );
	object->rva006185E0();

	if( !isOverride )
		g_bfmeGameCW->m_nameMap[ nameKey ] = object;
}
