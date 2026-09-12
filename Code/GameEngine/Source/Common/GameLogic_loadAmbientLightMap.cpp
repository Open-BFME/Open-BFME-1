// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringbaseascii /ICode/Libraries/Source/WWVegas/WWLib
// Retail implementation of ?loadAmbientLightMap@GameLogic@@QAEXVAsciiString@@@Z.
// The method prepares the map's ambient-light texture before terrain loading.

#include "Common/AsciiString.h"

#include <stdio.h>
#include <string.h>

typedef unsigned long DWORD;

extern "C" __declspec(dllimport) void __stdcall Sleep(DWORD);

class __declspec(novtable) GameEngine
{
public:
    virtual void slot00() = 0;
    virtual void slot01() = 0;
    virtual void slot02() = 0;
    virtual void slot03() = 0;
    virtual void slot04() = 0;
    virtual void slot05() = 0;
    virtual void slot06() = 0;
    virtual void slot07() = 0;
    virtual void slot08() = 0;
    virtual void slot09() = 0;
    virtual void slot10() = 0;
    virtual void slot11() = 0;
    virtual void slot12() = 0;
    virtual void slot13() = 0;
    virtual void slot14() = 0;
    virtual void slot15() = 0;
    virtual void serviceWindowsOS() = 0;
};

extern GameEngine *TheGameEngine;

static inline void loadAmbientLightMapYieldToOS()
{
    Sleep(0);
    if (TheGameEngine)
        TheGameEngine->serviceWindowsOS();
}

class MapCache;
extern MapCache *TheMapCache;

class GameState
{
public:
    bool isInSaveDirectory(const AsciiString &) const;

    struct SaveGameInfo
    {
        AsciiString saveGameMapName;
        AsciiString pristineMapName;
    };

    SaveGameInfo *getSaveGameInfo()
    {
        return &m_gameInfo;
    }

private:
    char m_unrecovered[0x18];
    SaveGameInfo m_gameInfo;
};

extern GameState *TheGameState;

class FileSystem
{
public:
    bool doesFileExist(const char *) const;
};

extern FileSystem *TheFileSystem;

class TerrainLogicCallTarget
{
public:
    void loadAmbientLightMap(AsciiString);
    void clearAmbientLightMap();
};

class TerrainLogic;
extern TerrainLogic *TheTerrainLogic;

extern void j_00010c8f();
extern void j_00002ae5();

class GameLogic
{
public:
    void loadAmbientLightMap(AsciiString);
};

void GameLogic::loadAmbientLightMap(AsciiString mapName)
{
    if (!TheMapCache)
        return;

    char filename[260];
    char fullFledgeFilename[260];
    memset(filename, 0, sizeof(filename));
    strcpy(filename, mapName.str());

    loadAmbientLightMapYieldToOS();
    if (TheGameState->isInSaveDirectory(filename))
        strcpy(filename, TheGameState->getSaveGameInfo()->pristineMapName.str());

    int length = strlen(filename);
    if (length < 4)
        return;

    char *extension = filename + length - 4;
    while ((extension > filename) && (*extension != '\\') && (*extension != '/'))
        --extension;
    *extension = 0;

    sprintf(fullFledgeFilename, "%s\\ambientlightmap.tga", filename);
    if (TheFileSystem->doesFileExist(fullFledgeFilename))
    {
        typedef void (TerrainLogicCallTarget::*LoadAmbientLightMapCall)(AsciiString);
        union
        {
            void (*generic)();
            LoadAmbientLightMapCall typed;
        } loadAmbientLightMap;
        loadAmbientLightMap.generic = j_00010c8f;
        (reinterpret_cast<TerrainLogicCallTarget *>(TheTerrainLogic)->*
            loadAmbientLightMap.typed)(AsciiString(fullFledgeFilename));
    }
    else
    {
        typedef void (TerrainLogicCallTarget::*ClearAmbientLightMapCall)();
        union
        {
            void (*generic)();
            ClearAmbientLightMapCall typed;
        } clearAmbientLightMap;
        clearAmbientLightMap.generic = j_00002ae5;
        (reinterpret_cast<TerrainLogicCallTarget *>(TheTerrainLogic)->*
            clearAmbientLightMap.typed)();
    }
}
