// cl: /DNDEBUG /MD /EHsc
// Retail RVA 0x00520920. Names prefixed with bfme describe recovered behavior;
// the original member spelling is not known. The caller at 0x005216B0 passes
// this map-preview object and MapMetaData, whose filename is at +0x50.
// The display-name callee reads the player count at +0x20 and appends it.
#include "../../../../../inputs/reference/shims/stringinline/StringInline.h"

class MapMetaData
{
public:
    UnicodeString bfme_getDisplayName();
};

class WindowManager
{
public:
    void bfme_setAptText(const AsciiString &, const UnicodeString &);
};

extern WindowManager *g_theWindowManager;

class AptMapPreview
{
public:
    void bfmeSetMapTitle(MapMetaData *map);
};

void AptMapPreview::bfmeSetMapTitle(MapMetaData *map)
{
    if (g_theWindowManager)
    {
        if (map)
        {
            AsciiString key("APT:MapTitle");
            g_theWindowManager->bfme_setAptText(key, map->bfme_getDisplayName());
        }
        else
            g_theWindowManager->bfme_setAptText(AsciiString("APT:MapTitle"), UnicodeString(L" "));
    }
}
