// Open-BFME5 conversions.

// TU-local layout view of Player; getAttackedBy is the pinned row at the ILT retail calls
// (0x000C9CA0, bool(int) const at Player+0x29F).
class Player
{
public:
	bool getAttackedBy(int playerIndex) const;
	char m_bfmePad[0x24];
	int m_playerIndex;
};

// 0x012ED748 is retail's PlayerList singleton (game/GameEngine/Source/Common/RTS/PlayerList.cpp
// defines `PlayerList *ThePlayerList`); this view carries the pinned getEachPlayerFromMask row.
class PlayerList
{
public:
	Player *getEachPlayerFromMask(unsigned short &mask);
};

extern PlayerList *ThePlayerList;	// retail [0x012ED748]

class Parameter;

// Retail's ScriptEngine global at 0x012F076C, spelled canonically so this TU
// links against game/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngine.cpp's
// definition; this view carries the pinned player-mask resolver (row 0x0034DB40).
class ScriptEngine
{
public:
	unsigned short unidentified_0034DB40(Parameter *parameter);
};
extern ScriptEngine *TheScriptEngine;

// Retail keeps the resolver's whole EAX (no zero-extension of the 16-bit mask),
// so the row is called through its own symbol with an int result view.
static __forceinline int nextPlayerMask(int parameter)
{
	typedef int (ScriptEngine::*Raw)(Parameter *);
	Raw raw = reinterpret_cast<Raw>(&ScriptEngine::unidentified_0034DB40);
	return (TheScriptEngine->*raw)((Parameter *)parameter);
}

char __stdcall bfmeGo1093A(int a, int b)
{
	int h;

	a = nextPlayerMask(a);
	h = nextPlayerMask(b);
	while ((short)a) {
		Player *r = ThePlayerList->getEachPlayerFromMask(*(unsigned short *)&a);

		if (r) {
			b = h;
			while ((short)b) {
				Player *q = ThePlayerList->getEachPlayerFromMask(*(unsigned short *)&b);

				if (q) {
					int m = q->m_playerIndex;

					if (r->getAttackedBy(m))
						return 1;
				}
			}
		}
	}
	return 0;
}
