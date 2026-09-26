// ?scriptPlayers002EE2D0Call11@@YGXH@Z
class ScriptEngine { public: int resolvePlayerMask(int param, int flag); };
extern ScriptEngine* TheScriptEngine;
struct Rva002EE330Player { char m_pad[0x298]; void onScript002EE2D0(int a, int b); };
struct Rva002EE330PlayerList { Rva002EE330Player* nextFromMask(unsigned short* mask); };
extern Rva002EE330PlayerList* Rva002EE330ThePlayers;
void __stdcall scriptPlayers002EE2D0Call11(int param)
{
	param = TheScriptEngine->resolvePlayerMask(param, 0);
	while ((unsigned short)param) {
		Rva002EE330Player* player = Rva002EE330ThePlayers->nextFromMask((unsigned short*)&param);
		if (player)
			player->onScript002EE2D0(1, 1);
	}
}
