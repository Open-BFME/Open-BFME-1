// cl: /DNDEBUG /MD /EHsc
// stlport
//
// Open-BFME5: GameMessageParser scalar-deleting destructor at retail RVA
// 0x006235B0 (30 bytes). The exact default/message constructors at
// 0x00623510/0x006236D0, the matched protected complete destructor at
// 0x00623530, and the parser's network call sites establish this identity.

class GameMessageParser
{
public:
	static void forceDeletingDestructor();
	virtual ~GameMessageParser();
};

void GameMessageParser::forceDeletingDestructor()
{
	GameMessageParser value;
}
