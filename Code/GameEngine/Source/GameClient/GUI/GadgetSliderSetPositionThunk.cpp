// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: GadgetSliderSetPosition, retail 0x0055DB20.
//
// The Zero Hour one-liner. Its definition is not in this tree -- only call
// sites, in OptionsMenu.cpp -- so it is spelled here with the two things the
// retail bytes pin: GSM_SET_SLIDER is 0x400d, and GameWindowManager's
// winSendSystemMsg is vtable slot 53 (`call [eax+0xd4]`).
//
// Only that one slot is named; the rest stay anonymous because nothing here
// needs them.

class GameWindow;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowManager.h
class GameWindowManager
{
public:
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
	virtual void slot6() = 0;
	virtual void slot7() = 0;
	virtual void slot8() = 0;
	virtual void slot9() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void slot39() = 0;
	virtual void slot40() = 0;
	virtual void slot41() = 0;
	virtual void slot42() = 0;
	virtual void slot43() = 0;
	virtual void slot44() = 0;
	virtual void slot45() = 0;
	virtual void slot46() = 0;
	virtual void slot47() = 0;
	virtual void slot48() = 0;
	virtual void slot49() = 0;
	virtual void slot50() = 0;
	virtual void slot51() = 0;
	virtual void slot52() = 0;
	virtual int winSendSystemMsg(GameWindow *window, unsigned int msg,
		unsigned int mData1, unsigned int mData2) = 0;
};

extern GameWindowManager *TheWindowManager;

enum
{
	GSM_SET_SLIDER = 0x400d
};

// ?GadgetSliderSetPosition@@YAXPAVGameWindow@@H@Z
void GadgetSliderSetPosition( GameWindow *g, int pos )
{
	TheWindowManager->winSendSystemMsg( g, GSM_SET_SLIDER, (unsigned int)pos, 0 );
}
