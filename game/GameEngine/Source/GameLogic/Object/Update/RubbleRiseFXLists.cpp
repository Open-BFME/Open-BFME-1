// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Open-BFME: RubbleRiseUpdate FXList field parser, retail 0x002A4030, 138 bytes.
//
// The FieldParse table at 0x010C2AB0 pairs the string "FXList" with this body
// and "OCL" with the landed parseRubbleRiseObjectCreationLists at 0x002A40E0.
// The two bodies are the same code over two different arrays. This one reads
// the FXList store at 0x012F144C and appends to the vectors at +0x84; the OCL
// one reads the ObjectCreationList store and appends to the vectors at +0x54.
//
// The phase names at 0x012B2080 read INITIAL, DELAY, BURST and FINAL.
#include <vector>

class FXList;

class INI
{
public:
	static int scanIndexList(const char *token, const char *const *values);
	const char *getNextToken( const char *seps = 0 );
	const char *getNextTokenOrNull( const char *seps = 0 );
};

class FXListStore
{
public:
	const FXList *findFXList( const char *name ) const;
};

extern FXListStore *TheFXListStore;

// Only the parsed vectors are modelled; other module fields remain opaque.
class RubbleRiseUpdateModuleData
{
public:
	unsigned char m_unreconstructed_00[0x84];
	_STL::vector<const FXList *> m_fxLists[4];						///< +0x84
};

static const char *const rubbleRisePhases[] = { "INITIAL", "DELAY", "BURST", "FINAL", 0 };

void parseRubbleRiseFXLists( INI* ini, void *instance, void * /*store*/, const void* /*userData*/ )
{
	RubbleRiseUpdateModuleData* self = (RubbleRiseUpdateModuleData*)instance;
	int phase = INI::scanIndexList(ini->getNextToken(), rubbleRisePhases);
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		const FXList *list = TheFXListStore->findFXList(token);
		self->m_fxLists[phase].push_back(list);
	}
}
