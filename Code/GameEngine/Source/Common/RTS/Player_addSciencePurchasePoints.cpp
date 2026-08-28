// cl: /DNDEBUG /MD /EHsc
// readable body of ?addSciencePurchasePoints@Player@@QAEXH@Z: Code/GameEngine/Source/Common/RTS/Player.cpp

// Player::addSciencePurchasePoints, retail 0x000C9960. Zero Hour's body with
// one BFME statement in front of it: points EARNED, as opposed to spent, are
// also recorded on the subobject at +0x348 before the running total moves.
//
// The rest is Zero Hour unchanged - remember the old total, add, clamp at zero,
// and tell the control bar only when the value actually moved and the bar
// exists. Retail keeps the old value in the register it loaded it into and
// compares against the member afterwards rather than against the sum, which is
// what re-reading m_sciencePurchasePoints in the comparison compiles to.
//
// Both callees are unnamed bodies. The recorder gets a _bfme_ name for the
// shape the call site proves; the control bar method keeps Zero Hour's name for
// the same call.

typedef int Int;

class Player;

class BfmeAcademyPointRecorder
{
public:
	void _bfme_recordPointsEarned( Int points );	// ILT thunk at 0x0001B969
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class ControlBar
{
public:
	void onPlayerSciencePurchasePointsChanged( Player *player );	// ILT thunk at 0x000439D7
};

extern ControlBar *TheControlBar;					// 0x012F33F8

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	void addSciencePurchasePoints( Int delta );

private:
	unsigned char m_unmodelled_000[ 0x264 ];
	Int m_sciencePurchasePoints;					// +0x264
	unsigned char m_unmodelled_268[ 0x348 - 0x268 ];
	BfmeAcademyPointRecorder m_pointRecorder;		// +0x348
};

// ?addSciencePurchasePoints@Player@@QAEXH@Z
void Player::addSciencePurchasePoints( Int delta )
{
	if( delta > 0 )
		m_pointRecorder._bfme_recordPointsEarned( delta );

	Int oldSPP = m_sciencePurchasePoints;
	m_sciencePurchasePoints += delta;
	if( m_sciencePurchasePoints < 0 )
		m_sciencePurchasePoints = 0;

	if( oldSPP != m_sciencePurchasePoints && TheControlBar != 0 )
		TheControlBar->onPlayerSciencePurchasePointsChanged( this );
}
