// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
// readable body of ?detectionBeginUpdate@FirewallHelperClass@@QAE_NXZ: Code/GameEngine/Source/GameNetwork/FirewallHelper.cpp

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/FirewallHelper.h
class FirewallHelperClass
{
public:
    bool detectionBeginUpdate();
};

class FirewallHelperDetectionBeginUpdateShim
{
public:
    bool begin();
};

bool FirewallHelperClass::detectionBeginUpdate()
{
    return ((FirewallHelperDetectionBeginUpdateShim *)this)->begin();
}
