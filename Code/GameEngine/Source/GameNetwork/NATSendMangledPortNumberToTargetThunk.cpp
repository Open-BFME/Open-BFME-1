// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /Code/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib
// readable body of ?sendMangledPortNumberToTarget@NAT@@IAEXGPAVGameSlot@@@Z: Code/GameEngine/Source/GameNetwork/nat.cpp

class GameSlot;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NAT.h
class NAT
{
protected:
    void sendMangledPortNumberToTarget(unsigned short mangledPort, GameSlot *targetSlot);
};

class NATSendMangledPortShim
{
public:
    void send(unsigned short mangledPort, GameSlot *targetSlot);
};

void NAT::sendMangledPortNumberToTarget(unsigned short mangledPort, GameSlot *targetSlot)
{
    ((NATSendMangledPortShim *)this)->send(mangledPort, targetSlot);
}
