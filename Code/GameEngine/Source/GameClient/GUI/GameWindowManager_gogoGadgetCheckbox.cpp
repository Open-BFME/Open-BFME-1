// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/gamewindowlist /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad

// The primary GameWindowManager vtable puts this method in slot 16 at
// 0x0047DD90. The CHECKBOX arm of createGadget selects that slot after it
// sets style bit 4, and the push-button sibling has the same three-argument
// ABI and owner, look, and label sequence.

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
	virtual GameWindow *gogoGadgetCheckbox(GameWindow *, GameFont *, bool);
};

extern GameWindowManager *TheWindowManager;
extern void GadgetCheckBoxSetText(GameWindow *, UnicodeString);

// The retail calls use the incremental-link thunks, not the folded bodies.
#pragma comment(linker, "/alternatename:?winSetOwner@GameWindow@@QAEHPAV1@@Z=?j_00047230@@YAXXZ")
#pragma comment(linker, "/alternatename:?GadgetCheckBoxSetText@@YAXPAVGameWindow@@VUnicodeString@@@Z=?j_00018241@@YAXXZ")

GameWindow *GameWindowManager::gogoGadgetCheckbox(GameWindow *parent,
	GameFont *font, bool visual)
{
	if ((parent->instanceData->style & 4) == 0)
		return 0;
	GameWindow *checkbox = TheWindowManager->create(parent);
	if (checkbox == 0)
		return 0;
	checkbox->winSetOwner(parent->owner);
	assignDefaultGadgetLook(checkbox, font, visual);
	UnicodeString text = winTextLabelToText(parent->instanceData->textLabel);
	if (text.getLength())
		GadgetCheckBoxSetText(checkbox, text);
	return checkbox;
}
