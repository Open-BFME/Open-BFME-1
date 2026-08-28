// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: GameSlot::disconnected, retail 0x000A3080.
//
// Zero Hour declares it inline in GameInfo.h --
// `Bool disconnected(void) const { return isHuman() && m_disconnected; }` --
// and retail carries an out-of-line copy at this address anyway, which is what
// the row claims. Spelled here as an out-of-line definition so one gets
// emitted; the header's inline form has no address to claim.
//
// The one offset it pins: m_disconnected at +0x40. isHuman() stays a call --
// retail does not inline it either, reaching it through ILT 0x000279CB.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameSlot
{
public:
	bool isHuman(void) const;						///< ILT 0x000279CB
	bool disconnected(void) const;

private:
	char m_unreconstructed_00[0x40];
	bool m_disconnected;							///< retail this+0x40
};

// ?disconnected@GameSlot@@QBE_NXZ
bool GameSlot::disconnected(void) const
{
	return isHuman() && m_disconnected;
}
