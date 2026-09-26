// ?scriptPlayers002F07A0Set298@@YGXHH@Z
class ScriptEngine { public: int resolvePlayerMask(int param, int flag); };
extern ScriptEngine* TheScriptEngine;
struct Rva002EE330Player { char m_pad[0x298]; int m_value298; };
struct Rva002EE330PlayerList { Rva002EE330Player* nextFromMask(unsigned short* mask); };
extern Rva002EE330PlayerList* Rva002EE330ThePlayers;
void __stdcall scriptPlayers002F07A0Set298(int param, volatile int value)
{
	param = TheScriptEngine->resolvePlayerMask(param, 0);
	while ((unsigned short)param) {
		Rva002EE330Player* player = Rva002EE330ThePlayers->nextFromMask((unsigned short*)&param);
		if (player)
			player->m_value298 = value;
	}
}
