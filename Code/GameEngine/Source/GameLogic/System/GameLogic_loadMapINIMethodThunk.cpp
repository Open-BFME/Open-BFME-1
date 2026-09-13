// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringbaseascii /ICode/Libraries/Source/WWVegas/WWLib
// Retail implementation of ?loadMapINI@GameLogic@@QAEXVAsciiString@@@Z.
// The readable reference implementation is in GameLogic/System/GameLogic.cpp;
// this facade supplies only the recovered ABI/layout needed by this retail TU.

/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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

static inline void loadMapINIYieldToOS()
{
    Sleep(0);
    if (TheGameEngine)
        TheGameEngine->serviceWindowsOS();
}

class MapCache;
extern MapCache *TheMapCache;

struct SaveGameInfo
{
    AsciiString saveGameMapName;
    AsciiString pristineMapName;
};

class GameState
{
public:
    bool isInSaveDirectory(const AsciiString &) const;

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

class Xfer;

enum INILoadType
{
    INI_LOAD_INVALID = 0,
    INI_LOAD_OVERWRITE = 1,
    INI_LOAD_CREATE_OVERRIDES = 2
};

class INI
{
public:
    INI();
    ~INI();
    void load(AsciiString, INILoadType, Xfer *);

private:
    char m_storage[0x848];
};

class __declspec(novtable) GameTextInterface
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
    virtual void initMapStringFile(const AsciiString &) = 0;
};

extern GameTextInterface *TheGameText;

class GameLogic
{
public:
    void loadMapINI(AsciiString);
};

void GameLogic::loadMapINI(AsciiString mapName)
{
    if (!TheMapCache)
        return;

    char filename[260];
    char fullFledgeFilename[260];
    memset(filename, 0, sizeof(filename));
    strcpy(filename, mapName.str());

    loadMapINIYieldToOS();
    if (TheGameState->isInSaveDirectory(filename))
        strcpy(filename, TheGameState->getSaveGameInfo()->pristineMapName.str());

    int length = strlen(filename);
    if (length < 4)
        return;

    char *extension = filename + length - 4;
    while ((extension > filename) && (*extension != '\\') && (*extension != '/'))
        --extension;
    *extension = 0;

    loadMapINIYieldToOS();
    sprintf(fullFledgeFilename, "%s\\map.ini", filename);
    if (TheFileSystem->doesFileExist(fullFledgeFilename))
    {
        INI ini;
        ini.load(AsciiString(fullFledgeFilename), INI_LOAD_CREATE_OVERRIDES, 0);
    }

    loadMapINIYieldToOS();
    sprintf(fullFledgeFilename, "%s\\solo.ini", filename);
    if (TheFileSystem->doesFileExist(fullFledgeFilename))
    {
        INI ini;
        ini.load(AsciiString(fullFledgeFilename), INI_LOAD_CREATE_OVERRIDES, 0);
    }

    loadMapINIYieldToOS();
    sprintf(fullFledgeFilename, "%s\\map.str", filename);
    if (TheFileSystem->doesFileExist(fullFledgeFilename))
        TheGameText->initMapStringFile(fullFledgeFilename);
}
