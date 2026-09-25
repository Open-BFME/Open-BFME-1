// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/gamewindowlist /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad

// GameWindowManager slot 17 (+0x44) of the vtable at VA 0x010F8B60, next to
// the landed gogoGadgetCheckbox in slot 16 at 0x0047DD90. The style-bit-2
// guard (GWS_RADIO_BUTTON), the 8-byte RadioButtonData copy and the setup
// sequence follow the Zero Hour gogoGadgetRadioButton; retail ends with
// ret 0x10, so BFME keeps the reduced four-argument ABI of its siblings.
// The style test goes through the inline WinInstanceData::getStyle() over the
// dword m_style, as the Zero Hour BitTest(instData->getStyle(), ...) does:
// reading the field directly swaps ESI and EDI for this and the new window.
//
// Slot 29 (0x0047EDE0) and the ILT 0x0003A52B -> 0x004BD400 text setter
// keep address-derived names; see the ledger notes for their evidence.

#include <string.h>

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
	char m_gap00[0xc];
	unsigned int m_style;
	char m_gap10[0x178];
	AsciiString m_textLabelString;

	unsigned int getStyle() const { return m_style; }
};

class GameWindow
{
public:
	int winSetOwner(GameWindow *owner);
	void winSetUserData(void *data);
};

// The first argument is a creation descriptor, not a GameWindow: the body
// reads [arg1+0x30] as a WinInstanceData pointer, while retail GameWindow
// embeds its WinInstanceData at +0x30 (winGetInstanceData 0x00478C60 is
// lea eax,[ecx+0x30]). Field names keep the offset until the type is known.
struct Rva0047DEC0Desc
{
	GameWindow *m_owner00;
	char m_gap04[0x2c];
	WinInstanceData *m_instData30;
};

struct RadioButtonData
{
	int dword_0;
	int dword_4;
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
	virtual GameWindow *rva0047EDE0(Rva0047DEC0Desc *);
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
	virtual GameWindow *gogoGadgetRadioButton(Rva0047DEC0Desc *, RadioButtonData *, GameFont *, bool);
};

extern GameWindowManager *TheWindowManager;
extern void rva004BD400(GameWindow *, UnicodeString);


GameWindow *GameWindowManager::gogoGadgetRadioButton(Rva0047DEC0Desc *desc,
	RadioButtonData *rData, GameFont *defaultFont, bool defaultVisual)
{
	GameWindow *radioButton;
	RadioButtonData *radioData;

	if ((desc->m_instData30->getStyle() & 2) == 0)
		return 0;
	radioButton = TheWindowManager->rva0047EDE0(desc);
	if (radioButton == 0)
		return 0;
	radioData = new RadioButtonData;
	memcpy(radioData, rData, sizeof(RadioButtonData));
	radioButton->winSetUserData(radioData);
	radioButton->winSetOwner(desc->m_owner00);
	assignDefaultGadgetLook(radioButton, defaultFont, defaultVisual);
	UnicodeString text = winTextLabelToText(desc->m_instData30->m_textLabelString);
	if (text.getLength())
		rva004BD400(radioButton, text);
	return radioButton;
}
