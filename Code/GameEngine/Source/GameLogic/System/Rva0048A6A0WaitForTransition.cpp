// cl: /DNDEBUG /MD
// ZH GameLogic.cpp:2184 transition pump, with BFME's member delay.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowTransitions.h
class GameWindowTransitionsHandler
{
public:
	bool isFinished();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowManager.h
class GameWindowManager
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void update();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Display.h
class Display
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void draw();
};

extern GameWindowTransitionsHandler *TheTransitionHandler;
extern GameWindowManager *TheWindowManager;
extern Display *TheDisplay;
extern void setFPMode();
extern "C" __declspec(dllimport) void __stdcall Sleep( unsigned int ms );

class Rva0048A6A0TransitionWait
{
public:
	void waitForTransition();

private:
	char m_pad[0x50];
	unsigned int m_delay;
};

void Rva0048A6A0TransitionWait::waitForTransition()
{
	if( !TheTransitionHandler->isFinished() ) {
		do {
			TheWindowManager->update();
			if( !TheTransitionHandler->isFinished() ) {
				TheDisplay->draw();
				setFPMode();
				Sleep( m_delay );
			}
		} while( !TheTransitionHandler->isFinished() );
	}
}
