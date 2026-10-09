void bfmeGo911A(void);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowManager.h
class GameWindowManager
{
public:
	virtual void winRepaint(void);
};

class BfmeThingBCD
{
public:
	void bfmeGoBCD();
};

void BfmeThingBCD::bfmeGoBCD()
{
	bfmeGo911A();
	reinterpret_cast<GameWindowManager *>(this)->GameWindowManager::winRepaint();
}
