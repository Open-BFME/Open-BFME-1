// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /game/GameEngine/Include /game/GameEngine/Include/Precompiled /game/Libraries/Source/WWVegas/WWLib
// readable body of ?sendMangledPortNumberToTarget@NAT@@IAEXGPAVGameSlot@@@Z: game/GameEngine/Source/GameNetwork/nat.cpp

class GameSlot;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NAT.h
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
