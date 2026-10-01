// ?scriptPlayers002EE4B0Set295@@YGXH@Z
class ScriptEngine { public: int resolvePlayerMask(int param, int flag); };
extern ScriptEngine* TheScriptEngine;
struct Rva002EE330Player { char m_pad[0x294]; unsigned char m_flag294; unsigned char m_flag295;  };
struct Rva002EE330PlayerList { Rva002EE330Player* nextFromMask(unsigned short* mask); };
class PlayerList;
extern PlayerList* ThePlayerList;
static inline Rva002EE330PlayerList* thePlayersView() { return (Rva002EE330PlayerList*)ThePlayerList; }
void __stdcall scriptPlayers002EE4B0Set295(int param)
{
	param = TheScriptEngine->resolvePlayerMask(param, 0);
	while ((unsigned short)param) {
		Rva002EE330Player* player = thePlayersView()->nextFromMask((unsigned short*)&param);
		if (player)
			player->m_flag295 = 1;
	}
}
