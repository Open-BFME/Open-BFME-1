// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /game/Libraries/Source/WWVegas/WWLib
// readable body of ?populateObserverList@ControlBar@@QAEXXZ: game/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarObserver.cpp

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class ControlBar
{
public:
    void populateObserverList();
};

class ControlBarPopulateObserverListShim
{
public:
    void populate();
};

void ControlBar::populateObserverList()
{
    ((ControlBarPopulateObserverListShim *)this)->populate();
}
