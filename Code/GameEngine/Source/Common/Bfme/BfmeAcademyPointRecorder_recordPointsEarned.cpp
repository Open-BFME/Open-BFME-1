// cl: /DNDEBUG /MD /EHsc
// Open-BFME: BfmeAcademyPointRecorder::_bfme_recordPointsEarned, retail
// 0x000E88D0, 36 bytes.
//
// One guarded accumulate: the global at 0x012F0898 -- the game logic, the same
// one every frame counter in the image reads -- carries a flag at +0x90, and
// only while it is set do the points land in the running total at this+0x124.

typedef int Int;
typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	unsigned char m_unmodelled_000[0x90];
	Bool m_bfmeRecordingEnabled;				// +0x90
};

extern GameLogic *TheGameLogic;

class BfmeAcademyPointRecorder
{
public:
	void _bfme_recordPointsEarned(Int points);

private:
	unsigned char m_unmodelled_000[0x124];
	Int m_pointsEarned;					// this+0x124
};

void BfmeAcademyPointRecorder::_bfme_recordPointsEarned(Int points)
{
	if (TheGameLogic->m_bfmeRecordingEnabled)
	{
		m_pointsEarned += points;
	}
}
