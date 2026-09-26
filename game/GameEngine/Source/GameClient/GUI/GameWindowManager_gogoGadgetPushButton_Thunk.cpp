// cl: /DNDEBUG /MD /EHsc
//
// BFME's GameWindowManager vtable exposes the push-button factory through
// the reduced (parent, font, visual) ABI.  The old scaffold carried the
// larger Zero Hour spelling, but retail ends with ret 0xc and uses the
// vslot-25 look arguments at stack offsets for this three-argument method.

class GameWindow;
class GameFont;

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringBase();
	StringBase(const StringBase<T> &that);
	void releaseBuffer();

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

	int getLength() const
	{
		return data ? *(unsigned short *)((char *)data + 4) : 0;
	}
};

class WinInstanceData
{
public:
	char padBeforeStyle[0xc];
	unsigned char style;
	char padAfterStyle[0x17b];
	AsciiString textLabel;
};

class GameWindow
{
public:
	GameWindow *owner;
	char pad[0x2c];
	WinInstanceData *instanceData;

	int winSetOwner(GameWindow *owner);
	void winSetUserData(void *data);
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
	virtual GameWindow *create(GameWindow *);
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
	virtual GameWindow *gogoGadgetPushButton(GameWindow *, GameFont *, bool);
};

extern GameWindowManager *TheWindowManager;
extern void GadgetRadioSetText(GameWindow *, UnicodeString);

// Preserve the retail incremental-link call sites rather than resolving
// these folded helpers directly.
#pragma comment(linker, "/alternatename:?winSetOwner@GameWindow@@QAEHPAV1@@Z=?j_00047230@@YAXXZ")
#pragma comment(linker, "/alternatename:?winSetUserData@GameWindow@@QAEXPAX@Z=?j_00002e69@@YAXXZ")
#pragma comment(linker, "/alternatename:?GadgetRadioSetText@@YAXPAVGameWindow@@VUnicodeString@@@Z=?j_000424f1@@YAXXZ")

// ?gogoGadgetPushButton@GameWindowManager@@UAEPAVGameWindow@@PAV2@PAVGameFont@@_N@Z
GameWindow *GameWindowManager::gogoGadgetPushButton(GameWindow *parent,
	GameFont *font, bool visual)
{
	if ((parent->instanceData->style & 1) == 0)
		return 0;
	GameWindow *button = TheWindowManager->create(parent);
	if (button == 0)
		return 0;
	button->winSetOwner(parent->owner);
	button->winSetUserData(0);
	assignDefaultGadgetLook(button, font, visual);
	UnicodeString text = winTextLabelToText(parent->instanceData->textLabel);
	if (text.getLength())
		GadgetRadioSetText(button, text);
	return button;
}
