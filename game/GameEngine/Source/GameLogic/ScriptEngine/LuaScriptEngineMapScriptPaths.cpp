// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Reconstructs the Lua script path loader at retail RVA 0x002ECF40.

#include "ascii_string.h"
template <> inline bool StringBase<char>::isNotEmpty() const { return m_data != 0 && m_data->length != 0; }
#include <string.h>
#include <stdio.h>

class GameState
{
public:
    bool isInSaveDirectory(const AsciiString &path) const;
};

struct Rva002ECF40GameStateView
{
    char m_unknown00[0x1c];
    AsciiString m_pristineMapName;
};

class FileSystem
{
public:
    bool doesFileExist(const char *filename) const;
};

class Rva002E55C0LuaHost
{
public:
    void loadFile(const char *filename);
};

class LuaScriptEngine
{
public:
    void rva002ECF40(const AsciiString &mapName);
    void rva002EC990RegisterScriptFunctions();
    void rva002EC840ParseTokenFile(const char *filename, bool keepOpen);
};

extern GameState *TheGameState;
extern FileSystem *TheFileSystem;

// ?rva002ECF40@LuaScriptEngine@@QAEXABVAsciiString@@@Z
void LuaScriptEngine::rva002ECF40(const AsciiString &mapName)
{
    rva002EC990RegisterScriptFunctions();
    if (mapName.isNotEmpty())
    {
        char mapPath[260];
        memset(mapPath, 0, sizeof(mapPath));
        strcpy(mapPath, mapName.str());
        if (TheGameState && TheGameState->isInSaveDirectory(AsciiString(mapPath)))
            strcpy(mapPath, reinterpret_cast<Rva002ECF40GameStateView *>(TheGameState)->m_pristineMapName.str());
        int length = (int)strlen(mapPath);
        if (length < 4)
            return;
        char *end = mapPath + length - 4;
        while (end > mapPath && *end != '\\' && *end != '/')
            --end;
        *end = 0;
        char scriptPath[260];
        sprintf(scriptPath, "%s\\Scripts.lua", mapPath);
        if (TheFileSystem->doesFileExist(scriptPath))
            reinterpret_cast<Rva002E55C0LuaHost *>(this)->loadFile(scriptPath);
        sprintf(scriptPath, "%s\\ScriptEvents.xml", mapPath);
        if (TheFileSystem->doesFileExist(scriptPath))
            rva002EC840ParseTokenFile(scriptPath, true);
    }
}
