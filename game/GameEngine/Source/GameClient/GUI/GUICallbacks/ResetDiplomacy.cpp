// cl: /DNDEBUG /MD /EHsc

class WindowLayout;

class GameWindow;

class InGameUI
{
public:
	void unregisterWindowLayout( WindowLayout *layout );
};

class BfmeDiplomacyLayoutTeardown
{
public:
	virtual void slot00() = 0;
	virtual void deletingDestructor( unsigned int flags ) = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void destroyWindows() = 0;
};

class BfmeDiplomacyAnimateWindowTeardown
{
public:
	virtual void deletingDestructor( unsigned int flags ) = 0;
};

class AnimateWindowManager
{
public:
	virtual ~AnimateWindowManager();
};

extern WindowLayout *theLayout;
extern GameWindow *theWindow;
extern InGameUI *TheInGameUI;
extern AnimateWindowManager *theAnimateWindowManager;

void InitBuddyControls( int type );

void ResetDiplomacy( void )
{
	if(theLayout)
	{
		TheInGameUI->unregisterWindowLayout(theLayout);
		reinterpret_cast<BfmeDiplomacyLayoutTeardown *>(theLayout)->destroyWindows();
		if (theLayout)
			reinterpret_cast<BfmeDiplomacyLayoutTeardown *>(theLayout)->deletingDestructor( 1 );
		InitBuddyControls(-1);
	}
	theLayout = 0;
	theWindow = 0;
	BfmeDiplomacyAnimateWindowTeardown *animate = reinterpret_cast<BfmeDiplomacyAnimateWindowTeardown *>(theAnimateWindowManager);
	if (animate)
		animate->deletingDestructor( 1 );
	theAnimateWindowManager = 0;
}
