// cl: /DNDEBUG /MD /EHsc
// readable body of ?setEvaEnabled@Eva@@: Code/GameEngine/Source/GameClient/Eva.cpp
// Open-BFME5: Eva::setEvaEnabled, spelled against the retail BFME layout.
//
// BFME's Eva is not Zero Hour's.  Retail keeps one 24-byte per-message check
// record in a vector at +0x4c/+0x50 and a single enable flag at +0x5c, and the
// setter is a no-op when the flag would not change -- none of which the
// GameClient/Eva.h in the reference tree describes.  Spelling the class locally
// in its own translation unit keeps the drift out of a shared header (AGENTS.md,
// "Placement and integrity").
//
// Identity evidence: the body's single caller reaches it as
// `mov ecx, [TheEva]; jmp <here>` at 0x002F05D0, TheEva being the 0x012F142C
// global that the matched ?parseMiscEvaData@INI@@ also loads; the +0x5c byte it
// writes is the same one Eva::reset (0x004267D0) and the Eva constructor
// (0x004271B0) stamp TRUE.

typedef bool Bool;

// Retail per-message check record: 24 bytes, the frame stamp this body
// invalidates living at +0x04.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Eva.h
struct EvaCheck
{
	float m_triggeredOnFrame;
	float m_timeForNextCheck;
	char  m_rest[ 0x10 ];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Eva.h
class Eva
{
public:
	void setEvaEnabled( Bool enabled );

private:
	char       m_head[ 0x4c ];
	EvaCheck  *m_checksBegin;		// +0x4c
	EvaCheck  *m_checksEnd;			// +0x50
	char       m_tail[ 0x08 ];		// +0x54 .. +0x5b
	Bool       m_enabled;			// +0x5c
};

void Eva::setEvaEnabled( Bool enabled )
{
	// Retail bails before the store when nothing changes.
	if( enabled == m_enabled )
		return;

	// Going dark invalidates every pending check so nothing fires on re-enable.
	if( !enabled )
	{
		EvaCheck *check = m_checksBegin;
		EvaCheck *last = m_checksEnd;
		while( check != last )
		{
			check->m_timeForNextCheck = -1.0f;
			++check;
		}
	}

	m_enabled = enabled;
}
