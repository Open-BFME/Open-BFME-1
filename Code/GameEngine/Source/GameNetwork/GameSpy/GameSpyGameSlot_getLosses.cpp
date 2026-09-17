// cl: /DNDEBUG /DWIN32 /MD

// The reference StagingRoomGameInfo.h declares getLosses inline on
// GameSpyGameSlot.  The retail constructor stores m_losses at +0x5c, and the
// adjacent setFavoriteSide body stores m_favoriteSide at +0x60.

typedef int Int;

class GameSpyGameSlot
{
public:
	Int getLosses(void) const;

private:
	unsigned char m_body[0x5c];
	Int m_losses;
};

// Retail RVA 0x006370B0.
Int GameSpyGameSlot::getLosses(void) const
{
	return m_losses;
}
