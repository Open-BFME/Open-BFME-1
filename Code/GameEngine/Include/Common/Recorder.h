#pragma once

#include "ascii_string.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData {
public:
    AsciiString getPath_UserData() const;
};

extern GlobalData *TheWritableGlobalData;
#define TheGlobalData ((const GlobalData *)TheWritableGlobalData)

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Recorder.h
class RecorderClass {
public:
    static AsciiString getReplayDir();
    static AsciiString getReplayExtention();
    AsciiString getLastReplayFileName();
};
