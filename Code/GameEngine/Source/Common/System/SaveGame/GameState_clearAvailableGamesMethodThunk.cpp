// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/shims/campaignmanagerascii /ICode/Libraries/Source/WWVegas/WWLib
// Open-BFME5: exact C++ reconstruction of the retail scratch-save cleanup body.

#include "Common/AsciiString.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameState.h
class GameState
{
public:
    AsciiString getFilePathInSaveDirectory(const AsciiString &leaf) const;

private:
    void deleteScratchSaveFile();
};

extern GameState *TheGameState;
extern "C" __declspec(dllimport) int __stdcall DeleteFileA(const char *fileName);

void GameState::deleteScratchSaveFile()
{
    AsciiString fileName = TheGameState->getFilePathInSaveDirectory(AsciiString("00000000.sav"));
    const char *text = *(const char **)&fileName;
    DeleteFileA(text ? text + 8 : "");
}
