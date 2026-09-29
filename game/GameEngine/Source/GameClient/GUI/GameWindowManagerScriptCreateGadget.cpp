// cl: /DNDEBUG /DWIN32 /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
// Identity: landed createWindow at RVA 004874A0 and the ZH createGadget twin.
// BFME uses the four-argument descriptor ABI and adds source-window draw copying.
// Layout: WinInstanceData fields witnessed by name_oracle; descriptor +30 from
// createWindow and retail. Opaque auxiliary views retain the target address.
#include "ascii_string.h"
#include <string.h>
class GameWindow { public: char pad[0x6c]; void *dword_6c; GameWindow *winGetChild(); };
class WinInstanceData { public: char pad[12]; unsigned m_style; unsigned m_status; GameWindow *m_owner; char pad18[0x184-0x18]; void *m_font; AsciiString m_textLabelString; AsciiString m_decoratedNameString; };
class Open2479440Record { public: GameWindow *dword_0; char pad[0x2c]; WinInstanceData *dword_30; };
enum NameKeyType { NAMEKEY_INVALID=0 };
class NameKeyGenerator { public: NameKeyType nameToKey(const AsciiString&); };
extern NameKeyGenerator *TheNameKeyGenerator;
class GameWindowManager;
extern GameWindowManager *TheWindowManager;
class Rva00486B10ManagerView { public:
virtual void slot00();
virtual void slot04();
virtual void slot08();
virtual void slot0c();
virtual void slot10();
virtual void slot14();
virtual void slot18();
virtual void slot1c();
virtual void slot20();
virtual void slot24();
virtual void slot28();
virtual void slot2c();
virtual void slot30();
virtual void slot34();
virtual GameWindow *slot38(Open2479440Record *record, void *font, bool assign);
virtual GameWindow *slot3c(Open2479440Record *record, void *font, bool assign);
virtual GameWindow *slot40(Open2479440Record *record, void *font, bool assign);
virtual GameWindow *slot44(Open2479440Record *record, void *data, void *font, bool assign);
virtual GameWindow *slot48(Open2479440Record *record, void *data, void *font, bool assign);
virtual GameWindow *slot4c(Open2479440Record *record, void *data, void *font, bool assign);
virtual GameWindow *slot50(Open2479440Record *record, void *data, void *font, bool assign);
virtual GameWindow *slot54(Open2479440Record *record, void *font, bool assign);
virtual GameWindow *slot58(Open2479440Record *record, void *data, void *font, bool assign);
virtual GameWindow *slot5c(Open2479440Record *record, void *data, void *font, bool assign);
virtual GameWindow *slot60(Open2479440Record *record, void *data, void *font, bool assign);
};
struct WinDrawData { void *image; unsigned color,borderColor; };
void Rva00485460CopyDrawData(GameWindow*,GameWindow*,WinDrawData*,WinDrawData*,WinDrawData*);
extern WinDrawData enabledSliderThumbDrawData[9];
extern WinDrawData disabledSliderThumbDrawData[9];
extern WinDrawData hiliteSliderThumbDrawData[9];
extern WinDrawData enabledSliderDrawData[9];
extern WinDrawData disabledSliderDrawData[9];
extern WinDrawData hiliteSliderDrawData[9];
extern WinDrawData enabledDownButtonDrawData[9];
extern WinDrawData disabledDownButtonDrawData[9];
extern WinDrawData hiliteDownButtonDrawData[9];
extern WinDrawData enabledUpButtonDrawData[9];
extern WinDrawData disabledUpButtonDrawData[9];
extern WinDrawData hiliteUpButtonDrawData[9];
extern WinDrawData enabledListBoxDrawData[9];
extern WinDrawData disabledListBoxDrawData[9];
extern WinDrawData hiliteListBoxDrawData[9];
extern WinDrawData enabledEditBoxDrawData[9];
extern WinDrawData disabledEditBoxDrawData[9];
extern WinDrawData hiliteEditBoxDrawData[9];
extern WinDrawData enabledDropDownButtonDrawData[9];
extern WinDrawData disabledDropDownButtonDrawData[9];
extern WinDrawData hiliteDropDownButtonDrawData[9];
GameWindow *GadgetListBoxGetUpButton(GameWindow*);
GameWindow *GadgetListBoxGetDownButton(GameWindow*);
GameWindow *GadgetListBoxGetSlider(GameWindow*);
GameWindow *GadgetComboBoxGetDropDownButton(GameWindow*);
GameWindow *GadgetComboBoxGetEditBox(GameWindow*);
GameWindow *GadgetComboBoxGetListBox(GameWindow*);
class BfmeKeyLC;
void bfmeGo926B(BfmeKeyLC*,char);
class BfmeObjENK;
void bfmeGoENK(BfmeObjENK*,char);
struct Rva00486B10EntryData { char pad[12]; unsigned dword_c; short word_10; char tail[22]; };
struct Rva00486B10ListData { short word_0,word_2; void *dword_4; char byte_8,byte_9,byte_a,byte_b,byte_c,byte_d; char pad_e[6]; void *dword_14; char tail[0x4c-0x18]; };
struct Rva00486B10ComboData { char pad[8]; short word_8; short pad_a; unsigned dword_c; Rva00486B10ListData *dword_10; Rva00486B10EntryData *dword_14; char pad18[8]; int dword_20; };
GameWindow *createGadget(char *type,void *data,Open2479440Record *record,GameWindow *source) {
 GameWindow *window=0;
 record->dword_30->m_owner=record->dword_0;
if(!strcmp(type,"PUSHBUTTON")) {
record->dword_30->m_style |= 1;
window=((Rva00486B10ManagerView*)TheWindowManager)->slot38(record,record->dword_30->m_font,false);
}
else if(!strcmp(type,"COMMANDBUTTON")) {
record->dword_30->m_style |= 1;
window=((Rva00486B10ManagerView*)TheWindowManager)->slot3c(record,record->dword_30->m_font,false);
}
else if(!strcmp(type,"RADIOBUTTON")) {
char filename[64]; char *c;
 strcpy(filename,record->dword_30->m_decoratedNameString.str());
 c=strchr(filename,':'); if(c) *c=0;
 if(TheNameKeyGenerator) *(int*)data=(int)TheNameKeyGenerator->nameToKey(AsciiString(filename));
record->dword_30->m_style |= 2;
window=((Rva00486B10ManagerView*)TheWindowManager)->slot44(record,data,record->dword_30->m_font,false);
}
else if(!strcmp(type,"CHECKBOX")) {
record->dword_30->m_style |= 4;
window=((Rva00486B10ManagerView*)TheWindowManager)->slot40(record,record->dword_30->m_font,false);
}
else if(!strcmp(type,"TABCONTROL")) {
record->dword_30->m_style |= 8192;
window=((Rva00486B10ManagerView*)TheWindowManager)->slot48(record,data,record->dword_30->m_font,false);
}
else if(!strcmp(type,"VERTSLIDER")) {
record->dword_30->m_style |= 8;
window=((Rva00486B10ManagerView*)TheWindowManager)->slot50(record,data,record->dword_30->m_font,false);
GameWindow *thumb=window->winGetChild(); if(thumb) {
Rva00485460CopyDrawData(thumb,source?source->winGetChild():0,enabledSliderThumbDrawData,disabledSliderThumbDrawData,hiliteSliderThumbDrawData);
if(thumb->dword_6c) bfmeGo926B((BfmeKeyLC*)thumb,1);
}
}
else if(!strcmp(type,"HORZSLIDER")) {
record->dword_30->m_style |= 16;
window=((Rva00486B10ManagerView*)TheWindowManager)->slot50(record,data,record->dword_30->m_font,false);
GameWindow *thumb=window->winGetChild(); if(thumb) {
Rva00485460CopyDrawData(thumb,source?source->winGetChild():0,enabledSliderThumbDrawData,disabledSliderThumbDrawData,hiliteSliderThumbDrawData);
}
}
else if(!strcmp(type,"SCROLLLISTBOX")) {
record->dword_30->m_style |= 32;
window=((Rva00486B10ManagerView*)TheWindowManager)->slot4c(record,data,record->dword_30->m_font,false);
GameWindow *upButton=GadgetListBoxGetUpButton(window);
Rva00485460CopyDrawData(upButton,source?GadgetListBoxGetUpButton(source):0,enabledUpButtonDrawData,disabledUpButtonDrawData,hiliteUpButtonDrawData);
GameWindow *downButton=GadgetListBoxGetDownButton(window);
Rva00485460CopyDrawData(downButton,source?GadgetListBoxGetDownButton(source):0,enabledDownButtonDrawData,disabledDownButtonDrawData,hiliteDownButtonDrawData);
GameWindow *slider=GadgetListBoxGetSlider(window); if(slider) {
GameWindow *sourceSlider=source?GadgetListBoxGetSlider(source):0;
Rva00485460CopyDrawData(slider,sourceSlider,enabledSliderDrawData,disabledSliderDrawData,hiliteSliderDrawData);
GameWindow *thumb=slider->winGetChild(); if(thumb) {
Rva00485460CopyDrawData(thumb,sourceSlider?sourceSlider->winGetChild():0,enabledSliderThumbDrawData,disabledSliderThumbDrawData,hiliteSliderThumbDrawData);
if(thumb->dword_6c) { bfmeGo926B((BfmeKeyLC*)thumb,1);bfmeGoENK((BfmeObjENK*)window,1);}
}
}
}
else if(!strcmp(type,"COMBOBOX")) {
Rva00486B10ComboData *cData=(Rva00486B10ComboData*)data;
 cData->dword_14=new Rva00486B10EntryData; memset(cData->dword_14,0,sizeof(Rva00486B10EntryData));
 cData->dword_10=new Rva00486B10ListData; memset(cData->dword_10,0,sizeof(Rva00486B10ListData));
 cData->dword_20=0;
 cData->dword_14->dword_c=cData->dword_c;
 cData->dword_14->word_10=cData->word_8;
 cData->dword_10->word_0=10;
 cData->dword_10->byte_8=0;
 cData->dword_10->byte_d=0;
 cData->dword_10->byte_9=0;
 cData->dword_10->byte_a=1;
 cData->dword_10->byte_b=0;
 cData->dword_10->byte_c=1;
 cData->dword_10->word_2=1;
 cData->dword_10->dword_14=0;
 cData->dword_10->dword_4=0;
record->dword_30->m_style |= 32768;
window=((Rva00486B10ManagerView*)TheWindowManager)->slot60(record,data,record->dword_30->m_font,false);
GameWindow *dropDownButton=GadgetComboBoxGetDropDownButton(window);
Rva00485460CopyDrawData(dropDownButton,source?GadgetComboBoxGetDropDownButton(source):0,enabledDropDownButtonDrawData,disabledDropDownButtonDrawData,hiliteDropDownButtonDrawData);
GameWindow *editBox=GadgetComboBoxGetEditBox(window);
Rva00485460CopyDrawData(editBox,source?GadgetComboBoxGetEditBox(source):0,enabledEditBoxDrawData,disabledEditBoxDrawData,hiliteEditBoxDrawData);
GameWindow *listBox=GadgetComboBoxGetListBox(window); if(listBox) {
GameWindow *sourceList=source?GadgetComboBoxGetListBox(source):0;
Rva00485460CopyDrawData(listBox,sourceList,enabledListBoxDrawData,disabledListBoxDrawData,hiliteListBoxDrawData);
GameWindow *upButton=GadgetListBoxGetUpButton(listBox);
Rva00485460CopyDrawData(upButton,source?GadgetListBoxGetUpButton(source):0,enabledUpButtonDrawData,disabledUpButtonDrawData,hiliteUpButtonDrawData);
GameWindow *downButton=GadgetListBoxGetDownButton(listBox);
Rva00485460CopyDrawData(downButton,source?GadgetListBoxGetDownButton(source):0,enabledDownButtonDrawData,disabledDownButtonDrawData,hiliteDownButtonDrawData);
GameWindow *slider=GadgetListBoxGetSlider(listBox); if(slider) {
GameWindow *sourceSlider=sourceList?GadgetListBoxGetSlider(sourceList):0;
Rva00485460CopyDrawData(slider,sourceSlider,enabledSliderDrawData,disabledSliderDrawData,hiliteSliderDrawData);
GameWindow *thumb=slider->winGetChild(); if(thumb) {
Rva00485460CopyDrawData(thumb,sourceSlider?sourceSlider->winGetChild():0,enabledSliderThumbDrawData,disabledSliderThumbDrawData,hiliteSliderThumbDrawData);
if(thumb->dword_6c) { bfmeGo926B((BfmeKeyLC*)thumb,1);}
}
}
}
}
else if(!strcmp(type,"ENTRYFIELD")) {
record->dword_30->m_style |= 64;
window=((Rva00486B10ManagerView*)TheWindowManager)->slot5c(record,data,record->dword_30->m_font,false);
}
else if(!strcmp(type,"STATICTEXT")) {
record->dword_30->m_style |= 128;
window=((Rva00486B10ManagerView*)TheWindowManager)->slot58(record,data,record->dword_30->m_font,false);
}
else if(!strcmp(type,"PROGRESSBAR")) {
record->dword_30->m_style |= 256;
window=((Rva00486B10ManagerView*)TheWindowManager)->slot54(record,record->dword_30->m_font,false);
}

return window;
}
