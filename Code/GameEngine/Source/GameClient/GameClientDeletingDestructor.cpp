// cl: /DNDEBUG /MD /EHsc
// Scalar wrapper 0x00597680 calls GameClient::~GameClient through ILT 0x00025FB8.

class GameClient
{
public:
	virtual ~GameClient();
};

__declspec(noinline) GameClient::~GameClient() {}

void Force_GameClient_Deleting_Destructor(GameClient *client)
{
	delete client;
}
