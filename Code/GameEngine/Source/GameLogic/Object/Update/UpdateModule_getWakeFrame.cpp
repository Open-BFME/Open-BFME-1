// cl: /DNDEBUG /MD /EHsc
// readable body of ?getWakeFrame@UpdateModule@@IBE?AW4UpdateSleepTime@@XZ: Code/GameEngine/Source/GameLogic/Object/Update/UpdateModule.cpp

// UpdateModule::getWakeFrame, retail 0x002B2020. No calls: the frame counter is
// read straight out of TheGameLogic at +0x3C - the accessor is inlined - and
// compared against the module's own next-call frame at +0x14. A frame already
// due sleeps one frame rather than zero.

typedef unsigned int UnsignedInt;

// A real enum: the decorated name says ?AW4UpdateSleepTime@@, which a typedef
// for UnsignedInt does not produce.
enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	unsigned char m_unmodelled_00[ 0x3C ];
	UnsignedInt m_frame;					// +0x3C
};

extern GameLogic *TheGameLogic;				// 0x012F0898

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule
{
protected:
	UpdateSleepTime getWakeFrame( void ) const;

private:
	unsigned char m_unmodelled_00[ 0x14 ];
	UnsignedInt m_nextCallFrame;			// +0x14
};

// ?getWakeFrame@UpdateModule@@IBE?AW4UpdateSleepTime@@XZ
UpdateSleepTime UpdateModule::getWakeFrame( void ) const
{
	UnsignedInt now = TheGameLogic->m_frame;

	if( m_nextCallFrame > now )
		return (UpdateSleepTime)( m_nextCallFrame - now );

	return UPDATE_SLEEP_NONE;
}
