// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/gamewindow /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad

// stlport
// Retail 0x0045DD90 updates two float pairs and applies them to a GameWindow.
// Its two callers pass three stack arguments and clean up 12 bytes. Neither
// caller proves an owning class, so the function and record retain the RVA.
// See reverse/identity_evidence/0x0045dd90-coordinate-pairs.md.
#include "GameClient/GameWindow.h"

struct Rva0045DD90FloatPair
{
    float x;
    float y;
};

struct Rva0045DD90Record
{
    char m_padding[0x10];
    GameWindow *m_window;
    Rva0045DD90FloatPair m_position;
    Rva0045DD90FloatPair m_size;
};

extern "C" void __cdecl rva0045DD90UpdateCoordinatePairs(
    Rva0045DD90Record *record, const Rva0045DD90FloatPair *position,
    const Rva0045DD90FloatPair *size)
{
    if (position->x != record->m_position.x ||
        position->y != record->m_position.y)
    {
        record->m_position = *position;
        if (record->m_window)
            record->m_window->winSetPosition((int)position->x, (int)position->y);
    }

    if (size->x != record->m_size.x || size->y != record->m_size.y)
    {
        record->m_size = *size;
        if (record->m_window)
            record->m_window->winSetSize((int)size->x, (int)size->y);
    }
}
