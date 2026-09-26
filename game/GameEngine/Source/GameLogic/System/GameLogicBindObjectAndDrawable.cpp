// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// BFME retail 0x003833C0.  The matched StealthUpdate destructor reaches this
// through ILT 0x0003DCF8 with TheBfmeGameLogic in ECX, an Object*, and a
// Drawable*.  GameLogic.cpp and the ZH donor name the same reciprocal binding.

typedef unsigned long DWORD;

extern "C" __declspec(dllimport) void __stdcall Sleep( DWORD milliseconds );

// BFME's GameEngine vtable puts serviceWindowsOS in slot 16 (+0x40), as also
// established by the matched DataChunk yield sites.
class GameEngine
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void serviceWindowsOS() = 0;
};

extern GameEngine *TheGameEngine;

class Drawable;

class Object
{
public:
	void friend_bindToDrawable( Drawable *draw );
};

class Drawable
{
public:
	void friend_bindToObject( Object *object );
};

class GameLogic
{
public:
	void bindObjectAndDrawable( Object *object, Drawable *draw );
};

static inline void rva003833C0YieldToOS()
{
	Sleep( 0 );
	if( TheGameEngine )
	{
		TheGameEngine->serviceWindowsOS();
	}
}

void GameLogic::bindObjectAndDrawable( Object *object, Drawable *draw )
{
	rva003833C0YieldToOS();
	draw->friend_bindToObject( object );
	rva003833C0YieldToOS();
	object->friend_bindToDrawable( draw );
	rva003833C0YieldToOS();
}
