// cl: /O2 /Ob1 /DNDEBUG /MD /EHsc /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Include
#include "ascii_string.h"
#include "Common/INI/INI.h"

template <> inline bool StringBase<char>::isEmpty() const
{
    return m_data == 0 || m_data->length == 0;
}

class SubsystemInterface
{
public:
    virtual ~SubsystemInterface();
    virtual void init();
    virtual bool loadIniFilesFromLegend();
    virtual void postProcessLoad();
    void setName(AsciiString name);
    void setNameInline(AsciiString name) { m_name = name; }
    AsciiString m_name;
};

class ImageCollection
{
public:
    ImageCollection();
    void load(int textureSize);
    unsigned char m_bytes[0x14];
};

class Anim2DCollection : public SubsystemInterface
{
public:
    Anim2DCollection();
    unsigned char m_bytes[8];
};

class BfmeReg963 : public SubsystemInterface
{
public:
    BfmeReg963();
    unsigned char m_bytes[0x20];
};

class AnimationSoundClientBehaviorGlobal : public SubsystemInterface {};
class AnimationSoundModuleManager;

class Mouse : public SubsystemInterface
{
public:
    virtual void slot04(); virtual void slot05(); virtual void slot06();
    virtual void slot07(); virtual void slot08();
    virtual void parseIni();
    virtual void initCursorResources();
    virtual void slot0B(); virtual void slot0C(); virtual void slot0D();
    virtual void slot0E(); virtual void slot0F(); virtual void slot10();
    virtual void setMouseLimits();
};

class DisplayStringManager : public SubsystemInterface {};
class Keyboard : public SubsystemInterface {};
class Display : public SubsystemInterface {};
class GameWindowManager : public SubsystemInterface {};
class IMEManager : public SubsystemInterface {};
class InGameUI : public SubsystemInterface {};
class VideoPlayer : public SubsystemInterface {};
class LanguageFilter : public SubsystemInterface {};
class SnowManager : public SubsystemInterface {};
class CloudEffectSystem : public SubsystemInterface {};
class CloudSystem : public SubsystemInterface {};

class Snapshot { public: virtual ~Snapshot(); };
class TerrainVisual : public Snapshot, public SubsystemInterface {};

class Shell : public SubsystemInterface
{
public:
    Shell();
    unsigned char m_bytes[0x68];
};

class HotKeyManager : public SubsystemInterface
{
public:
    HotKeyManager();
    unsigned char m_bytes[0x18];
};

class RayEffectSystem : public SubsystemInterface
{
public:
    RayEffectSystem();
    unsigned char m_bytes[0xE00];
};

class ControlBarResizer
{
public:
    ControlBarResizer();
    unsigned char m_bytes[4];
};
class HeaderTemplateManager { public: void init(); };
class CampaignManager
{
public:
    CampaignManager();
    void init();
    unsigned char m_bytes[0x1C];
};

class FontLibrary
{
public:
    virtual ~FontLibrary();
    virtual void init();
    virtual bool loadIniFilesFromLegend();
};

struct FontDesc { AsciiString name; int size; bool bold; };

class GlobalLanguage
{
public:
    unsigned char m_bytes[0xD0];
    FontDesc m_drawGroupInfoFont;
};
struct DrawGroupInfo
{
    AsciiString m_fontName;
    int m_fontSize;
    bool m_fontIsBold;
};

class GameMessageTranslator;
class CommandTranslator;
class MessageStream
{
public:
    unsigned int attachTranslator(GameMessageTranslator *, unsigned int);
    GameMessageTranslator *findTranslator(unsigned int);
};

class Rva0042ECB0
{
public:
    Rva0042ECB0() : m_value(0) {}
    virtual void handle();
    int m_value;
};
class Rva0042EC60
{
public:
    Rva0042EC60() : m_value(1) {}
    virtual void handle();
    int m_value;
};
class Rva0042E430 { public: virtual void slot(); };
class Rva0042E480 { public: virtual void slot(); };
class Rva0042E4D0 { public: virtual void slot(); };

#define TRANSLATOR(T, N) class T { public: T(); unsigned char m_bytes[N]; };
TRANSLATOR(LookAtTranslator, 0x1F8)
TRANSLATOR(MetaEventTranslator, 0x28)
TRANSLATOR(Gen_005B42F0, 0x38)
TRANSLATOR(Rva005B1A00, 0x3C)
TRANSLATOR(SelectionTranslator, 0x40)
TRANSLATOR(BfmeOwnVVD, 0x158)
TRANSLATOR(Rva005A7A90, 0x30)
#undef TRANSLATOR

extern GlobalLanguage *TheGlobalLanguageData;
extern DrawGroupInfo *TheDrawGroupInfo;
extern DisplayStringManager *TheDisplayStringManager;
extern Keyboard *TheKeyboard;
extern ImageCollection *TheMappedImageCollection;
extern Anim2DCollection *TheAnim2DCollection;
extern AnimationSoundClientBehaviorGlobal *g_animationSoundClientBehaviorGlobal;
extern MessageStream *TheMessageStream;
extern FontLibrary *TheFontLibrary;
extern Mouse *TheMouse;
extern Display *TheDisplay;
extern HeaderTemplateManager *TheHeaderTemplateManager;
extern GameWindowManager *TheWindowManager;
extern IMEManager *TheIMEManager;
extern Shell *TheShell;
extern InGameUI *TheInGameUI;
extern HotKeyManager *TheHotKeyManager;
extern TerrainVisual *TheTerrainVisual;
extern RayEffectSystem *TheRayEffects;
extern VideoPlayer *TheVideoPlayer;
extern LanguageFilter *TheLanguageFilter;
extern CampaignManager *TheCampaignManager;
extern SnowManager *TheSnowManager;
extern CloudEffectSystem *TheCloudEffectSystem;
extern CloudSystem *TheCloudSystem;
class Gen0048D200;
Gen0048D200 *make0048D380();
LanguageFilter *createLanguageFilter();
void registerGuiFXCallbacks00510FA0();

class GameClient
{
public:
    virtual ~GameClient();
    virtual void init();
#define V(N) virtual void slot##N();
    V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09)
    V(0A) V(0B) V(0C) V(0D) V(0E) V(0F) V(10) V(11)
    V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
    V(1A) V(1B) V(1C) V(1D) V(1E) V(1F) V(20)
#undef V
    virtual Display *createGameDisplay();
    virtual InGameUI *createInGameUI();
    virtual GameWindowManager *createWindowManager();
    virtual FontLibrary *createFontLibrary();
    virtual DisplayStringManager *createDisplayStringManager();
    virtual VideoPlayer *createVideoPlayer();
    virtual TerrainVisual *createTerrainVisual();
    virtual Keyboard *createKeyboard();
    virtual Mouse *createMouse();
    virtual SnowManager *createSnowManager();
    virtual CloudEffectSystem *createCloudEffectManager();
    virtual CloudSystem *createCloudBreakEffectManager();
    virtual void setFrameRate(float);
    unsigned char m_unmodelled004[0x24];
    unsigned int m_nextDrawableID;
    unsigned int m_translators[32];
    unsigned int m_numTranslators;
    CommandTranslator *m_commandTranslator;
};

// Open BFME 2 donor: Code/GameEngine/Source/GameClient/GameClientDrawableTOC.cpp.
// ?init@GameClient@@UAEXXZ
void GameClient::init()
{
    setFrameRate(33.333333f);
    INI ini;
    ini.loadFile(AsciiString("Data\\INI\\DrawGroupInfo.ini"), INI_LOAD_OVERWRITE, 0);
    if (TheGlobalLanguageData)
    {
        const AsciiString &fontName = TheGlobalLanguageData->m_drawGroupInfoFont.name;
        if (!fontName.isEmpty())
        {
            TheDrawGroupInfo->m_fontName = fontName;
            TheDrawGroupInfo->m_fontSize = TheGlobalLanguageData->m_drawGroupInfoFont.size;
            TheDrawGroupInfo->m_fontIsBold = TheGlobalLanguageData->m_drawGroupInfoFont.bold;
        }
    }
    TheDisplayStringManager = createDisplayStringManager();
    if (TheDisplayStringManager)
    {
        TheDisplayStringManager->init();
        TheDisplayStringManager->setName(AsciiString("TheDisplayStringManager"));
    }
    TheKeyboard = createKeyboard();
    TheKeyboard->init();
    TheKeyboard->setNameInline(AsciiString("TheKeyboard"));
    TheMappedImageCollection = new ImageCollection;
    TheMappedImageCollection->load(512);
    TheAnim2DCollection = new Anim2DCollection;
    TheAnim2DCollection->init();
    TheAnim2DCollection->setNameInline(AsciiString("TheAnim2DCollection"));
    g_animationSoundClientBehaviorGlobal = (AnimationSoundClientBehaviorGlobal *)new BfmeReg963;
    g_animationSoundClientBehaviorGlobal->init();
    g_animationSoundClientBehaviorGlobal->setNameInline(AsciiString("TheAnimationSoundModuleManager"));
    if (TheMessageStream)
    {
        m_translators[m_numTranslators++] = TheMessageStream->attachTranslator((GameMessageTranslator *)new Rva0042ECB0, 4);
        m_translators[m_numTranslators++] = TheMessageStream->attachTranslator((GameMessageTranslator *)new LookAtTranslator, 5);
        m_translators[m_numTranslators++] = TheMessageStream->attachTranslator((GameMessageTranslator *)new Rva0042EC60, 10);
        m_translators[m_numTranslators++] = TheMessageStream->attachTranslator((GameMessageTranslator *)new MetaEventTranslator, 20);
        m_translators[m_numTranslators++] = TheMessageStream->attachTranslator((GameMessageTranslator *)new Rva0042E430, 25);
        m_translators[m_numTranslators++] = TheMessageStream->attachTranslator((GameMessageTranslator *)new Gen_005B42F0, 27);
        m_translators[m_numTranslators++] = TheMessageStream->attachTranslator((GameMessageTranslator *)new Rva005B1A00, 40);
        m_translators[m_numTranslators++] = TheMessageStream->attachTranslator((GameMessageTranslator *)new SelectionTranslator, 50);
        m_translators[m_numTranslators++] = TheMessageStream->attachTranslator((GameMessageTranslator *)new BfmeOwnVVD, 60);
        m_translators[m_numTranslators] = TheMessageStream->attachTranslator((GameMessageTranslator *)new Rva005A7A90, 70);
        m_commandTranslator = (CommandTranslator *)TheMessageStream->findTranslator(m_translators[m_numTranslators++]);
        m_translators[m_numTranslators++] = TheMessageStream->attachTranslator((GameMessageTranslator *)new Rva0042E480, 100);
        m_translators[m_numTranslators++] = TheMessageStream->attachTranslator((GameMessageTranslator *)new Rva0042E4D0, 999999999);
    }
    TheFontLibrary = createFontLibrary();
    if (TheFontLibrary)
    {
        TheFontLibrary->init();
        TheFontLibrary->loadIniFilesFromLegend();
    }
    TheMouse = createMouse();
    TheMouse->parseIni();
    TheMouse->initCursorResources();
    TheMouse->setNameInline(AsciiString("TheMouse"));
    TheDisplay = createGameDisplay();
    if (TheDisplay)
    {
        TheDisplay->init();
        TheDisplay->setName(AsciiString("TheDisplay"));
    }
    TheHeaderTemplateManager = (HeaderTemplateManager *)new ControlBarResizer;
    if (TheHeaderTemplateManager)
        TheHeaderTemplateManager->init();
    TheWindowManager = createWindowManager();
    if (TheWindowManager)
    {
        TheWindowManager->init();
        TheWindowManager->setName(AsciiString("TheWindowManager"));
    }
    TheIMEManager = (IMEManager *)make0048D380();
    if (TheIMEManager)
    {
        TheIMEManager->init();
        TheIMEManager->setName(AsciiString("TheIMEManager"));
    }
    TheShell = new Shell;
    if (TheShell)
    {
        TheShell->init();
        TheShell->setName(AsciiString("TheShell"));
    }
    TheInGameUI = createInGameUI();
    if (TheInGameUI)
    {
        TheInGameUI->init();
        TheInGameUI->setName(AsciiString("TheInGameUI"));
    }
    TheHotKeyManager = new HotKeyManager;
    if (TheHotKeyManager)
    {
        TheHotKeyManager->init();
        TheHotKeyManager->setName(AsciiString("TheHotKeyManager"));
    }
    TheTerrainVisual = createTerrainVisual();
    if (TheTerrainVisual)
    {
        TheTerrainVisual->init();
        TheTerrainVisual->setName(AsciiString("TheTerrainVisual"));
    }
    TheRayEffects = new RayEffectSystem;
    if (TheRayEffects)
    {
        TheRayEffects->init();
        TheRayEffects->setName(AsciiString("TheRayEffects"));
    }
    TheMouse->init();
    if (TheMouse)
    {
        TheMouse->setMouseLimits();
        TheMouse->setName(AsciiString("TheMouse"));
    }
    TheVideoPlayer = createVideoPlayer();
    if (TheVideoPlayer)
    {
        TheVideoPlayer->init();
        TheVideoPlayer->setName(AsciiString("TheVideoPlayer"));
    }
    TheLanguageFilter = createLanguageFilter();
    if (TheLanguageFilter)
    {
        TheLanguageFilter->init();
        TheLanguageFilter->setName(AsciiString("TheLanguageFilter"));
    }
    TheCampaignManager = new CampaignManager;
    TheCampaignManager->init();
    TheDisplayStringManager->postProcessLoad();
    TheSnowManager = createSnowManager();
    if (TheSnowManager)
    {
        TheSnowManager->init();
        TheSnowManager->setName(AsciiString("TheSnowManager"));
    }
    TheCloudEffectSystem = createCloudEffectManager();
    if (TheCloudEffectSystem)
    {
        TheCloudEffectSystem->init();
        TheCloudEffectSystem->setName(AsciiString("TheCloudEffectManager"));
    }
    TheCloudSystem = createCloudBreakEffectManager();
    if (TheCloudSystem)
    {
        TheCloudSystem->init();
        TheCloudSystem->setName(AsciiString("TheCloudBreakEffectManager"));
    }
    registerGuiFXCallbacks00510FA0();
}
