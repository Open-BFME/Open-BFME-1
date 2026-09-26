// cl: /DNDEBUG /DWIN32 /MD

// StagingRoomGameInfo.h declares this accessor inline.  The adjacent exact
// setFavoriteSide body at 0x006370C0 stores the same field at this+0x60.

typedef int Int;

class GameSpyGameSlot
{
public:
	Int getFavoriteSide(void) const;

private:
	unsigned char m_body[0x60];
	Int m_favoriteSide;
};

// Retail RVA 0x006370D0.
Int GameSpyGameSlot::getFavoriteSide(void) const
{
	return m_favoriteSide;
}
