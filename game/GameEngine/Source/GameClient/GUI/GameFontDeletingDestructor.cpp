// cl: /O2

// The exact constructor at 0x004735A0 identifies this 30-byte scalar-deleting
// destructor as the GameFont vtable slot.
class GameFont
{
	public:
	virtual ~GameFont();
};

void forceGameFontDeletingDestructor()
{
	GameFont value;
}
