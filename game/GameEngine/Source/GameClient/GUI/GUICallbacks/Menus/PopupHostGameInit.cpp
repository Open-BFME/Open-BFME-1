// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

// Native BFME PopupHostGameInit: RVA 004D68C0; 1253 bytes.
// Ported from EA GPL-3.0-or-later GeneralsMD PopupHostGame.cpp.
// FunctionLexicon VA 012A9A9C pairs PopupHostGameInit (01086A9C) with
// ILT RVA 00032821 which jumps to body RVA 004D68C0.
// Retail widget strings preserve all nine ZH controls in the same order;
// the later ZH use-stats/limit-armies controls are absent from this body.
// Window-manager slots: focus +B0; lookup +DC; modal +EC. GameSpy local name +68.
// CustomMatchPreferences occupies 20 bytes at caller ESP+10..ESP+23;
// its constructor/destructor are the named retail bodies behind B0F5/41F6A.
// emptyString01336E54 names the existing UnicodeString::TheEmptyString singleton
// by address because the canonical unicode_string.h omits that static member.
#include "ascii_string.h"
#include "unicode_string.h"
template<class T> inline StringBase<T>::~StringBase() { releaseBuffer(); }
template<> inline const char *StringBase<char>::str() const { return m_data ? m_data->data : ""; }
inline UnicodeString::UnicodeString() { m_text=0; }
inline UnicodeString::UnicodeString(const UnicodeString& s) { ((StringBase<unsigned short>*)this)->StringBase<unsigned short>::StringBase(*(const StringBase<unsigned short>*)&s); }
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short>*)this)->releaseBuffer(); }
class WindowLayout;
class GameWindow;
enum NameKeyType { NAMEKEY_INVALID=0 };
class NameKeyGenerator { public: NameKeyType nameToKey(const char*); };
extern NameKeyGenerator* TheNameKeyGenerator;
class GameWindowManager { public:
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
 virtual int winSetFocus(GameWindow*);
 virtual void slot45();
 virtual void slot46();
 virtual void slot47();
 virtual void slot48();
 virtual void slot49();
 virtual void slot50();
 virtual void slot51();
 virtual void slot52();
 virtual void slot53();
 virtual void slot54();
 virtual GameWindow* winGetWindowFromId(GameWindow*,NameKeyType);
 virtual void slot56();
 virtual void slot57();
 virtual void slot58();
 virtual int winSetModal(GameWindow*);
};
extern GameWindowManager* TheWindowManager;
class GameSpyInfo { public:
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
 virtual AsciiString getLocalName();
};
extern GameSpyInfo* TheGameSpyInfo;
class CustomMatchPreferences {
public: CustomMatchPreferences(); virtual ~CustomMatchPreferences(); bool allowsObservers();
private: char storage[16];
};
void GadgetTextEntrySetText(GameWindow*,UnicodeString);
void GadgetCheckBoxSetChecked(GameWindow*,bool);
void GadgetComboBoxReset(GameWindow*);
void PopulateCustomLadderComboBox();
extern NameKeyType parentPopupID;
extern GameWindow* parentPopup;
extern NameKeyType textEntryGameNameID;
extern GameWindow* textEntryGameName;
extern NameKeyType buttonCreateGameID;
extern GameWindow* buttonCreateGame;
extern NameKeyType checkBoxAllowObserversID;
extern GameWindow* checkBoxAllowObservers;
extern NameKeyType textEntryGameDescriptionID;
extern GameWindow* textEntryGameDescription;
extern NameKeyType buttonCancelID;
extern GameWindow* buttonCancel;
extern NameKeyType textEntryLadderPasswordID;
extern GameWindow* textEntryLadderPassword;
extern NameKeyType comboBoxLadderNameID;
extern GameWindow* comboBoxLadderName;
extern NameKeyType textEntryGamePasswordID;
extern GameWindow* textEntryGamePassword;
extern UnicodeString emptyString01336E54;
void PopupHostGameInit( WindowLayout *layout, void *userData )
{
	parentPopupID = TheNameKeyGenerator->nameToKey(AsciiString("PopupHostGame.wnd:ParentHostPopUp").str());
	parentPopup = TheWindowManager->winGetWindowFromId(0, parentPopupID);

	textEntryGameNameID = TheNameKeyGenerator->nameToKey(AsciiString("PopupHostGame.wnd:TextEntryGameName").str());
	textEntryGameName = TheWindowManager->winGetWindowFromId(parentPopup, textEntryGameNameID);
	UnicodeString name;
	name.translate(TheGameSpyInfo->getLocalName());
	GadgetTextEntrySetText(textEntryGameName, name);

	textEntryGameDescriptionID = TheNameKeyGenerator->nameToKey(AsciiString("PopupHostGame.wnd:TextEntryGameDescription").str());
	textEntryGameDescription = TheWindowManager->winGetWindowFromId(parentPopup, textEntryGameDescriptionID);
	GadgetTextEntrySetText(textEntryGameDescription, emptyString01336E54);

	textEntryLadderPasswordID = TheNameKeyGenerator->nameToKey(AsciiString("PopupHostGame.wnd:TextEntryLadderPassword").str());
	textEntryLadderPassword = TheWindowManager->winGetWindowFromId(parentPopup, textEntryLadderPasswordID);
	GadgetTextEntrySetText(textEntryLadderPassword, emptyString01336E54);

	textEntryGamePasswordID = TheNameKeyGenerator->nameToKey(AsciiString("PopupHostGame.wnd:TextEntryGamePassword").str());
	textEntryGamePassword = TheWindowManager->winGetWindowFromId(parentPopup, textEntryGamePasswordID);
	GadgetTextEntrySetText(textEntryGamePassword, emptyString01336E54);

	buttonCreateGameID = TheNameKeyGenerator->nameToKey(AsciiString("PopupHostGame.wnd:ButtonCreateGame").str());
	buttonCreateGame = TheWindowManager->winGetWindowFromId(parentPopup, buttonCreateGameID);

	buttonCancelID = TheNameKeyGenerator->nameToKey(AsciiString("PopupHostGame.wnd:ButtonCancel").str());
	buttonCancel = TheWindowManager->winGetWindowFromId(parentPopup, buttonCancelID);

	checkBoxAllowObserversID = TheNameKeyGenerator->nameToKey(AsciiString("PopupHostGame.wnd:CheckBoxAllowObservers").str());
	checkBoxAllowObservers = TheWindowManager->winGetWindowFromId(parentPopup, checkBoxAllowObserversID);
	CustomMatchPreferences customPref;
	GadgetCheckBoxSetChecked(checkBoxAllowObservers, customPref.allowsObservers());

	comboBoxLadderNameID = TheNameKeyGenerator->nameToKey(AsciiString("PopupHostGame.wnd:ComboBoxLadderName").str());
	comboBoxLadderName = TheWindowManager->winGetWindowFromId(parentPopup, comboBoxLadderNameID);
	if (comboBoxLadderName)
		GadgetComboBoxReset(comboBoxLadderName);
	PopulateCustomLadderComboBox();


 TheWindowManager->winSetFocus(parentPopup);
 TheWindowManager->winSetModal(parentPopup);
}
