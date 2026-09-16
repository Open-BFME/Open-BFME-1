// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Open-BFME: RubbleRiseUpdate OCL field parser, retail 0x002A40E0, 138 bytes.
//
// The FieldParse table at 0x010C2AB0 pairs the string "OCL" with this body.
// Its other fields are MinRubbleRiseDelay, RubbleRiseDamping and RubbleHeight,
// and the module registry pins the RubbleRiseUpdate constructor at 0x002A3640,
// one run of functions below this one. The already landed
// parseStructureToppleObjectCreationLists at 0x002B0890 is the same code for
// StructureToppleUpdate, so this body is the RubbleRiseUpdate copy of it.
//
// The phase names at 0x012B2080 read INITIAL, DELAY, BURST, FINAL, one more
// than the topple version, and the vector array starts at +0x54 instead of
// +0x6C.
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
class RubbleRiseUpdateModuleData
{
public:
	unsigned char m_unreconstructed_00[0x54];
	_STL::vector<const ObjectCreationList *> m_objectCreationLists[4];						///< +0x54
};

static const char *const objectCreationPhases[] = { "INITIAL", "DELAY", "BURST", "FINAL", 0 };

void parseRubbleRiseObjectCreationLists( INI* ini, void *instance, void * /*store*/, const void* /*userData*/ )
{
	RubbleRiseUpdateModuleData* self = (RubbleRiseUpdateModuleData*)instance;
	int phase = INI::scanIndexList(ini->getNextToken(), objectCreationPhases);
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		const ObjectCreationList *list = TheObjectCreationListStore->findObjectCreationList(token);
		self->m_objectCreationLists[phase].push_back(list);
	}
}
