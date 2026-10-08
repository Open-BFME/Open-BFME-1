// Retail 0x007E4D40: movie paths and signed colour-table initialization.
// Evidence: targets/game/reverse/identity_evidence/007e4d40-movie-init.md
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c- /I.
#include "game/Libraries/Source/WWVegas/WWLib/ascii_string.h"
#include <stdio.h>
#include <string.h>

class SubtitleEntry;
typedef SubtitleEntry *(__cdecl *CreateSubtitleEntry)(AsciiString *, int,
    const AsciiString &, unsigned int, int, int, int, int, int);

// The witnessed prefix is shared with VideoPlayerInit.cpp.
// The base constructor writes +8, +12 and +16 without a receiver adjustment.
class VideoPlayer
{
public:
    virtual ~VideoPlayer();
    virtual void init();

private:
    char m_pad04[4];
    void *m_makeNameCallback;
    int m_second;
    CreateSubtitleEntry m_createSubtitleEntry;
};
class GlobalData;
extern GlobalData *TheWritableGlobalData;
AsciiString GetRegistryLanguage();
class Rva009A58C0 { public: static void store(int); };
void Rva009A4D00Init();

extern unsigned char g_Va01309848;
extern char g_Va01309849[];
extern char g_Va0130994D[];
extern unsigned char g_Va0130998D;
extern char g_Va0130998E[];
extern char g_Va01309A92[];
extern unsigned char g_Va01309AD2;
extern char g_Va01309AD3[];
extern char g_Va01309BD7[];
class Gen_00C70BC0Target;
extern Gen_00C70BC0Target TheBfmeObject_00C70BC0;
extern unsigned int g_Va01308838[1024];
extern int g_Va01308438[256];
extern int g_Va01308038[256];
extern int g_Va01307C38[256];
extern int g_Va01307838[256];
extern unsigned int g_Va01307438[256];

class Rva007E4A00 : public VideoPlayer
{
public:
    virtual ~Rva007E4A00();
    virtual void init();
};

// ?init@Rva007E4A00@@UAEXXZ
void Rva007E4A00::init()
{
    VideoPlayer::init();
    AsciiString &path = *(AsciiString *)((char *)TheWritableGlobalData + 0xdc0);
    const void *header = *(const void **)&path;
    if (header && *(const unsigned short *)((const char *)header + 4)) {
        g_Va01309848 = 1;
        sprintf(g_Va01309849, "%s%s\\", path.str(), "Data\\Movies");
        strcpy(g_Va0130994D, "Mod Path");
    }
    g_Va0130998D = 1;
    sprintf(g_Va0130998E, "Lang/%s/Data/Movies/", GetRegistryLanguage().str());
    strcpy(g_Va01309A92, "Localized Path");
    g_Va01309AD2 = 1;
    sprintf(g_Va01309AD3, "%s\\", "Data\\Movies");
    strcpy(g_Va01309BD7, "Non-Localized Path");
    Rva009A58C0::store((int)&TheBfmeObject_00C70BC0);
    Rva009A4D00Init();
    for (unsigned int i = 0; i < 1024; ++i) {
        int value = (int)((int)(i - 256) * 1.2f - 15.0f);
        g_Va01308838[i] = (unsigned char)(value > 255 ? 255 : (value < 0 ? 0 : value));
    }
    for (int i = 0; i < 256; ++i) {
        g_Va01308438[i] = ((i - 128) * 443) / 256 + 256;
        g_Va01308038[i] = ((i - 128) * -86) / 256;
        g_Va01307C38[i] = ((i - 128) * -179) / 256 + 256;
        g_Va01307838[i] = ((i - 128) * 351) / 256 + 256;
        int value = ((i - 23) * 255) / 211;
        g_Va01307438[i] = (unsigned int)(value > 255 ? 255 : (value < 0 ? 0 : value)) << 24;
    }
}
