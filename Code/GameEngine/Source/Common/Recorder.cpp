// cl: /ICode/Libraries/Source/WWVegas/WWLib /DNDEBUG /MD /EHsc
#include "string_base.h"
#include <stdio.h>

extern "C" unsigned int __cdecl strlen(const char *str);

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;

static const char replayExtention[] = ".rep";
static const char lastReplayFileName[] = "00000000";
static const char replayDir[] = "Replays\\";

// TheGameLogic->getFrame() inlines to the frame word at +0x3C of the global,
// same layout as the rest of the family (see DisconnectManager_voteForPlayerDisconnect_Thunk.cpp).
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
    unsigned char m_unreconstructed_00[0x3C];
    UnsignedInt m_frame;                                   ///< retail this+0x3C

    UnsignedInt getFrame(void) const { return m_frame; }
};
extern GameLogic *TheGameLogic;                            ///< retail [0x012F0898]

// Union of possible argument payloads (MessageStream.h); only the size (16
// bytes) matters here since writeToFile passes it through by value.
union GameMessageArgumentType
{
    Int integer;
    float real;
    bool boolean;
    UnsignedInt objectID;
    UnsignedInt drawableID;
    UnsignedInt teamID;
    struct { float x, y, z; } location;
    struct { Int x, y; } pixel;
    struct { Int loX, loY, hiX, hiY; } pixelRegion;
    UnsignedInt timestamp;
    wchar_t wChar;
};

enum GameMessageArgumentDataType
{
    ARGUMENTDATATYPE_INTEGER,
    ARGUMENTDATATYPE_REAL,
    ARGUMENTDATATYPE_BOOLEAN,
    ARGUMENTDATATYPE_OBJECTID,
    ARGUMENTDATATYPE_DRAWABLEID,
    ARGUMENTDATATYPE_TEAMID,
    ARGUMENTDATATYPE_ASCIISTRING,
    ARGUMENTDATATYPE_LOCATION,
    ARGUMENTDATATYPE_PIXEL,
    ARGUMENTDATATYPE_PIXELREGION,
    ARGUMENTDATATYPE_TIMESTAMP,
    ARGUMENTDATATYPE_WIDECHAR,
    ARGUMENTDATATYPE_UNKNOWN = 11
};

// Layout confirmed by NetPacket_readGameMessage.cpp: m_vptr, m_next, m_type, m_argCount.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameMessageParser.h
class GameMessageParserArgumentType
{
public:
    GameMessageParserArgumentType *getNext() { return m_next; }
    GameMessageArgumentDataType getType() { return m_type; }
    Int getArgCount() { return m_argCount; }

    void *m_vptr;
    GameMessageParserArgumentType *m_next;                 ///< retail this+0x04
    GameMessageArgumentDataType m_type;                    ///< retail this+0x08
    Int m_argCount;                                        ///< retail this+0x0C
};

// Ctor body lives at 0x00009836 (GameMessageParserCtorThunk.cpp); the
// deleting destructor is retail's vtable slot 0 (BFME's MemoryPoolObject
// deleteInstance reduces to a plain `delete`, unlike ZH's pooled version --
// see reverse/re_attempts.log for the same drift on other MemoryPoolObjects).
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameMessageParser.h
class GameMessageParser
{
public:
    GameMessageParser(class GameMessage *msg);
    virtual ~GameMessageParser();

    UnsignedByte getNumTypes() const { return (UnsignedByte)m_argTypeCount; }
    GameMessageParserArgumentType *getFirstArgumentType() const { return (GameMessageParserArgumentType *)m_first; }

    void *m_first;                                         ///< retail this+0x04
    void *m_last;                                          ///< retail this+0x08
    Int m_argTypeCount;                                    ///< retail this+0x0C
};

// getType/getPlayerIndex/getArgumentCount are inlined field reads; getArgument
// and getArgumentDataType leave calls in the bytes and are pinned ILT thunks.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MessageStream.h
class GameMessage
{
public:
    typedef Int Type;

    unsigned char m_unreconstructed_00[0x10];
    Type m_type;                                           ///< retail this+0x10
    Int m_playerIndex;                                     ///< retail this+0x14
    UnsignedByte m_argCount;                                ///< retail this+0x18

    Type getType() const { return m_type; }
    Int getPlayerIndex() const { return m_playerIndex; }
    UnsignedByte getArgumentCount() const { return m_argCount; }

    const GameMessageArgumentType *getArgument(Int index) const;      ///< ILT 0x00045AE3
    int getArgumentDataType(Int index);                               ///< ILT 0x0001A3D4
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString {
public:
    AsciiString() { base()->StringBase<char>::StringBase(); }
    AsciiString(const AsciiString &that) { base()->StringBase<char>::StringBase(*that.base()); }
    AsciiString(const char *str) { base()->StringBase<char>::StringBase(str); }
    ~AsciiString() { base()->releaseBuffer(); }

    void concat(const char *str)
    {
        base()->concat(str, strlen(str));
    }

private:
    StringBase<char> *base() { return (StringBase<char> *)this; }
    const StringBase<char> *base() const { return (const StringBase<char> *)this; }

private:
    StringBase<char>::Header *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData {
public:
    AsciiString getPath_UserData() const;
};

extern GlobalData *TheWritableGlobalData;
#define TheGlobalData ((const GlobalData *)TheWritableGlobalData)

enum RecorderModeType {
    RECORDERMODETYPE_RECORD,
    RECORDERMODETYPE_PLAYBACK,
    RECORDERMODETYPE_NONE
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Recorder.h
class RecorderClass {
public:
    char m_pad0[0xc];
    FILE *m_file;                                          ///< retail this+0x0C
    char m_pad1[0x18 - 0xc - 4];
    RecorderModeType m_mode;
    static AsciiString getReplayDir();
    static AsciiString getReplayExtention();
    AsciiString getLastReplayFileName();
    RecorderModeType getMode();

protected:
    void writeToFile(GameMessage *msg);
    void writeArgument(GameMessageArgumentDataType type, GameMessageArgumentType arg);
};

AsciiString RecorderClass::getReplayDir()
{
    const char *dir = replayDir;
    AsciiString tmp = TheGlobalData->getPath_UserData();
    tmp.concat(dir);
    return tmp;
}

AsciiString RecorderClass::getReplayExtention()
{
    return AsciiString(replayExtention);
}

AsciiString RecorderClass::getLastReplayFileName()
{
    return AsciiString(lastReplayFileName);
}

RecorderModeType RecorderClass::getMode()
{
    return m_mode;
}

// ?writeToFile@RecorderClass@@IAEXPAVGameMessage@@@Z
void RecorderClass::writeToFile(GameMessage *msg)
{
    // Write the frame number for this command.
    UnsignedInt frame = TheGameLogic->getFrame();
    fwrite(&frame, sizeof(frame), 1, m_file);

    // Write the command type
    GameMessage::Type type = msg->getType();
    fwrite(&type, sizeof(type), 1, m_file);

    // Write the player index
    Int playerIndex = msg->getPlayerIndex();
    fwrite(&playerIndex, sizeof(playerIndex), 1, m_file);

    GameMessageParser *parser = new GameMessageParser(msg);
    UnsignedByte numTypes = parser->getNumTypes();
    fwrite(&numTypes, sizeof(numTypes), 1, m_file);

    GameMessageParserArgumentType *argType = parser->getFirstArgumentType();
    while (argType != 0) {
        UnsignedByte argT = (UnsignedByte)(argType->getType());
        fwrite(&argT, sizeof(argT), 1, m_file);

        UnsignedByte argTypeCount = (UnsignedByte)(argType->getArgCount());
        fwrite(&argTypeCount, sizeof(argTypeCount), 1, m_file);

        argType = argType->getNext();
    }

    Int numArgs = msg->getArgumentCount();
    for (Int i = 0; i < numArgs; ++i) {
        writeArgument((GameMessageArgumentDataType)msg->getArgumentDataType(i), *(msg->getArgument(i)));
    }

    delete parser;

    fflush(m_file);
}

void RecorderClass::writeArgument(GameMessageArgumentDataType type, GameMessageArgumentType arg)
{
    if (type == ARGUMENTDATATYPE_INTEGER) {
        fwrite(&arg.integer, sizeof(arg.integer), 1, m_file);
    } else if (type == ARGUMENTDATATYPE_REAL) {
        fwrite(&arg.real, sizeof(arg.real), 1, m_file);
    } else if (type == ARGUMENTDATATYPE_BOOLEAN) {
        fwrite(&arg.boolean, sizeof(arg.boolean), 1, m_file);
    } else if (type == ARGUMENTDATATYPE_OBJECTID) {
        fwrite(&arg.objectID, sizeof(arg.objectID), 1, m_file);
    } else if (type == ARGUMENTDATATYPE_DRAWABLEID) {
        fwrite(&arg.drawableID, sizeof(arg.drawableID), 1, m_file);
    } else if (type == ARGUMENTDATATYPE_TEAMID) {
        fwrite(&arg.teamID, sizeof(arg.teamID), 1, m_file);
    } else if (type == ARGUMENTDATATYPE_LOCATION) {
        fwrite(&arg.location, sizeof(arg.location), 1, m_file);
    } else if (type == ARGUMENTDATATYPE_PIXEL) {
        fwrite(&arg.pixel, sizeof(arg.pixel), 1, m_file);
    } else if (type == ARGUMENTDATATYPE_PIXELREGION) {
        fwrite(&arg.pixelRegion, sizeof(arg.pixelRegion), 1, m_file);
    } else if (type == ARGUMENTDATATYPE_TIMESTAMP) {
        fwrite(&arg.timestamp, sizeof(arg.timestamp), 1, m_file);
    } else if (type == ARGUMENTDATATYPE_WIDECHAR) {
        fwrite(&arg.wChar, sizeof(arg.wChar), 1, m_file);
    }
}
