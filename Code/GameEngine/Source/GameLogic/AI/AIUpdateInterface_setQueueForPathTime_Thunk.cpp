// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: AIUpdateInterface::setQueueForPathTime, retail 0x0026ECA0.
//
// The Zero Hour body unchanged, with SLEEPY_AI on. It is here rather than in
// Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp -- which carries
// the real body and 34 matched rows -- because that TU compiles it to within
// two operands of retail and both are class offsets its shim gets wrong:
//
//     target:   8a 86 30 03 00 00     mov al,[esi+0x330]     m_isInUpdate
//     AIUpdate: 8a 86 16 02 00 00     mov al,[esi+0x216]
//     target:   8b 46 08              mov eax,[esi+0x08]     getObject()
//     AIUpdate: 8b 46 0c              mov eax,[esi+0x0c]
//
// Nothing else in the 83 bytes differs. Correcting either one means editing
// reference/shims/aiupdatelayout, which is compiled into that whole TU: the
// m_isInUpdate delta is 0x11a bytes of missing members spread through a class
// this tree has not reconstructed, and m_obj at +0x08 comes from the real
// UpdateModule/Module headers, so moving it moves every module class in the
// tree. Both are worth doing and neither is this function's job.
//
// The +0x08 reading is independently confirmed: AIUpdateInterface::privateGetHealed
// at 0x0027DE10 loads getObject() from the same slot and byte-verifies.
//
// TheGameLogic is retail 0x012F0898 and getFrame() inlines to its +0x3c.

class Object;

enum UpdateSleepTime
{
	UPDATE_SLEEP_INVALID	= 0,
	UPDATE_SLEEP_NONE		= 1,				// retail: cmp edi,1 / jl
	UPDATE_SLEEP_FOREVER	= 0x3fffffff
};

#define UPDATE_SLEEP(numFrames)				((UpdateSleepTime)(numFrames))

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	unsigned int getFrame( void ) const { return m_frame; }

private:
	char m_unreconstructed_00[0x3c];
	unsigned int m_frame;						///< retail this+0x3c
};

extern GameLogic *TheGameLogic;					///< retail 0x012F0898

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandInterface
{
private:
	char m_unreconstructed_00[4];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule
{
public:
	// Undefined: it exists so the vptr occupies +0x00.
	virtual ~UpdateModule();

	Object *getObject( void ) const { return m_obj; }

protected:
	UpdateSleepTime getWakeFrame( void ) const;								///< ILT 0x000176C5
	void setWakeFrame( Object *obj, UpdateSleepTime whenToWakeUp );			///< ILT 0x000157DA -> 0x002B2040

	char m_unreconstructed_04[4];
	Object *m_obj;								///< retail this+0x08
	char m_unreconstructed_0c[0x20 - 0x0c];		///< brings UpdateModule to 0x20
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface : public UpdateModule, public AICommandInterface
{
public:
	void setQueueForPathTime( int frames );

private:
	char m_unreconstructed_24[0x17c - 0x24];
	int m_queueForPathFrame;					///< retail this+0x17c
	char m_unreconstructed_180[0x330 - 0x180];
	bool m_isInUpdate;							///< retail this+0x330
};

// ?setQueueForPathTime@AIUpdateInterface@@QAEXH@Z
void AIUpdateInterface::setQueueForPathTime( int frames )
{
	if (frames >= UPDATE_SLEEP_NONE && getWakeFrame() > UPDATE_SLEEP(frames))
	{
		if (m_isInUpdate)
		{
			// we're changing this while in our own update (probably via a move state).
			// just do nothing, since update will calculate the correct sleep behavior at the end.
		}
		else
		{
			setWakeFrame(getObject(), UPDATE_SLEEP(frames));
		}
	}
	m_queueForPathFrame = frames ? (TheGameLogic->getFrame() + frames) : 0;
}
