// cl: /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WWLib
// Recovered map-preview description update at RVA 0x005208D0.
// Descriptive bfme names do not claim original source spellings. The metadata
// getter calls the cached map.str text loader, then returns its first line.

#include "unicode_string.h"

class GameWindow;
void GadgetListBoxReset(GameWindow *listbox);
int GadgetListBoxAddEntryText(GameWindow *listbox, UnicodeString text,
    int color, int row, int column, bool overwrite);

class MapMetaData
{
public:
    UnicodeString bfme_getDescriptionFirstLine();
};

class AptMapPreview
{
public:
    void bfmeSetMapDescription(MapMetaData *map);
private:
    char m_unmodelled[0x10];
    GameWindow *m_descriptionList;
};

void AptMapPreview::bfmeSetMapDescription(MapMetaData *map)
{
    if (m_descriptionList)
    {
        GadgetListBoxReset(m_descriptionList);
        if (map)
            GadgetListBoxAddEntryText(m_descriptionList,
                map->bfme_getDescriptionFirstLine(), -1, -1, -1, true);
    }
}
