// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

#include <vector>

class FXList;

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	const char *getNextTokenOrNull(const char *seps = 0);
	static int scanIndexList(const char *token, const char *const *list);
};

class FXListStore
{
public:
	const FXList *findFXList(const char *name) const;
};

class ObjectCreationList;
class ObjectCreationListStore
{
public:
	const ObjectCreationList *findObjectCreationList(const char *name) const;
};

extern FXListStore *TheFXListStore;
extern ObjectCreationListStore *TheObjectCreationListStore;
extern const char *const StructureCollapsePhaseNames[6];

// Only the five parsed slots are modelled; the original class spelling is unknown.
class Rva002AEDF0ModuleData
{
public:
	unsigned char m_unreconstructed_00[0x50];
	_STL::vector<const ObjectCreationList *> m_objectCreationLists[5];
	_STL::vector<const FXList *> m_effects[5];
};

void parseStructureCollapseEffects(INI *ini, void *instance, void *store, const void *userData)
{
	Rva002AEDF0ModuleData *self = (Rva002AEDF0ModuleData *)instance;
	int phase = INI::scanIndexList(ini->getNextToken(), StructureCollapsePhaseNames);
	for (const char *token = ini->getNextToken(); token != 0; token = ini->getNextTokenOrNull())
	{
		const FXList *effect = TheFXListStore->findFXList(token);
		self->m_effects[phase].push_back(effect);
	}
}

void parseStructureCollapseObjectCreationLists(INI *ini, void *instance, void *store, const void *userData)
{
	Rva002AEDF0ModuleData *self = (Rva002AEDF0ModuleData *)instance;
	int phase = INI::scanIndexList(ini->getNextToken(), StructureCollapsePhaseNames);
	for (const char *token = ini->getNextToken(); token != 0; token = ini->getNextTokenOrNull())
	{
		const ObjectCreationList *list = TheObjectCreationListStore->findObjectCreationList(token);
		self->m_objectCreationLists[phase].push_back(list);
	}
}
