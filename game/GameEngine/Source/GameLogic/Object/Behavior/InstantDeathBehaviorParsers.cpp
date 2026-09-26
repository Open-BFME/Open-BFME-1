// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
#include <vector>

class ObjectCreationList;
class WeaponTemplate;

template <typename T> class StringBase
{
	friend class BFMERetailAsciiString;
	StringBase( const T *text );
	void *m_data;
};

// Retail constructs the by-value argument through an inline base forwarder.
class BFMERetailAsciiString : private StringBase<char>
{
public:
	BFMERetailAsciiString( const char *text ) : StringBase<char>(text) {}
	~BFMERetailAsciiString();
};

class INI
{
public:
	const char *getNextToken( const char *seps = 0 );
	const char *getNextTokenOrNull( const char *seps = 0 );
};

class WeaponStore
{
public:
	const WeaponTemplate *findWeaponTemplate( BFMERetailAsciiString name ) const;
};

class ObjectCreationListStore
{
public:
	const ObjectCreationList *findObjectCreationList( const char *name ) const;
};

extern ObjectCreationListStore *TheObjectCreationListStore;
extern WeaponStore *TheWeaponStore;

class InstantDeathBehaviorModuleData
{
public:
	unsigned char m_unreconstructed_00[0x40];
	_STL::vector<const ObjectCreationList *> m_objectCreationLists;
	_STL::vector<const WeaponTemplate *> m_weapons;
};

void parseInstantDeathObjectCreationLists( INI* ini, void *instance, void * /*store*/, const void* /*userData*/ )
{
	InstantDeathBehaviorModuleData* self = (InstantDeathBehaviorModuleData*)instance;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		const ObjectCreationList *list = TheObjectCreationListStore->findObjectCreationList(token);
		self->m_objectCreationLists.push_back(list);
	}
}

// The registered Weapon field appends to the module vector at +0x4C.
void parseInstantDeathWeapons( INI* ini, void *instance, void * /*store*/, const void* /*userData*/ )
{
	InstantDeathBehaviorModuleData* self = (InstantDeathBehaviorModuleData*)instance;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		const WeaponTemplate *weapon = TheWeaponStore->findWeaponTemplate(token);
		self->m_weapons.push_back(weapon);
	}
}
