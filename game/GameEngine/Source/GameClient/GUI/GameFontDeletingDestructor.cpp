// cl: /O2

// The exact constructor at 0x004735A0 identifies this 30-byte scalar-deleting
// destructor as the GameFont vtable slot.
class GameFont
{
	public:
	virtual ~GameFont();
};

// The implicit copy constructor (no retail twin) emits the vftable and with
// it ??_G without a second, non-retail copy of the default constructor.
void forceGameFontDeletingDestructor(const GameFont &that)
{
	GameFont value(that);
}
