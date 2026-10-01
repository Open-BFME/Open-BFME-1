// ?scriptPlayers002F0020Set@@YGXHH@Z
class ScriptEngine { public: int resolvePlayerMask(int param, int flag); };
extern ScriptEngine* TheScriptEngine;
struct Rva002EE330Player { char m_pad[0x258]; int m_value258; void onScript002F0020A(int value); void onScript002F0020B(int value); };
struct Rva002EE330PlayerList { Rva002EE330Player* nextFromMask(unsigned short* mask); };
// ?ThePlayerList@@3PAVPlayerList@@A -- retail 0x012ED748, defined once in
// Common/RTS/PlayerList.cpp. The view above is this TU's own layout of it.
class PlayerList;
extern PlayerList *ThePlayerList;
void __stdcall scriptPlayers002F0020Set(int param, int value)
{
	param = TheScriptEngine->resolvePlayerMask(param, 0);
	while ((unsigned short)param) {
		Rva002EE330Player* player = ((Rva002EE330PlayerList*)ThePlayerList)->nextFromMask((unsigned short*)&param);
		if (player) {
			player->onScript002F0020A(value);
			player->onScript002F0020B(player->m_value258);
		}
	}
}
