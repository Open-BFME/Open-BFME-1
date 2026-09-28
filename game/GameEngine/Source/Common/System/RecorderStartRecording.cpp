// cl: /Igame/Libraries/Source/WWVegas/WWLib /MD /EHsc
// RecorderClass 0x0009B6C0: updateRecord's four-int helper. ZH startRecording
// supplies the control-flow draft; all offsets and BFME additions follow retail.
// The terminal ret 0x10 proves the four argument slots; updateRecord at
// 0x0009BFE0 supplies difficulty, mode, rank points and max FPS in that order.
#include "ascii_string.h"
#include "unicode_string.h"
#include <stdio.h>
#include <windows.h>

// Use the canonical string declarations with the inline forwarding bodies
// witnessed here: char destruction -> 0x00887940; wide -> 0x008881D0.
// This retains retail's by-value argument construction and EH state schedule.
template <typename T> inline StringBase<T>::~StringBase() { releaseBuffer(); }
template <typename T> inline const T *StringBase<T>::str() const { return m_data ? m_data->data : (const T*)L""; }
template <typename T> inline int StringBase<T>::getLength() const { return m_data ? m_data->length : 0; }
template <typename T> inline void StringBase<T>::concat(const StringBase<T> &s) { concat(s.str(), s.getLength()); }
inline UnicodeString::UnicodeString() { *(void**)this = 0; }
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short>*)this)->releaseBuffer(); }
inline UnicodeString &UnicodeString::operator=(const UnicodeString &s) { ((StringBase<unsigned short>*)this)->set(*(const StringBase<unsigned short>*)&s); return *this; }

class FileSystem { public: bool createDirectory(AsciiString path); };
extern FileSystem *TheFileSystem;
class GameTextInterface {
public:
    virtual void slot0(); virtual void slot1(); virtual void slot2();
    virtual void slot3(); virtual void slot4(); virtual void slot5();
    virtual void slot6(); virtual void slot7(); virtual void slot8(); virtual void slot9();
    virtual UnicodeString fetch(const char *, bool *exists=0);
};
extern GameTextInterface *TheGameText;
// Preserve the existing callee's ledger spelling (0x000AED00) and four-byte
// returned wide-string layout. No new semantic identity is asserted for it.
class UnicodeStringAL : public UnicodeString {};
class BfmeVersionAL { public: UnicodeStringAL bfmeVersionTextAL(); };
class Version { public: UnicodeString getUnicodeBuildTime(); unsigned int getVersionNumber(); };
extern Version *TheVersion;
int Rva0009B4B0(int, int);
class GlobalData {
public:
    // These BFME offsets were checked with name_oracle; none has a witness.
    char pad000[0xbc8]; unsigned int field0bc8;
    char padbcc[4]; int field0bd0;
    char padbd4[0x11ec-0xbd4]; bool field11ec;
    char pad11ed[3]; int field11f0;
};
extern GlobalData *TheWritableGlobalData;
// Retail compares both address words, unlike the ZH IP-only comparison.
// Keep address-derived field names where name_oracle has only a ZH hint.
class GameSlot { public: char pad000[0x30]; unsigned int field0030; unsigned short field0034; };
class GameInfo {
public:
    virtual void slot0(); virtual void slot1(); virtual void slot2();
    virtual void slot3(); virtual void slot4(); virtual int getLocalSlotNum();
    int field0004; int m_crcInterval;
    char pad00c[0x34-0xc]; unsigned int field0034; unsigned short field0038;
    GameSlot *getSlot(int);
    void setCRCInterval(int n) { m_crcInterval = n < 100 ? n : 100; }
};
class GameSpyStagingRoom : public GameInfo {};
class LANAPI {
public:
    virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
    virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
    virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
    virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
    virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
    virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
    virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
    virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
    virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
    virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
    virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
    virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
    virtual GameInfo *GetMyGame();
};
class NetworkInterface;
extern NetworkInterface *TheNetwork;
extern LANAPI *TheLAN;
extern GameSpyStagingRoom *TheGameSpyGame;
extern GameInfo *TheSkirmishGameInfo;
extern int OpenBFME5_netCRCInterval;
AsciiString GameInfoToAsciiString(const GameInfo *, bool=true);

class RecorderClass {
public:
    virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void slot3();
    virtual void reset();
    char pad004[8]; FILE *m_file; AsciiString m_fileName;
    int field0014; int m_mode; int field001c;
    GameInfo m_gameInfo;
    // Constructor sibling proves the embedded replay state spans 0x278 bytes.
    char padGameInfo[0x298-0x20-sizeof(GameInfo)];
    int field0298; int field029c;
    static AsciiString getReplayDir(); static AsciiString getReplayExtention();
    AsciiString getLastReplayFileName();
protected:
    void logGameStart(AsciiString);
    void Rva0009B6C0RecorderStart(int difficulty, int gameMode, int rankPoints, int maxFPS);
};

void RecorderClass::Rva0009B6C0RecorderStart(int difficulty, int gameMode, int rankPoints, int maxFPS)
{
    reset();
    m_mode = 0;
    AsciiString filepath = getReplayDir();
    TheFileSystem->createDirectory(filepath);
    m_fileName = getLastReplayFileName();
    m_fileName.concat(getReplayExtention());
    filepath.concat(m_fileName);
    m_file = fopen(filepath.str(), "w+b");
    if (!m_file) return;
    fprintf(m_file, "BFMEREPL");
    unsigned int t=0;
    fwrite(&t,4,1,m_file); fwrite(&t,4,1,m_file);
    unsigned int frames=0;
    fwrite(&frames,4,1,m_file);
    fwrite(&field0298,4,1,m_file); fwrite(&field029c,4,1,m_file);
    bool b=false;
    fwrite(&b,1,1,m_file);
    for (int i=0;i<8;++i) fwrite(&b,1,1,m_file);
    UnicodeString replayName;
    replayName = TheGameText->fetch("GUI:LastReplay");
    fwprintf(m_file,L"%ws",replayName.str()); fputwc(0,m_file);
    SYSTEMTIME systemTime;
    GetLocalTime(&systemTime); fwrite(&systemTime,sizeof(systemTime),1,m_file);
    UnicodeStringAL versionString=((BfmeVersionAL*)TheVersion)->bfmeVersionTextAL();
    UnicodeString versionTimeString=TheVersion->getUnicodeBuildTime();
    unsigned int versionNumber=TheVersion->getVersionNumber();
    fwprintf(m_file,L"%ws",versionString.str()); fputwc(0,m_file);
    fwprintf(m_file,L"%ws",versionTimeString.str()); fputwc(0,m_file);
    fwrite(&versionNumber,4,1,m_file);
    int value=Rva0009B4B0(TheWritableGlobalData->field0bd0,TheWritableGlobalData->field0bd0);
    fwrite(&value,4,1,m_file);
    fwrite(&TheWritableGlobalData->field0bc8,4,1,m_file);
    fwrite(&TheWritableGlobalData->field11ec,1,1,m_file);
    fwrite(&TheWritableGlobalData->field11f0,4,1,m_file);
    fpos_t position;
    fgetpos(m_file,&position);
    AsciiString theSlotList;
    int localIndex=-1;
    if (TheNetwork) {
        if (TheLAN) {
            GameInfo *game=TheLAN->GetMyGame();
            theSlotList=GameInfoToAsciiString(game);
            for (int i=0;i<8;++i) {
                GameSlot *slot=game->getSlot(i);
                if (game->field0034==slot->field0030 && game->field0038==slot->field0034) { localIndex=i; break; }
            }
        } else {
            theSlotList=GameInfoToAsciiString(TheGameSpyGame);
            localIndex=TheGameSpyGame->getLocalSlotNum();
        }
    } else {
        if (TheSkirmishGameInfo) {
            TheSkirmishGameInfo->setCRCInterval(OpenBFME5_netCRCInterval);
            theSlotList=GameInfoToAsciiString(TheSkirmishGameInfo);
            localIndex=0;
        } else {
            m_gameInfo.setCRCInterval(OpenBFME5_netCRCInterval);
            theSlotList=GameInfoToAsciiString(&m_gameInfo);
        }
    }
    logGameStart(theSlotList);
    fwrite(theSlotList.str(),theSlotList.getLength()+1,1,m_file);
    fprintf(m_file,"%d",localIndex); fputc(0,m_file);
    fwrite(&difficulty,4,1,m_file); fwrite(&gameMode,4,1,m_file);
    fwrite(&rankPoints,4,1,m_file); fwrite(&maxFPS,4,1,m_file);
}
