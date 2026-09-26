// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
#include <vector>

class ObjectCreationList;

class INI
{
public:
	static int scanIndexList(const char *token, const char *const *values);
	const char *getNextToken( const char *seps = 0 );
	const char *getNextTokenOrNull( const char *seps = 0 );
};

class ObjectCreationListStore
{
public:
	const ObjectCreationList *findObjectCreationList( const char *name ) const;
};

extern ObjectCreationListStore *TheObjectCreationListStore;

// Only the parsed vectors are modelled; other module fields remain opaque.
class StructureToppleUpdateModuleData
{
public:
	unsigned char m_unreconstructed_00[0x6C];
	_STL::vector<const ObjectCreationList *> m_objectCreationLists[3];						///< +0x6C
};

static const char *const objectCreationPhases[] = { "INITIAL", "DELAY", "FINAL", 0 };

void parseStructureToppleObjectCreationLists( INI* ini, void *instance, void * /*store*/, const void* /*userData*/ )
{
	StructureToppleUpdateModuleData* self = (StructureToppleUpdateModuleData*)instance;
	int phase = INI::scanIndexList(ini->getNextToken(), objectCreationPhases);
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		const ObjectCreationList *list = TheObjectCreationListStore->findObjectCreationList(token);
		self->m_objectCreationLists[phase].push_back(list);
	}
}
