// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Native BfmeAptScreenOptions::Save callback, RVA 0x00560280, 7212 bytes.
// The matched constructor registers AptOptions::Save through ILT 0x00012544.
// See docs/analysis/options_save_00560280.md for the layout and callee evidence.
// Unwitnessed BFME members and virtual slots retain their offsets.
#include "ascii_string.h"
#include <map>
class GameWindow
{
  public:
    void *winGetUserData();
    int winEnable(bool);
};
bool GadgetCheckBoxIsChecked(GameWindow *);
void GadgetComboBoxGetSelectedPos(GameWindow *, int *);
void *GadgetComboBoxGetItemData(GameWindow *, int);
struct Rva00560280SliderData
{
    char field00[12];
    int position;
};
inline int GadgetSliderGetPosition(GameWindow *w)
{
    Rva00560280SliderData *d = (Rva00560280SliderData *)w->winGetUserData();
    if (d)
    {
        return d->position;
    }
    return -1;
}
typedef std::map<AsciiString, AsciiString> PreferenceMap;
class UserPreferences : public PreferenceMap
{
  public:
    virtual ~UserPreferences();
    virtual void slot04();
    virtual void slot08();
    virtual bool write();
    char field0C[0x10 - sizeof(PreferenceMap)];
};
class OptionPreferences : public UserPreferences
{
  public:
    void setAudioLOD(int);
    void setOnlineIPAddress(unsigned);
};
class BfmeS1148;
void bfmeGo1148(BfmeS1148 *);
void Rva0007E5F0OptionPreferencesClear(OptionPreferences *);
class BfmeThingSB
{
  public:
    void bfmeSetSB(int);
};
// Names and values from the retail StaticGameLODNames table at RVA 0x00EA73E4.
enum StaticGameLODLevel
{
    LOD_VERYLOW,
    LOD_LOW,
    LOD_MEDIUM,
    LOD_HIGH,
    LOD_ULTRA_HIGH,
    LOD_CUSTOM
};
// The reference GameLODManager header has the three-level Zero Hour layout.
// BFME has six levels, with the two selectors witnessed here at +16C0/+16C4.
class GameLODManager
{
  public:
    bool setStaticLODLevel(StaticGameLODLevel);
    const char *getStaticGameLODLevelName(StaticGameLODLevel);
    StaticGameLODLevel getStaticLODLevel() const
    {
        return field16C0;
    }
    StaticGameLODLevel getField16C4() const
    {
        return field16C4;
    }
    char field0000[0x16c0];
    StaticGameLODLevel field16C0, field16C4;
};
extern GameLODManager *TheGameLODManager;
class Display
{
  public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual bool slot16();
    virtual void slot17();
    virtual int slot18();
    virtual void slot19(int, int *, int *, int *);
};
class Rva005A00B0AudioClient
{
  public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void stopAudioEvent(void *);
};
extern Display *TheDisplay;
extern Rva005A00B0AudioClient *TheAudioClientUpdate;
class Rva00465B80
{
  public:
    void apply();
};
struct Rva00579160Manager;
extern Rva00579160Manager *Rva00579160TheManager;
class GameLogic;
extern GameLogic *TheGameLogic;
struct Rva00367E30Logic
{
    char pad[0x10c];
    int field10C;
};
class GameSpyInfo;
extern GameSpyInfo *TheGameSpyInfo;
// Retail reads 0x012F4AD0 here, the byte ShowOptions stores beside g_bfmeD1072 (0x012F4AD1).
extern unsigned char g_optByte12F4AD0;
extern void *g_quitMenuLayout;
extern void *g_Va012F4AE4;
struct Rva006C9270GlobalData
{
    char field00[0x1b];
    bool field1B;
    char field1C;
    bool field1D, field1E, field1F;
    char field20[8];
    bool field28;
    char field29[3];
    int field2C, field30;
    char field34[0x2c];
    bool field60;
    char field61[15];
    bool field70;
    char field71[0xa04];
    bool fieldA75;
    char fieldA76;
    bool fieldA77;
    char fieldA78[0x16];
    bool fieldA8E;
    char fieldA8F[0xd5];
    float fieldB64, fieldB68;
    char fieldB6C[0x50];
    float fieldBBC;
    char fieldBC0[0x47];
    bool fieldC07;
    char fieldC08[0x60];
    float fieldC68;
};
// Retail spells the one writable GlobalData global (0x012ED5C8) with EA's own
// type; the field view above stays TU-local and the pointer is cast at each use.
class GlobalData;
extern GlobalData *TheWritableGlobalData;
static inline Rva006C9270GlobalData *localGlobalData()
{
    return (Rva006C9270GlobalData *)TheWritableGlobalData;
}
class BfmeAptScreenOptions
{
  public:
    void _bfme_save(const char *);
    char field000[0x258];
    int field258;
    int field25C;
    OptionPreferences options;
    int field274, field278, field27C;
    bool field280;
    char field281[3];
    GameWindow *field284;
    GameWindow *field288;
    GameWindow *field28C;
    GameWindow *field290;
    GameWindow *field294;
    GameWindow *field298;
    GameWindow *field29C;
    GameWindow *field2A0;
    GameWindow *field2A4;
    GameWindow *field2A8;
    GameWindow *field2AC;
    GameWindow *field2B0;
    GameWindow *field2B4;
    GameWindow *field2B8;
    GameWindow *field2BC;
    GameWindow *field2C0;
    GameWindow *field2C4;
    GameWindow *field2C8;
    GameWindow *field2CC;
    GameWindow *field2D0;
    GameWindow *field2D4;
    GameWindow *field2D8;
    GameWindow *field2DC;
    GameWindow *field2E0;
    GameWindow *field2E4;
    GameWindow *field2E8;
    GameWindow *field2EC;
    GameWindow *field2F0;
    GameWindow *field2F4;
    GameWindow *field2F8;
    GameWindow *field2FC;
    GameWindow *field300;
    GameWindow *field304;
    bool field308;
    char field309[3];
    int field30C;
};
void BfmeAptScreenOptions::_bfme_save(const char *)
{
    // These locals span all pages, as in the shared preference-saving code.
    int val, index;
    if (g_Va012F4AE4)
    {
        TheAudioClientUpdate->stopAudioEvent(g_Va012F4AE4);
        g_Va012F4AE4 = 0;
    }
    // Standard and network pages share graphics and audio preferences.
    if (field258 == 2 || field258 == 3)
    {
        if (g_optByte12F4AD0)
        {
            if (field288)
            {
                GadgetComboBoxGetSelectedPos(field288, &index);
                bool changed;
                switch (index)
                {
                case 0:
                    changed = TheGameLODManager->setStaticLODLevel(LOD_ULTRA_HIGH);
                    break;
                case 1:
                    changed = TheGameLODManager->setStaticLODLevel(LOD_HIGH);
                    break;
                case 2:
                    changed = TheGameLODManager->setStaticLODLevel(LOD_MEDIUM);
                    break;
                case 3:
                    changed = TheGameLODManager->setStaticLODLevel(LOD_LOW);
                    break;
                case 4:
                    changed = TheGameLODManager->setStaticLODLevel(LOD_VERYLOW);
                    break;
                case 5:
                    bfmeGo1148((BfmeS1148 *)&options);
                    changed = TheGameLODManager->setStaticLODLevel(LOD_CUSTOM);
                    break;
                default:
                    changed = false;
                    break;
                }
                if (changed)
                {
                    options["StaticGameLOD"] = TheGameLODManager->getStaticGameLODLevelName(
                        TheGameLODManager->getStaticLODLevel());
                    StaticGameLODLevel fixedLevel = TheGameLODManager->getField16C4();
                    options["FixedStaticGameLOD"] =
                        TheGameLODManager->getStaticGameLODLevelName(fixedLevel);
                }
                if (index == 4 || index == 3)
                {
                    AsciiString prefString;
                    prefString = AsciiString("no");
                    options["HeatEffects"] = prefString;
                    localGlobalData()->field1D = false;
                    localGlobalData()->fieldA75 = false;
                }
                else if (index == 2 || index == 1 || index == 0)
                {
                    AsciiString prefString;
                    prefString = AsciiString("yes");
                    options["HeatEffects"] = prefString;
                    localGlobalData()->field1D = true;
                    localGlobalData()->fieldA75 = true;
                }
                if (index == 2)
                    localGlobalData()->fieldA77 = true;
                else if (index == 1 || index == 0)
                    localGlobalData()->fieldA77 = false;
                if (index != 5)
                    Rva0007E5F0OptionPreferencesClear(&options);
            }
        }
        if (g_optByte12F4AD0 && field284 &&
            (((Rva00367E30Logic *)TheGameLogic)->field10C == 8 || ((Rva00367E30Logic *)TheGameLogic)->field10C == 4) && !TheGameSpyInfo)
        {
            GadgetComboBoxGetSelectedPos(field284, &index);
            if (index < TheDisplay->slot18() && index >= 0)
            {
                int width, height, depth;
                TheDisplay->slot19(index, &width, &height, &depth);
                if (localGlobalData()->field2C != width ||
                    localGlobalData()->field30 != height)
                {
                    field278 = height;
                    field274 = width;
                    field27C = depth;
                    field280 = TheDisplay->slot16();
                    field308 = true;
                }
            }
        }
        val = field2F8 ? GadgetSliderGetPosition(field2F8) : -1;
        if (val != -1)
        {
            float gamma = 1.0f;
            if (val < 50)
            {
                if (val <= 0)
                    gamma = 0.6f;
                else
                    gamma = 1.0f - 0.4f * (float)(50 - val) / 50.0f;
            }
            else if (val > 50)
                gamma = 1.0f + (float)(val - 50) / 50.0f;
            AsciiString prefString;
            prefString.format("%d", val);
            options["Brightness"] = prefString;
            if (localGlobalData()->fieldC68 != gamma)
                localGlobalData()->fieldC68 = gamma;
        }
        val = field2F4 ? GadgetSliderGetPosition(field2F4) : -1;
        if (val != -1)
        {
            if (val < 1)
                val = 1;
            localGlobalData()->fieldBBC = val / 50.0f;
            localGlobalData()->fieldB68 = val / 50.0f;
            localGlobalData()->fieldB64 = val / 50.0f;
            AsciiString prefString;
            prefString.format("%d", val);
            options["ScrollFactor"] = prefString;
        }
        val = field2E0 ? GadgetSliderGetPosition(field2E0) : -1;
        if (val != -1)
        {
            AsciiString prefString;
            prefString.format("%d", val);
            options["MusicVolume"] = prefString;
        }
        val = field2F0 ? GadgetSliderGetPosition(field2F0) : -1;
        if (val != -1)
        {
            AsciiString prefString;
            prefString.format("%d", val);
            options["MovieVolume"] = prefString;
        }
        val = field2EC ? GadgetSliderGetPosition(field2EC) : -1;
        if (val != -1)
        {
            AsciiString prefString;
            prefString.format("%d", val);
            options["AmbientVolume"] = prefString;
        }
        val = field2E4 ? GadgetSliderGetPosition(field2E4) : -1;
        if (val != -1)
        {
            AsciiString prefString;
            prefString.format("%d", val);
            options["SFXVolume"] = prefString;
        }
        val = field2E8 ? GadgetSliderGetPosition(field2E8) : -1;
        if (val != -1)
        {
            AsciiString prefString;
            prefString.format("%d", val);
            options["VoiceVolume"] = prefString;
        }
        if (field290)
        {
            val = GadgetCheckBoxIsChecked(field290);
            if (val != -1)
            {
                AsciiString prefString;
                prefString = val ? AsciiString("yes") : AsciiString("no");
                options["AllHealthBars"] = prefString;
                localGlobalData()->fieldA8E = val != 0;
            }
        }
        if (field294)
        {
            val = GadgetCheckBoxIsChecked(field294);
            if (val != -1)
            {
                AsciiString prefString;
                prefString = val ? AsciiString("yes") : AsciiString("no");
                options["AlternateMouseSetup"] = prefString;
                localGlobalData()->field60 = val == 0;
            }
        }
        if (field29C)
        {
            val = GadgetCheckBoxIsChecked(field29C);
            if (val != -1)
            {
                AsciiString prefString;
                prefString = val ? AsciiString("yes") : AsciiString("no");
                options["UnitDecals"] = prefString;
                localGlobalData()->fieldA75 = val != 0;
            }
        }
        if (field2B4)
        {
            val = GadgetCheckBoxIsChecked(field2B4);
            if (val != -1)
            {
                AsciiString prefString;
                prefString = val ? AsciiString("yes") : AsciiString("no");
                options["UseEAX3"] = prefString;
            }
        }

        if (field2B8)
        {
            val = GadgetCheckBoxIsChecked(field2B8);
            if (val != -1)
            {
                if (val)
                {
                    options.setAudioLOD(1);
                    ((BfmeThingSB *)TheGameLODManager)->bfmeSetSB(1);
                }
                else
                {
                    options.setAudioLOD(0);
                    ((BfmeThingSB *)TheGameLODManager)->bfmeSetSB(0);
                }
            }
        }
        options.write();
        if (g_quitMenuLayout)
            ((Rva00465B80 *)Rva00579160TheManager)->apply();
        // The advanced page stores its controls, then returns to the standard page.
    }
    else if (field258 == 4)
    {
        field30C = 5;
        if (field29C)
            field29C->winEnable(true);
        if (field290)
            field290->winEnable(true);
        if (field2BC)
        {
            val = GadgetCheckBoxIsChecked(field2BC);
            if (val != -1)
            {
                AsciiString prefString;
                prefString = val ? AsciiString("yes") : AsciiString("no");
                options["AnisotropicTextureFiltering"] = prefString;
            }
        }
        if (field2C0)
        {
            val = GadgetCheckBoxIsChecked(field2C0);
            if (val != -1)
            {
                AsciiString prefString;
                prefString = val ? AsciiString("yes") : AsciiString("no");
                options["TerrainLighting"] = prefString;
            }
        }
        if (field2C4)
        {
            val = GadgetCheckBoxIsChecked(field2C4);
            if (val != -1)
            {
                AsciiString prefString;
                prefString = val ? AsciiString("yes") : AsciiString("no");
                options["3DShadows"] = prefString;
            }
        }
        if (field2C8)
        {
            val = GadgetCheckBoxIsChecked(field2C8);
            if (val != -1)
            {
                AsciiString prefString;
                prefString = val ? AsciiString("yes") : AsciiString("no");
                options["2DShadows"] = prefString;
            }
        }
        if (field2CC)
        {
            val = GadgetCheckBoxIsChecked(field2CC);
            if (val != -1)
            {
                AsciiString prefString;
                prefString = val ? AsciiString("yes") : AsciiString("no");
                options["SmoothWaterBorder"] = prefString;
            }
        }
        if (field2D0)
        {
            val = GadgetCheckBoxIsChecked(field2D0);
            if (val != -1)
            {
                AsciiString prefString;
                prefString = val ? AsciiString("yes") : AsciiString("no");
                options["ShowProps"] = prefString;
            }
        }
        if (field2D4)
        {
            val = GadgetCheckBoxIsChecked(field2D4);
            if (val != -1)
            {
                AsciiString prefString;
                prefString = val ? AsciiString("yes") : AsciiString("no");
                options["ExtraAnimations"] = prefString;
            }
        }
        if (field2D8)
        {
            val = GadgetCheckBoxIsChecked(field2D8);
            if (val != -1)
            {
                AsciiString prefString;
                prefString = val ? AsciiString("yes") : AsciiString("no");
                options["HeatEffects"] = prefString;
            }
        }
        if (field2DC)
        {
            val = GadgetCheckBoxIsChecked(field2DC);
            if (val != -1)
            {
                AsciiString prefString;
                prefString = val ? AsciiString("no") : AsciiString("yes");
                options["DynamicLOD"] = prefString;
            }
        }
        if (field2FC)
        {
            AsciiString prefString;
            prefString.format("%d", GadgetSliderGetPosition(field2FC));
            options["TextureReduction"] = prefString;
        }
        if (field300)
        {
            AsciiString prefString;
            prefString.format("%d", GadgetSliderGetPosition(field300));
            options["MaxParticleCount"] = prefString;
        }
        options["UsePixelShader"] = localGlobalData()->field28 ? "no" : "yes";
        options["FPSLimit"] = localGlobalData()->field1E ? "yes" : "no";
        options["UseHighQualityVideo"] = localGlobalData()->field1F ? "yes" : "no";
        options["BuildingOcclusion"] = localGlobalData()->field70 ? "yes" : "no";
        options["GrassDrawSkip"] = localGlobalData()->field1B ? "yes" : "no";
        field258 = 2;
    }
    if (field258 == 3)
    {
        if (field2A0)
        {
            val = GadgetCheckBoxIsChecked(field2A0);
            if (val != -1)
            {
                AsciiString prefString;
                prefString = val ? AsciiString("yes") : AsciiString("no");
                options["SendDelay"] = prefString;
                localGlobalData()->fieldC07 = val != 0;
            }
        }
        if (field28C)
        {
            GadgetComboBoxGetSelectedPos(field28C, &index);
            if (index >= 0)
                options.setOnlineIPAddress((unsigned)GadgetComboBoxGetItemData(field28C, index));
        }
    }
}
