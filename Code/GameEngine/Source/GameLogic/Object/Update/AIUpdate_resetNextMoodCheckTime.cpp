// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// readable body of ?resetNextMoodCheckTime@AIUpdateInterface@@: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp
// AIUpdateInterface::resetNextMoodCheckTime, retail 0x0026FA00.
//
// Not Zero Hour's unconditional reset: BFME only pushes the deadline out, never
// pulls it in, so the store is guarded by a comparison. The idle-frame count
// comes from TheAI->getAiData() at global+0x14 then data+0x14, the current
// frame from TheGameLogic+0x3C, and the randomly-offset flag is the byte at
// this+0x32A.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char Bool;

#define TRUE 1

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	UnsignedInt getFrame( void ) const { return m_frame; }

	unsigned char m_unreconstructed_00[ 0x3C ];
	UnsignedInt m_frame;								///< retail this+0x3C
};

extern GameLogic *TheGameLogic;							///< retail [0x012F0898]

class AIData
{
public:
	unsigned char m_unreconstructed_00[ 0x14 ];
	UnsignedInt m_forceIdleFramesCount;					///< retail this+0x14
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AI
{
public:
	const AIData *getAiData( void ) const { return m_aiData; }

	unsigned char m_unreconstructed_00[ 0x14 ];
	AIData *m_aiData;									///< retail this+0x14
};

extern AI *TheAI;										///< retail [0x012EF214]

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
public:
	void resetNextMoodCheckTime( void );

private:
	unsigned char m_unreconstructed_00[ 0x1FC ];
	UnsignedInt m_nextMoodCheckTime;					///< retail this+0x1FC
	unsigned char m_unreconstructed_200[ 0x32A - 0x200 ];
	Bool m_randomlyOffsetMoodCheck;						///< retail this+0x32A
};

void AIUpdateInterface::resetNextMoodCheckTime()
{
	UnsignedInt when = TheAI->getAiData()->m_forceIdleFramesCount + TheGameLogic->getFrame();
	if( when > m_nextMoodCheckTime )
		m_nextMoodCheckTime = when;

	// the flag store follows the if in source; MSVC hoists it above the branch and
	// lands it after the pop, which is the whole difference from the other order
	m_randomlyOffsetMoodCheck = TRUE;
}
