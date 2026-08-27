// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/disconnectmanager /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad

#include "windows.h"

typedef int Int;

class ConnectionManager;

// Retail calls this address directly; the helper loads TheDisconnectMenu and
// creates the BFME DisconnectScreen.apt layout internally.
extern void d_0050e9a0(void);

class DisconnectManager
{
protected:
	void turnOnScreen(ConnectionManager *connectionManager);
	void populateDisconnectScreen(ConnectionManager *connectionManager);
	void resetPlayerTimeouts(ConnectionManager *connectionManager);

private:
	unsigned char m_pad_00_to_0c[0x0c];
	Int m_disconnectState;
	Int m_lastKeepAliveSendTime;
	unsigned char m_pad_14_to_258[0x244];
	Int m_haveNotifiedOtherPlayersOfCurrentFrame;
	Int m_timeOfDisconnectScreenOn;
};

// ?turnOnScreen@DisconnectManager@@IAEXPAVConnectionManager@@@Z
void DisconnectManager::turnOnScreen(ConnectionManager *connectionManager)
{
	d_0050e9a0();
	m_disconnectState = 0;
	m_lastKeepAliveSendTime = -1;
	populateDisconnectScreen(connectionManager);
	resetPlayerTimeouts(connectionManager);
	m_haveNotifiedOtherPlayersOfCurrentFrame = 0;
	m_timeOfDisconnectScreenOn = timeGetTime();
}
