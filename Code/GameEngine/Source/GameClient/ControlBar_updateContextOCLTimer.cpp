// cl: /DNDEBUG /MD /EHsc
// Open-BFME: ControlBar::updateContextOCLTimer, retail 0x004AA980, 188 bytes.
//
// The reference's body with a guard around it: BFME checks that the selected
// drawable actually has an object before doing any of the work, which is what
// puts the function-local static's once-flag inside the test rather than at
// the top.
//
// The divisor is five, not the reference's thirty: the reciprocal multiply by
// 0xCCCCCCCD with a shift of two is a divide by five, and a shift of three
// would be the ten it looks like at a glance.
//
// The layout: the selected drawable at this+0x5C, its object at the drawable's
// +0xFC, and the last displayed second count at this+0x6C. The static key sits
// at 0x012F3624 behind the initialised-once bit at 0x012F3628.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

enum { LOGICFRAMES_PER_SECOND = 5 };

enum NameKeyType { NAMEKEY_INVALID = 0 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);		// ILT 0x0003ADD7
};

extern NameKeyGenerator *TheNameKeyGenerator;			// 0x012ED600

#define NAMEKEY(x) (TheNameKeyGenerator->nameToKey(x))

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/OCLUpdate.h
class OCLUpdate
{
public:
	UnsignedInt getRemainingFrames(void);			// ILT 0x00032AA6
	Real getCountdownPercent(void);				// ILT 0x00047069
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	OCLUpdate *findUpdateModule(NameKeyType key);		// ILT 0x0002AE23
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Drawable.h
class Drawable
{
public:
	Object *getObject(void) { return m_object; }

private:
	char m_slice_pad[0xFC];					// retail this+0x00 .. +0xFB, untouched
	Object *m_object;					// this+0xFC
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class ControlBar
{
private:
	void updateContextOCLTimer(void);
	void updateOCLTimerTextDisplay(UnsignedInt secondsLeft, Real percentDone);	// ILT 0x00029839

	char m_slice_pad[0x5C];					// retail this+0x00 .. +0x5B, untouched
	Drawable *m_currentSelectedDrawable;			// this+0x5C
	char m_slice_padB[0x6C - 0x60];				// this+0x60 .. +0x6B, untouched
	UnsignedInt m_displayedOCLTimerSeconds;			// this+0x6C
};

void ControlBar::updateContextOCLTimer( void )
{
	Object *obj = m_currentSelectedDrawable->getObject();

	if( obj )
	{
		static const NameKeyType key_OCLUpdate = NAMEKEY( "OCLUpdate" );
		OCLUpdate *update = (OCLUpdate*)obj->findUpdateModule( key_OCLUpdate );

		UnsignedInt frames = update->getRemainingFrames();
		UnsignedInt seconds = frames / LOGICFRAMES_PER_SECOND;

		Real percent = update->getCountdownPercent();

		// if the time has changed since what was last shown to the user update the text
		if( m_displayedOCLTimerSeconds != seconds )
			updateOCLTimerTextDisplay( seconds, percent );
	}

}  // end updatecontextUnderConstruction
