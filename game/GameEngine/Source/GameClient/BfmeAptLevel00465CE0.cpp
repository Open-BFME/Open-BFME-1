// ?bfmeAptLevel00465CE0@@YAHPAVBfmeH1065@@@Z
// The helper returns the APT level for the first matching window ancestor.

class BfmeAptLevelResult00465CE0
{
public:
	unsigned char m_beforeLevel[0x250];
	int m_level;
};

class BfmeH1065
{
};

class GameWindow
{
public:
	GameWindow *winGetParent();
};

class GameWindowManager
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void findWindowAtLevel(GameWindow *window, int level, int timeout,
		BfmeAptLevelResult00465CE0 **result);
};

extern GameWindowManager *TheWindowManager;

int __cdecl bfmeAptLevel00465CE0(BfmeH1065 *window)
{
	if (window == 0)
	{
		return -1;
	}
	else
	{
		BfmeAptLevelResult00465CE0 *result = 0;

		loop:
		if (window == 0)
			goto noResult;

		TheWindowManager->findWindowAtLevel((GameWindow *)window, 0x1d, 0x7d0,
			&result);

		window = (BfmeH1065 *)((GameWindow *)window)->winGetParent();
		if (result == 0)
			goto loop;

		return result->m_level;

		noResult:
		return 0xc;
	}
}
