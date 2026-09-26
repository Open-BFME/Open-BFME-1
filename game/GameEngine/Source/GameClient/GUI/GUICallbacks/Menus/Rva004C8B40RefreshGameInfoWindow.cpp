// cl: /O2 /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Opaque BFME recovery for retail RVA 0x004C8B40.

template <typename T>
class StringBase
{
    friend class AsciiString;
    friend class UnicodeString;
public:
    const T *reverseFind(T c) const throw();
    void set(const StringBase<T> &src);
    void toLower();
private:
    void releaseBuffer();
    struct Header
    {
        int refCount;
        unsigned short length;
        unsigned short capacity;
        T data[1];
    };

    StringBase() : m_data(0) {}
    StringBase(const T *text);
    StringBase(const StringBase<T> &src);
    ~StringBase() {}
    Header *m_data;
};

class AsciiString : private StringBase<char>
{
public:
    AsciiString(const char *text) : StringBase<char>(text) {}
    AsciiString(const AsciiString &src) : StringBase<char>(src) {}
    ~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }

    void toLower() { ((StringBase<char> *)this)->toLower(); }
    const char *reverseFind(char c) const { return ((const StringBase<char> *)this)->reverseFind(c); }
    const char *str() const { return m_data ? &m_data->data[0] : ""; }
};

class UnicodeString : private StringBase<unsigned short>
{
public:
    UnicodeString() : StringBase<unsigned short>() {}
    UnicodeString(const UnicodeString &src) : StringBase<unsigned short>(src) {}
    ~UnicodeString() { ((StringBase<unsigned short> *)this)->releaseBuffer(); }

    void set(const UnicodeString &src)
    {
        ((StringBase<unsigned short> *)this)->set(
            *(const StringBase<unsigned short> *)&src);
    }

    void translate(const AsciiString &src);
};

class Image;
class ImageCollection
{
public:
    const Image *findImageByName(const AsciiString &name);
};

class GameWindow
{
public:
    int winHide(bool hide);
    int winBringToTop();
};

class GameInfo;
class GameSlot
{
public:
    bool isOccupied() const;
    bool isAI() const;
    bool isHuman() const;
    UnicodeString getName() const throw();

    int getState() const { return *(const int *)((const char *)this + 4); }
    int getColor() const { return *(const int *)((const char *)this + 0x0c); }
    int getPlayerTemplate() const { return *(const int *)((const char *)this + 0x14); }
};

class LANGameInfo
{
public:
    UnicodeString getPlayerName(int who);
};

class GameInfo
{
public:
    AsciiString getMap() const;
    GameSlot *getSlot(int slotNum);
};

class Rva00098E70GameInfoView
{
public:
    AsciiString getMap() const throw();
};

#pragma comment(linker, "/alternatename:?getMap@Rva00098E70GameInfoView@@QBE?AVAsciiString@@XZ=?getMap@GameInfo@@QBE?AVAsciiString@@XZ")

struct MapMetaData
{
    UnicodeString m_displayName;
};

struct MapCacheNode
{
    unsigned char m_treeLinks[0x14];
    MapMetaData second;
};

class MapCache
{
public:
    MapCacheNode *bfmeFind(const AsciiString &name);
    MapCacheNode *m_head;
};

class MultiplayerColorDefinition
{
public:
    int getColor() const { return *(const int *)((const char *)this + 0x10); }
};

class MultiplayerSettings
{
public:
    MultiplayerColorDefinition *getColor(int which);

    int getNumColors()
    {
        int *numColors = (int *)((char *)this + 0x3c);
        if (*numColors == 0)
            *numColors = *(int *)((char *)this + 0x34);
        return *numColors;
    }
};

class PlayerTemplate
{
public:
    const Image *getSideIconImage() const;

private:
    unsigned char m_bfmeHead[4];
    unsigned char m_bfmeTail[0x120];
};

class PlayerTemplateStore
{
public:
    const PlayerTemplate *getNthPlayerTemplate(int index) const;

    int getPlayerTemplateCount() const
    {
        return (int)(m_end - m_begin);
    }

private:
    unsigned char m_base[8];
    PlayerTemplate *m_begin;
    PlayerTemplate *m_end;
};

class GameTextInterface
{
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0c();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1c();
    virtual void slot20();
    virtual void slot24();
    virtual UnicodeString fetch(const char *label, bool *exists = 0) throw();
};

extern ImageCollection *TheMappedImageCollection;
extern MapCache *TheMapCache;
extern MultiplayerSettings *TheMultiplayerSettings;
extern GameTextInterface *TheGameText;
extern PlayerTemplateStore *ThePlayerTemplateStore;

extern void *gameInfoWindowLayout;
extern GameWindow *gameInfoWindowParent;
extern GameWindow *gameInfoWindowStaticTextGameName;
extern GameWindow *gameInfoWindowStaticTextMapName;
extern GameWindow *gameInfoWindowListBoxPlayers;
extern const Image *gameInfoWindowRandomIcon;
extern const Image *gameInfoWindowObserverIcon;

void GadgetStaticTextSetText(GameWindow *window, UnicodeString text) throw();
void GadgetListBoxReset(GameWindow *window);
int GadgetListBoxAddEntryText(GameWindow *window, UnicodeString text,
                              int color, int row, int column, bool overwrite) throw();
int GadgetListBoxAddEntryImage(GameWindow *window, const Image *image, int row,
                               int x, int width, int height, bool enabled,
                               int state);

void Rva004C8B40GameInfoWindowRefresh(GameInfo *gameInfo, UnicodeString gameName)
{
    static const Image *randomIcon = TheMappedImageCollection->findImageByName(
        AsciiString("GameinfoRANDOM"));
    static const Image *observerIcon = TheMappedImageCollection->findImageByName(
        AsciiString("GameinfoOBSRVR"));

    if (!gameInfoWindowLayout || !gameInfo)
        return;

    gameInfoWindowParent->winHide(false);
    gameInfoWindowParent->winBringToTop();

    GadgetStaticTextSetText(gameInfoWindowStaticTextGameName,
                            ((LANGameInfo *)gameInfo)->getPlayerName(0));

    UnicodeString map;
    AsciiString asciiMap = gameInfo->getMap();
    asciiMap.toLower();
    MapCache *mapCache = TheMapCache;
    MapCacheNode *it = mapCache->bfmeFind(asciiMap);
    if (it != mapCache->m_head)
    {
        map.set(it->second.m_displayName);
    }
    else
    {
        const char *noPath =
            ((Rva00098E70GameInfoView *)gameInfo)->getMap().reverseFind('\\');
        if (noPath)
        {
            ++noPath;
        }
        else
        {
            noPath = ((Rva00098E70GameInfoView *)gameInfo)->getMap().str();
        }
        map.translate(AsciiString(noPath));
    }
    GadgetStaticTextSetText(gameInfoWindowStaticTextMapName, map);

    GadgetListBoxReset(gameInfoWindowListBoxPlayers);

    int numColors = TheMultiplayerSettings->getNumColors();
    for (int i = 0; i < 8; ++i)
    {
        int playerColor = 0xffffffff;
        int color = -1;
        int addedRow;
        GameSlot *slot = gameInfo->getSlot(i);
        if (!slot || !slot->isOccupied())
            continue;
        color = slot->getColor();
        if (color > -1 && color < numColors)
        {
            MultiplayerColorDefinition *def = TheMultiplayerSettings->getColor(color);
            playerColor = def->getColor();
        }
        if (slot->isAI())
        {
            switch (slot->getState())
            {
            case 2:
                addedRow = GadgetListBoxAddEntryText(
                    gameInfoWindowListBoxPlayers,
                    TheGameText->fetch("GUI:EasyAI"), playerColor, -1, 1, true);
                break;
            case 3:
                addedRow = GadgetListBoxAddEntryText(
                    gameInfoWindowListBoxPlayers,
                    TheGameText->fetch("GUI:MediumAI"), playerColor, -1, 1, true);
                break;
            case 4:
                addedRow = GadgetListBoxAddEntryText(
                    gameInfoWindowListBoxPlayers,
                    TheGameText->fetch("GUI:HardAI"), playerColor, -1, 1, true);
                break;
            default:
                break;
            }
        }
        else if (slot->isHuman())
        {
            addedRow = GadgetListBoxAddEntryText(
                gameInfoWindowListBoxPlayers, slot->getName(), playerColor, -1, 1, true);
        }
        int playerTemplate = slot->getPlayerTemplate();
        if (playerTemplate == -2)
        {
            GadgetListBoxAddEntryImage(gameInfoWindowListBoxPlayers,
                                       observerIcon, addedRow, 0, 22, 25, true, -1);
        }
        else if (playerTemplate < 0 ||
                 playerTemplate >= ThePlayerTemplateStore->getPlayerTemplateCount())
        {
            GadgetListBoxAddEntryImage(gameInfoWindowListBoxPlayers,
                                       randomIcon, addedRow, 0, 22, 25, true, -1);
        }
        else
        {
            const PlayerTemplate *fact =
                ThePlayerTemplateStore->getNthPlayerTemplate(playerTemplate);
            GadgetListBoxAddEntryImage(gameInfoWindowListBoxPlayers,
                                       fact->getSideIconImage(), addedRow,
                                       0, 22, 25, true, -1);
        }
    }
}
