// Two small bodies the retail image emits twice each, both copies converted
// here under their own names. Each pokes the engine through its table and then,
// if the global data says so, tells the display to redraw; the shorter pair
// hands the redraw the last word of the frame, the longer pair tail-jumps into
// it with a fresh zero in the argument slot.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameEngine.h
class GameEngine
{
public:
	virtual void bfmeSpare000JV(void) = 0;
	virtual void bfmeSpare001JV(void) = 0;
	virtual void bfmeSpare002JV(void) = 0;
	virtual void bfmeSpare003JV(void) = 0;
	virtual void bfmeSpare004JV(void) = 0;
	virtual void bfmeSpare005JV(void) = 0;
	virtual void bfmeSpare006JV(void) = 0;
	virtual void bfmeSpare007JV(void) = 0;
	virtual void bfmeSpare008JV(void) = 0;
	virtual void bfmeSpare009JV(void) = 0;
	virtual void bfmeSpare010JV(void) = 0;
	virtual void bfmeSpare011JV(void) = 0;
	virtual void bfmeSpare012JV(void) = 0;
	virtual void bfmeSpare013JV(void) = 0;
	virtual void bfmeSpare014JV(void) = 0;
	virtual void bfmeSpare015JV(void) = 0;
	virtual void bfmeStepJV(void) = 0;		///< retail slot 16, [vptr+0x40]
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
public:
	unsigned char m_bfmeHead[0x1278];	// 0x0000
	unsigned char m_bfmeOn;			// 0x1278
};


// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Display.h
class Display
{
public:
	virtual void bfmeSpare000JV(void) = 0;
	virtual void bfmeSpare001JV(void) = 0;
	virtual void bfmeSpare002JV(void) = 0;
	virtual void bfmeSpare003JV(void) = 0;
	virtual void bfmeSpare004JV(void) = 0;
	virtual void bfmeSpare005JV(void) = 0;
	virtual void bfmeSpare006JV(void) = 0;
	virtual void bfmeSpare007JV(void) = 0;
	virtual void bfmeSpare008JV(void) = 0;
	virtual void bfmeSpare009JV(void) = 0;
	virtual void bfmeSpare010JV(void) = 0;
	virtual void bfmeSpare011JV(void) = 0;
	virtual void bfmeSpare012JV(void) = 0;
	virtual void bfmeSpare013JV(void) = 0;
	virtual void bfmeSpare014JV(void) = 0;
	virtual void bfmeSpare015JV(void) = 0;
	virtual void bfmeSpare016JV(void) = 0;
	virtual void bfmeSpare017JV(void) = 0;
	virtual void bfmeSpare018JV(void) = 0;
	virtual void bfmeSpare019JV(void) = 0;
	virtual void bfmeSpare020JV(void) = 0;
	virtual void bfmeSpare021JV(void) = 0;
	virtual void bfmeSpare022JV(void) = 0;
	virtual void bfmeSpare023JV(void) = 0;
	virtual void bfmeSpare024JV(void) = 0;
	virtual void bfmeSpare025JV(void) = 0;
	virtual void bfmeSpare026JV(void) = 0;
	virtual void bfmeSpare027JV(void) = 0;
	virtual void bfmeSpare028JV(void) = 0;
	virtual void bfmeSpare029JV(void) = 0;
	virtual void bfmeSpare030JV(void) = 0;
	virtual void bfmeSpare031JV(void) = 0;
	virtual void bfmeSpare032JV(void) = 0;
	virtual void bfmeSpare033JV(void) = 0;
	virtual void bfmeSpare034JV(void) = 0;
	virtual void bfmeSpare035JV(void) = 0;
	virtual void bfmeSpare036JV(void) = 0;
	virtual void bfmeSpare037JV(void) = 0;
	virtual void bfmeSpare038JV(void) = 0;
	virtual void bfmeSpare039JV(void) = 0;
	virtual void bfmeSpare040JV(void) = 0;
	virtual void bfmeSpare041JV(void) = 0;
	virtual void bfmeSpare042JV(void) = 0;
	virtual void bfmeSpare043JV(void) = 0;
	virtual void bfmeSpare044JV(void) = 0;
	virtual void bfmeSpare045JV(void) = 0;
	virtual void bfmeSpare046JV(void) = 0;
	virtual void bfmeSpare047JV(void) = 0;
	virtual void bfmeSpare048JV(void) = 0;
	virtual void bfmeSpare049JV(void) = 0;
	virtual void bfmeSpare050JV(void) = 0;
	virtual void bfmeSpare051JV(void) = 0;
	virtual void bfmeSpare052JV(void) = 0;
	virtual void bfmeSpare053JV(void) = 0;
	virtual void bfmeSpare054JV(void) = 0;
	virtual void bfmeSpare055JV(void) = 0;
	virtual void bfmeSpare056JV(void) = 0;
	virtual void bfmeSpare057JV(void) = 0;
	virtual void bfmeSpare058JV(void) = 0;
	virtual void bfmeSpare059JV(void) = 0;
	virtual void bfmeSpare060JV(void) = 0;
	virtual void bfmeSpare061JV(void) = 0;
	virtual void bfmeSpare062JV(void) = 0;
	virtual void bfmeSpare063JV(void) = 0;
	virtual void bfmeRedrawJV(int how) = 0;		///< retail slot 64, [vptr+0x100]
};

extern GameEngine *TheGameEngine;		///< retail [0x012ED524]
extern GlobalData *TheWritableGlobalData;	///< retail [0x012ED5C8]
extern Display *TheDisplay;			///< retail [0x012F1270]


void __stdcall bfmeShowJV(int spare)
{
	TheGameEngine->bfmeStepJV();

	if (TheWritableGlobalData->m_bfmeOn != 0)
		TheDisplay->bfmeRedrawJV(0);
}


void __stdcall bfmeShowJX(int spare)
{
	TheGameEngine->bfmeStepJV();

	if (TheWritableGlobalData->m_bfmeOn != 0)
		TheDisplay->bfmeRedrawJV(0);
}


void __stdcall bfmeShowJW(int spare, int other)
{
	TheGameEngine->bfmeStepJV();

	if (TheWritableGlobalData->m_bfmeOn != 0)
		TheDisplay->bfmeRedrawJV(0);
}


void __stdcall bfmeShowJY(int spare, int other)
{
	TheGameEngine->bfmeStepJV();

	if (TheWritableGlobalData->m_bfmeOn != 0)
		TheDisplay->bfmeRedrawJV(0);
}

