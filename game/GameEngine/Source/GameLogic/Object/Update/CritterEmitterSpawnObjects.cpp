// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
#include <vector>

class ObjectCreationList;

class INI
{
public:
	const char *getNextToken( const char *seps = 0 );
	const char *getNextTokenOrNull( const char *seps = 0 );
};

class ObjectCreationListStore
{
public:
	const ObjectCreationList *findObjectCreationList( const char *name ) const;
};

extern ObjectCreationListStore *TheObjectCreationListStore;

// Registration names CritterEmitterUpdate; the original data class spelling is unknown.
class Rva0028BB10ModuleData
{
public:
	unsigned char m_unreconstructed_00[0x14];
	_STL::vector<const ObjectCreationList *> m_objectCreationLists;						///< +0x14
};

void parseCritterEmitterSpawnObjects( INI* ini, void *instance, void * /*store*/, const void* /*userData*/ )
{
	Rva0028BB10ModuleData* self = (Rva0028BB10ModuleData*)instance;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		const ObjectCreationList *list = TheObjectCreationListStore->findObjectCreationList(token);
		self->m_objectCreationLists.push_back(list);
	}
}
