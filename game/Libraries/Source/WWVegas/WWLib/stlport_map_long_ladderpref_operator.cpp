// cl: /DNDEBUG /MD /EHsc /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/campaignmanagerascii /Iinputs/reference/shims/stringbaseunicode
// stlport

// The retail map subscript at 0x000ACC40 belongs to LadderPreferences' recent
// ladder map.  The callers pass a signed time_t key and use the returned
// LadderPref reference to fill a newly inserted record.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <stl/_config.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG
#include <map>
#include "Common/AsciiString.h"
#include "Common/UnicodeString.h"

class LadderPref
{
public:
	UnicodeString name;
	AsciiString address;
	unsigned short port;
	long lastPlayDate;
};

typedef std::map<long, LadderPref> LadderPrefMap;

template LadderPref &LadderPrefMap::operator[](const long &key);
