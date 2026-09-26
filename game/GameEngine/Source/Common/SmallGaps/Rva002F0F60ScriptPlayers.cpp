// ?scriptPlayers002F0F60Apply@@YGXPAURva002F0F60Script@@H@Z
class ScriptEngine { public: int resolvePlayerMask(void* param, int flag); };
extern ScriptEngine* TheScriptEngine;
struct Rva002F0F60Script { char m_pad[0x10]; int m_param; };
struct Rva002F0F60Arg { int m_0; int m_4; int m_value; };
struct Rva002EE330Sub { void apply(int value); };
struct Rva002EE330Player { char m_pad[0x30]; Rva002EE330Sub m_sub; };
struct Rva002EE330PlayerList { Rva002EE330Player* nextFromMask(unsigned short* mask); };
extern Rva002EE330PlayerList* Rva002EE330ThePlayers;
void __stdcall scriptPlayers002F0F60Apply(Rva002F0F60Script* script, int arg)
{
	int value = ((Rva002F0F60Arg*)arg)->m_value;
	arg = TheScriptEngine->resolvePlayerMask(&script->m_param, 0);
	while ((unsigned short)arg) {
		Rva002EE330Player* player = Rva002EE330ThePlayers->nextFromMask((unsigned short*)&arg);
		if (player)
			player->m_sub.apply(value);
	}
}
