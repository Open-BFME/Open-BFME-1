// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/disconnectmanager /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main

typedef bool Bool;
typedef int Int;
class ConnectionManager;

class DisconnectManager
{
protected:
	Bool isPlayerVotedOut( Int slot, ConnectionManager *connectionManager );
};

class DisconnectManagerIsPlayerVotedOutThunk : public DisconnectManager
{
public:
	Bool isPlayerVotedOutThunk( Int slot, ConnectionManager *connectionManager );
};

Bool DisconnectManagerIsPlayerVotedOutThunk::isPlayerVotedOutThunk(
	Int slot, ConnectionManager *connectionManager )
{
	return DisconnectManager::isPlayerVotedOut( slot, connectionManager );
}
