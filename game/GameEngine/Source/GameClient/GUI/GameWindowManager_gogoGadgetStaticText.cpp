// ?gogoGadgetStaticText@GameWindowManager@@UAEPAVGameWindow@@PAV2@PAU_TextData@@PAVGameFont@@_N@Z
// The GameWindowManager::gogoGadgetStaticText body spans 325 bytes at
// 0x0047E010 and occupies vtable slot 22. Retail passes four explicit
// arguments here. The longer Zero Hour overload stays in GameWindowManager.cpp.
// This file declares only the layouts and calls that this body needs.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/gamewindowlist /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad


class GameFont;
class DisplayString;

extern "C" void *memcpy(void *, const void *, unsigned int);

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringBase();
	StringBase(const StringBase<T> &that);
	void releaseBuffer();

public:
	int getLength() const
	{
		return data ? *(unsigned short *)((char *)data + 4) : 0;
	}

protected:
	void *data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const AsciiString &that) : StringBase<char>(that) {}
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString();
	UnicodeString(const UnicodeString &that) : StringBase<unsigned short>(that) {}
	~UnicodeString() { releaseBuffer(); }

	using StringBase<unsigned short>::getLength;
};

// BFME's static-text factory copies an eight-byte input record.  Keep the
// record typed and explicit: the retail body owns only the display pointer
// and the second four-byte text option word here.
typedef struct _TextData
{
	DisplayString *text;
	unsigned int options;
} TextData;

class WinInstanceData
{
public:
	char padBeforeStyle[0xc];
	unsigned int style;
	unsigned int status;
	char padBeforeTextLabel[0x174];
	AsciiString textLabel;
};

class GameWindow
{
public:
	GameWindow *owner;
	char pad[0x2c];
	WinInstanceData *instanceData;
};

class DisplayString
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void setWordWrapCentered(bool centered);
};

class DisplayStringManager
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual DisplayString *newDisplayString();
};

class GameWindowManager
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void assignDefaultGadgetLook(GameWindow *, GameFont *, bool);
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual GameWindow *winCreate(GameWindow *);
	virtual void v30();
	virtual void v31();
	virtual void v32();
	virtual void v33();
	virtual void v34();
	virtual void v35();
	virtual void v36();
	virtual void v37();
	virtual void v38();
	virtual void v39();
	virtual void v40();
	virtual void v41();
	virtual void v42();
	virtual void v43();
	virtual void v44();
	virtual void v45();
	virtual void v46();
	virtual void v47();
	virtual void v48();
	virtual void v49();
	virtual void v50();
	virtual void v51();
	virtual void v52();
	virtual void v53();
	virtual void v54();
	virtual void v55();
	virtual void v56();
	virtual void v57();
	virtual void v58();
	virtual void v59();
	virtual void v60();
	virtual void v61();
	virtual void v62();
	virtual void v63();
	virtual void v64();
	virtual void v65();
	virtual void v66();
	virtual void v67();
	virtual void v68();
	virtual void v69();
	virtual UnicodeString winTextLabelToText(AsciiString);
	virtual GameWindow *gogoGadgetStaticText(GameWindow *, TextData *, GameFont *, bool);
};

extern DisplayStringManager *TheDisplayStringManager;

// Retail calls these incremental-link entry points directly.
extern void j_00047230();
extern void j_00002e69();
extern void j_0002c16f();

GameWindow *GameWindowManager::gogoGadgetStaticText(GameWindow *parent,
	TextData *textData, GameFont *defaultFont, bool defaultVisual)
{
	GameWindow *textWin;
	typedef int (GameWindow::*SetOwner)(GameWindow *);
	typedef void (GameWindow::*SetUserData)(void *);
	typedef void (__cdecl *SetStaticText)(GameWindow *, UnicodeString);
	union { void (*fn)(); SetOwner setOwner; } uOwner = { j_00047230 };
	union { void (*fn)(); SetUserData setUserData; } uUserData = { j_00002e69 };
	union { void (*fn)(); SetStaticText setStaticText; } uStaticText = { j_0002c16f };

	parent->instanceData->style &= ~0x1000;
	if ((parent->instanceData->style & 0x80) != 0)
	{
		textWin = winCreate(parent);
		if (textWin != 0)
		{
			(textWin->*uOwner.setOwner)(parent->owner);

			TextData *data = new TextData;
			memcpy(data, textData, sizeof(TextData));
			data->text = TheDisplayStringManager->newDisplayString();
			unsigned int status = parent->instanceData->status;
			data->text->setWordWrapCentered((status & 0x40000) != 0);
			(textWin->*uUserData.setUserData)(data);

			assignDefaultGadgetLook(textWin, defaultFont, defaultVisual);

			UnicodeString text = winTextLabelToText(parent->instanceData->textLabel);
			if (text.getLength())
				uStaticText.setStaticText(textWin, text);
		}
		return textWin;
	}

	return 0;
}
