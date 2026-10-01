// ?scriptPlayers002EE2D0Call11@@YGXH@Z
class ScriptEngine { public: int resolvePlayerMask(int param, int flag); };
extern ScriptEngine* TheScriptEngine;
struct Rva002EE330Player { char m_pad[0x298]; void onScript002EE2D0(int a, int b); };
struct Rva002EE330PlayerList { Rva002EE330Player* nextFromMask(unsigned short* mask); };
// ThePlayerList (retail 0x012ED748) is PlayerList*; keep the local view, cast at the use.
class PlayerList;
extern PlayerList* ThePlayerList;
void __stdcall scriptPlayers002EE2D0Call11(int param)
{
	param = TheScriptEngine->resolvePlayerMask(param, 0);
	while ((unsigned short)param) {
		Rva002EE330Player* player = ((Rva002EE330PlayerList*)ThePlayerList)->nextFromMask((unsigned short*)&param);
		if (player)
			player->onScript002EE2D0(1, 1);
	}
}
