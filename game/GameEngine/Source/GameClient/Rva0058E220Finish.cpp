// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2 /Ob2
// Keep these together: retail passes the helper's entry in a private register.
#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

struct BfmeEntryWU { AsciiString text; int size; bool bold; char pad[3]; int color; };
struct BfmeEntryWR { AsciiString text; int size; bool bold; char pad[3]; int color; };
struct BfmeEntryWS { AsciiString text; int size; bool bold; char pad[3]; int color; };
struct BfmeEntryWT { AsciiString text; int size; bool bold; char pad[3]; int color; };
struct Gen_00442460 { BfmeEntryWU bfmeEntryWU() const; };
struct Gen_0043FC50 { BfmeEntryWR bfmeEntryWR() const; };
struct Gen_0043FD60 { BfmeEntryWS bfmeEntryWS() const; };
struct Gen_0043FE70 { BfmeEntryWT bfmeEntryWT() const; };
class InGameUI;
extern InGameUI *TheInGameUI;

struct Rva00579160Manager {
    virtual void slot00(); virtual void slot04(); virtual void slot08();
    virtual void slot0c(); virtual void slot10(); virtual void slot14();
    virtual void slot18(); virtual void slot1c(); virtual void slot20();
    virtual void slot24(); virtual const float *scale();
};
// Retail global 0x012F19E8, canonical name and pointee type;
// Rva00579160Manager is this TU's view of the pointee scaled() is read from.
class WindowManager;
extern WindowManager *g_rva012F19E8WindowManager;
static inline Rva00579160Manager *Rva00579160TheManager()
{
    return (Rva00579160Manager *)g_rva012F19E8WindowManager;
}

class GameFont;
class FontLibrary;
// Retail global 0x012F1B38: the defining declaration is `FontLibrary *TheFontLibrary`,
// so its declared pointee stays FontLibrary for the global symbol. The matched
// method body is FontLibraryBFMERetail::getFont at 0x004772D0; this TU only
// needs its call signature.
class FontLibraryBFMERetail {
public:
    GameFont *getFont(AsciiString *name, float size, unsigned char bold);
};
extern FontLibrary *TheFontLibrary;

struct Rva00588FA0Widget {
    virtual void slot00(); virtual void slot04(); virtual void slot08();
    virtual void slot0c(); virtual void slot10(); virtual void slot14();
    virtual void setFont(GameFont *font);
    virtual void slot1c(); virtual void slot20();
    virtual void setFlag(int value);
    virtual void setColor(int color, int reset);
};

static void Rva00588FA0(Rva00588FA0Widget *widget, BfmeEntryWU *entry)
{
    const float *range = Rva00579160TheManager()->scale();
    float factor = range[0] < range[1] ? range[0] : range[1];
    GameFont *font = reinterpret_cast<FontLibraryBFMERetail *>(TheFontLibrary)->getFont(&entry->text,
        entry->size * factor, entry->bold);
    widget->setColor(entry->color, 0);
    widget->setFlag(1);
    widget->setFont(font);
}

class Rva00592A10Owner {
public:
    void finish();
    char m_pad00[0x14];
    Rva00588FA0Widget *m_widgets[5];
};

void Rva00592A10Owner::finish()
{
    {
        Rva00588FA0(m_widgets[0],
            &((Gen_00442460 *)TheInGameUI)->bfmeEntryWU());
    }
    {
        Rva00588FA0(m_widgets[1],
            (BfmeEntryWU *)&((Gen_0043FC50 *)TheInGameUI)->bfmeEntryWR());
    }
    {
        Rva00588FA0(m_widgets[2],
            (BfmeEntryWU *)&((Gen_0043FC50 *)TheInGameUI)->bfmeEntryWR());
    }
    {
        Rva00588FA0(m_widgets[3],
            (BfmeEntryWU *)&((Gen_0043FD60 *)TheInGameUI)->bfmeEntryWS());
    }
    {
        Rva00588FA0(m_widgets[4],
            (BfmeEntryWU *)&((Gen_0043FE70 *)TheInGameUI)->bfmeEntryWT());
    }
}
