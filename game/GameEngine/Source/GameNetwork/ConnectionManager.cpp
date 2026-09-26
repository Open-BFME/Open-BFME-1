// cl: /D_STLP_USE_STATIC_LIB /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/connectionmanager /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
#define _BFME_RETAIL_TREE_INSERT_LAYOUT

#include "PreRTS.h"

#include "GameLogic/GameLogic.h"
#include "GameNetwork/NetCommandMsg.h"
#include "GameNetwork/ConnectionManager.h"

template class std::map<UnsignedShort, UnsignedByte>;

void ConnectionManager::processProgress(NetProgressCommandMsg *msg)
{
	TheGameLogic->processProgress(msg->getPlayerID(), msg->getPercentage());
}

// ?getLocalPlayerID@ConnectionManager@@QAEIXZ
UnsignedInt ConnectionManager::getLocalPlayerID()
{
	return m_localSlot;
}

// ?isPacketRouter@ConnectionManager@@QAE_NXZ
Bool ConnectionManager::isPacketRouter( void )
{
	return m_localSlot == m_packetRouterSlot;
}

// ?isPlayerConnected@ConnectionManager@@QAE_NH@Z
Bool ConnectionManager::isPlayerConnected( Int playerID )
{
	return ( playerID == m_localSlot || (m_connections[playerID] && m_connections[playerID]->m_openSentinel == -1) );
}

// BFME's version bears no resemblance to the reference's, which loops
// sendSingleFrameToPlayer over a frame range. Here it only raises the per-player
// watermark at this+0x12060, and the actual resend is driven separately by
// 0x00664B40. DisconnectManager::processDisconnectFrame is its caller.
// Retail forms the address of BOTH operands and loads through the selected one
// (lea eax,[ecx+eax*4+0x12060] ... lea ecx,[esp+8] ... mov edx,[ecx]; mov [eax],edx).
// BaseType.h's `max` macro cannot produce that under MSVC 7.1: it treats the
// ternary as an rvalue -- binding a reference to it is rejected outright -- so
// whatever BFME calls here is the STL-shaped template that returns const T&.
// Spelled locally because pulling in <algorithm> collides with GameMemory.h's
// placement new. Argument order is fixed by the equal case: retail takes the
// second operand when the two are equal.
template <class T> inline const T &maxRef(const T &a, const T &b) { return a > b ? a : b; }

void ConnectionManager::sendFrameDataToPlayer(UnsignedInt playerID, UnsignedInt startingFrame) {
	if (playerID >= MAX_SLOTS) {
		return;
	}

	m_playerLatestFrame[playerID] = maxRef(m_playerLatestFrame[playerID], startingFrame);
}
