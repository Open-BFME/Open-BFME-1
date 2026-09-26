// ?bfme_reportDesync@GameLogic@@QAEXPAVBfmeByteStream@@IH@Z
// partial score=0.82 date=2026-09-07
// cl: /DNDEBUG /MD /EHsc
// BANKED, NOT BYTE-EXACT: 1746 compiled bytes vs retail 1744.
// Real caller processLogicCRC pushes player, frame, stream and thiscall target
// 0x00388C10 returns ret 12 at 0x003892DD. The old no-argument pin was wrong.
// The third player argument is unused in this body. All control-flow paths were
// transcribed from retail; no new safety/fallback behavior has been introduced.
//
// Direct helper identities/routes for the next conversion pass:
// Recorder::bfmeFlushReplayHeader -> ILT 0x000365D4 -> 0x000971B0 (updates the
// recording header with frame/seed and flushes it); getMode -> 0x00043EEB.
// bfmeShowDesyncDialog -> 0x00020B21 -> 0x00522DD0; this forwards three args
// plus an empty callback object to its four-argument dialog implementation.
// BfmeByteStream::takeBuffer -> 0x009CB1F0; createMemoryReadFile -> 0x009CB470.
// bfmeDesyncDetail -> 0x00043072 -> 0x00387D90 (returns an AsciiString ref).
// Recorder::bfmeDumpFrame -> 0x0000D9B8 -> 0x0009A580.
// _bfme_dumpXferStream -> 0x009D9D90; output openFile -> 0x009C8860.
// TheFileSystem VA0x0134CB48; TheRecorder VA0x012ED62C; ScriptActions
// VA0x012F0620 (closeWindows slot10); GameText VA0x012F147C (fetch slot10);
// unknown UI receiver VA0x012F076C (slot12). GlobalData VA0x012ED5C8,
// map name+8; PlayerList VA0x012ED748, localPlayer+0xC, playerName+0x1C.
// Flags ignoreUnforced/fake/writeBinary at 0x012ED4E8/0x012F4C68/0x012ED4E7;
// forceFrame at 0x012A6F38. GetComputerNameA/free IAT proven at
// 0x01358D60/0x013593D4 from the PE import directory.
//
// Still wrong: stack 0x120 instead of retail0x128, zero-EDI lifetime and
// string/pointer spill allocation. UnicodeString is four bytes; an explicit
// eight-byte hypothesis causes a realigned EBP frame and was rejected.
// Named UnicodeString locals, nesting guards, cursor/pointer declaration order,
// and copied frame locals did not improve the result. A ternary map basename
// version is 1762B; explicit empty-map initial value produces this1746B bank.
// The retail forced-desync format has THREE percent-d conversions but the
// call pushes only TWO data arguments. That observable bug is retained here.
// Binary-output open failure skips buffer free while still destroying strings.

template<class T> struct StringData { int refs; unsigned short length,capacity; T text[1]; };
template<class T> class StringBase {
    friend class AsciiString; friend class UnicodeString;
private:
    StringBase():data(0) {}
    StringBase(const T*);
    StringBase(const StringBase&);
    ~StringBase();
    StringData<T>*data;
public:
    void set(const StringBase&);
};
class AsciiString:private StringBase<char> {
public:
    AsciiString() {}
    AsciiString(const char*p):StringBase<char>(p) {}
    AsciiString(const AsciiString&v):StringBase<char>(v) {}
    ~AsciiString() {}
    AsciiString& operator=(const char*);
    AsciiString& operator=(const AsciiString&v) {set(v); return *this;}
    void __cdecl format(AsciiString format,...);
    const char*str() const {return data?data->text:"";}
    unsigned int length() const {return data?data->length:0;}
    bool empty() const {return !data||!data->length;}
    const char*reverseFind(char c)const {
        const char*start=data?data->text:"";
        const char*p=start+(data?data->length:0);
        while(p!=start) {--p; if(*p==c)return p;}
        return 0;
    }
};
class UnicodeString:private StringBase<unsigned short> {
public:
    UnicodeString() {}
    UnicodeString(const UnicodeString&v):StringBase<unsigned short>(v) {}
    ~UnicodeString() {}
};
class File {
public:
    virtual void slot0(); virtual void slot1(); virtual void close(); virtual void slot3();
    virtual int write(const void*,int);
};
class BfmeByteStream:public File {
public:
    char *takeBuffer(int*length);
    AsciiString name;
};
class FileSystem {public:File*openFile(const char*,int);};
extern FileSystem*TheFileSystem;
File*createMemoryReadFile(char*,int);
bool _bfme_dumpXferStream(File*,File*);
enum RecorderModeType {MODE_RECORD=1};
class RecorderClass {public:void bfmeFlushReplayHeader(); RecorderModeType getMode(); void bfmeDumpFrame(File*,unsigned);};
extern RecorderClass*TheRecorder;
class ScriptActions {
public:
    virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void slot3(); virtual void slot4();
    virtual void slot5(); virtual void slot6(); virtual void slot7(); virtual void slot8(); virtual void slot9();
    virtual void closeWindows(bool);
};
extern ScriptActions*TheScriptActions;
class GameText {
public:
    virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void slot3(); virtual void slot4();
    virtual void slot5(); virtual void slot6(); virtual void slot7(); virtual void slot8(); virtual void slot9();
    virtual UnicodeString fetch(const char*,bool*);
};
extern GameText*TheGameText;
extern void __cdecl bfmeMakeZB(void*,void*,void*);
__forceinline void bfmeShowDesyncDialog(int code,const UnicodeString&first,const UnicodeString&second)
{
    bfmeMakeZB((void*)code,(void*)&first,(void*)&second);
}
class DesyncUI {
public:
    virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void slot3(); virtual void slot4();
    virtual void slot5(); virtual void slot6(); virtual void slot7(); virtual void slot8(); virtual void slot9();
    virtual void slot10(); virtual void slot11(); virtual void onDesync();
};
extern DesyncUI*g_desyncUI;
struct GlobalData {char pad[8];AsciiString mapName;};
extern GlobalData*TheGlobalData;
struct Player {char pad[0x1c];AsciiString name;};
struct PlayerList {char pad[0xc];Player*localPlayer;};
extern PlayerList*ThePlayerList;
extern bool g_ignoreUnforcedDesync,g_fakeDesync,g_writeBinaryDesync;
extern unsigned g_forceDesyncFrame;
extern "C" __declspec(dllimport) int __stdcall GetComputerNameA(char*,unsigned long*);
extern "C" __declspec(dllimport) void __cdecl free(void*);
class GameLogic {
public:
    void bfme_reportDesync(BfmeByteStream*,unsigned,int);
    const AsciiString& bfmeDesyncDetail(unsigned);
    char pad0[0x3c];unsigned currentFrame;
    char pad40[0x10];AsciiString desyncInfo;
    AsciiString *detailsBegin,*detailsEnd,*detailsCapacity;
    AsciiString detailTail, detailEnd;
    char pad68[4];bool sawMismatch;
    char pad6d[0x137];int desyncState;bool dialogShown;
};
void GameLogic::bfme_reportDesync(BfmeByteStream*stream,unsigned frame,int player)
{
    sawMismatch=true;
    if(g_ignoreUnforcedDesync&&g_forceDesyncFrame!=currentFrame)return;
    if(!dialogShown) {
        dialogShown=true;
        TheRecorder->bfmeFlushReplayHeader();
        TheScriptActions->closeWindows(true);
        if(!TheRecorder||TheRecorder->getMode()!=MODE_RECORD||g_forceDesyncFrame==currentFrame)
            bfmeShowDesyncDialog(3,TheGameText->fetch("GUI:DesyncTitle",0),TheGameText->fetch("GUI:DesyncText",0));
        desyncState=0;
        if(!TheRecorder||TheRecorder->getMode()!=MODE_RECORD||g_forceDesyncFrame==currentFrame)
            g_desyncUI->onDesync();
    }
    if(!stream)return;
    const char *map="";
    const char *slash=TheGlobalData->mapName.reverseFind('\\');
    if(slash)map=slash+1;
    AsciiString playerName(ThePlayerList->localPlayer->name);
    if(playerName.empty()) {
        char computerName[256]={0};
        unsigned long len=256;
        GetComputerNameA(computerName,&len);
        playerName=computerName;
    }
    AsciiString frameName;
    if(stream->name.str())frameName.format("Frame%s",stream->name.str());
    else frameName.format("Frame%d",frame);
    AsciiString filename;
    if(frame>0)filename.format("DESYNC-%s-%s-%s.txt",frameName.str(),map,playerName.str());
    else filename.format("DESYNC-%s-%s.txt",map,playerName.str());
    File*output=TheFileSystem->openFile(filename.str(),0x2a);
    if(output) {
        int size;
        char*buffer=stream->takeBuffer(&size);
        File*input=createMemoryReadFile(buffer,size);
        if(input) {
            AsciiString text;
            if(frame>0) {
                if(g_fakeDesync)text.format("*** Frame #%d -- THIS IS A FAKE DESYNC THAT WAS TRIGGERED INTENTIONALLY BY THIS PLAYER! IGNORE!\n\n",frame);
                else if(g_forceDesyncFrame==currentFrame)text.format("*** Frame #%d -- THIS IS A FORCED DESYNC TRIGGERED ON FRAME %d USING COMMANDLINE -forceDesyncOnFrame %d! IGNORE!!!!\n\n",frame,currentFrame);
                else text.format("Frame #%d\n\n",frame);
                output->write(text.str(),text.length());
            }
            text=desyncInfo;output->write(text.str(),text.length());
            for(unsigned i=0;i<(unsigned)(detailsEnd-detailsBegin);++i) {
                text=bfmeDesyncDetail(i);output->write(text.str(),text.length());
            }
            text=detailTail;output->write(text.str(),text.length());
            text=detailEnd;output->write(text.str(),text.length());
            text.format("\n");output->write(text.str(),text.length());
            text.format("\n--------------------------------------------------------\nREPLAY FILE\n---------------------------------------------------------\n");output->write(text.str(),text.length());
            TheRecorder->bfmeDumpFrame(output,frame);
            text.format("---------------------------------------------------------\n\n");output->write(text.str(),text.length());
            _bfme_dumpXferStream(input,output);
            input->close();output->close();
            if(g_writeBinaryDesync) {
                if(frame>0)filename.format("BIN_DESYNC-%s-%s-%s.bin",frameName.str(),map,playerName.str());
                else filename.format("BIN_DESYNC-%s-%s.bin",map,playerName.str());
                output=TheFileSystem->openFile(filename.str(),0x42);
                if(!output)return;
                output->write(buffer,size);output->close();
            }
            free(buffer);
        }
    }
}
