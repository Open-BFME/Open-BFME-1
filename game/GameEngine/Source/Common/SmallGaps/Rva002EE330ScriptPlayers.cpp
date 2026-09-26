// ?scriptPlayers002EE330Call@@YGXH@Z
class ScriptEngine { public: int resolvePlayerMask(int param, int flag); };
extern ScriptEngine* TheScriptEngine;
struct Rva002EE330Player { char m_pad[0x294]; unsigned char m_flag294; unsigned char m_flag295; void onScript002EE330(); };
struct Rva002EE330PlayerList { Rva002EE330Player* nextFromMask(unsigned short* mask); };
extern Rva002EE330PlayerList* Rva002EE330ThePlayers;
void __stdcall scriptPlayers002EE330Call(int param)
{
	param = TheScriptEngine->resolvePlayerMask(param, 0);
	while ((unsigned short)param) {
		Rva002EE330Player* player = Rva002EE330ThePlayers->nextFromMask((unsigned short*)&param);
		if (player)
			player->onScript002EE330();
	}
}
