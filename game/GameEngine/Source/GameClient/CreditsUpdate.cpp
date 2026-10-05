// cl: /DNDEBUG /D_STLP_USE_STATIC_LIB /MD /EHsc /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/stlp_nodealloc
// stlport
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
// CreditsManager::update, RVA 0x0040CE30, 1308 bytes including switch table.
// The constructor at 0x0040CA50 installs the CreditsManager vtable at
// VA 0x010F0D04. The update body is also reached by ILT 0x0002B5CB.
// The old 400-byte dump ended inside the instruction at 0x0040CFBF.
// The real ret is at 0x0040D334; its five-entry table ends at 0x0040D34C.
// Reference algorithm: Credits.cpp. These TU-local ABI views preserve BFME
// font and display-string slots; the string types use their shared headers.
#include <list>
#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"
#include "../../../Libraries/Source/WWVegas/WWLib/unicode_string.h"
typedef int Int; const int CREDIT_SPACE_OFFSET=2; const int TRUE=1;
enum { CREDIT_STYLE_TITLE, CREDIT_STYLE_POSITION, CREDIT_STYLE_NORMAL, CREDIT_STYLE_COLUMN, CREDIT_STYLE_BLANK };
struct ICoord2D { int x,y; };
class GameFont;
class DisplayString {
public:
    virtual void slot0()=0;
    virtual void setText(UnicodeString)=0;
    virtual void slot2()=0;virtual void slot3()=0;virtual void slot4()=0;virtual void slot5()=0;
    virtual void setFont(GameFont*)=0;
    virtual void slot7()=0;virtual void slot8()=0;virtual void slot9()=0;virtual void slot10()=0;
    virtual void slot11()=0;virtual void slot12()=0;virtual void slot13()=0;virtual void slot14()=0;
    virtual void getSize(int*,int*)=0;
};
class DisplayStringManager {
public:
    typedef DisplayString*(DisplayStringManager::*New)();
    typedef void (DisplayStringManager::*Free)(DisplayString*);
    struct Vtable { void *pad00[9]; New make; Free free; }; Vtable *vtable;
    DisplayString *newDisplayString() { return (this->*(vtable->make))(); }
    void freeDisplayString(DisplayString *s) { (this->*(vtable->free))(s); }
};
extern DisplayStringManager *TheDisplayStringManager;
class FontLibraryBFMERetail { public: GameFont *getFont(AsciiString*,float,unsigned char); };
class FontLibrary;
extern FontLibrary *TheFontLibrary;
struct FontDesc { AsciiString name; int size; bool bold; };
// View of the credits fonts read off the language singleton here.  The global
// itself is retail's TheGlobalLanguageData, a GlobalLanguage*; that class is
// declared by Common/System/game_engine_subsystems.h and by the upstream
// GameClient/GlobalLanguage.h, so only the members this TU touches are spelled
// out and they are reached through a cast.
class GlobalLanguageData {
public:
    char pad00[0xdc]; FontDesc m_creditsTitleFont,m_creditsPositionFont,m_creditsNormalFont;
    int adjustFontSize(int);
};
class GlobalLanguage;
extern GlobalLanguage *TheGlobalLanguageData;
class CreditsLine {
public:
    int m_style; UnicodeString m_text,m_secondText; bool m_useSecond,m_done;
    DisplayString *m_displayString,*m_secondDisplayString; ICoord2D m_pos; int m_height,m_color;
};
class CreditsManager {
public: virtual void update();
private:
    int pad04;
    typedef std::list<CreditsLine*> CreditsLineList;
    CreditsLineList m_creditLineList; CreditsLineList::iterator m_creditLineListIt;
    CreditsLineList m_displayedCreditLineList;
    int m_scrollRate,m_scrollRatePerFrames; bool m_scrollDown;
    int m_titleColor,m_positionColor,m_normalColor,m_currentStyle;
    bool m_isFinished; int m_framesSinceStarted,m_normalFontHeight;
};
void CreditsManager::update( void )
{
	if(m_isFinished)
		return;
	if (((int*)this)[0x3c/4]<=0 || ((int*)this)[0x40/4]<=0) return;
	m_framesSinceStarted++;
	
	if(m_framesSinceStarted%m_scrollRatePerFrames != 0)
		return;
	

	Int y = 0;
	Int yTest = 0;
	Int lastHeight = 0;
	Int start = m_scrollDown? 0:((int*)this)[0x40/4];
	Int end =m_scrollDown? ((int*)this)[0x40/4]:0;
	Int offsetStartMultiplyer = m_scrollDown? -1:0;  // if we're scrolling from the top, we need to subtract the height
	Int offsetEndMultiplyer = m_scrollDown? 0:1;
	Int directionMultiplyer = m_scrollDown? 1:-1;
	CreditsLineList::iterator drawIt = m_displayedCreditLineList.begin();
	while (drawIt != m_displayedCreditLineList.end())
	{
		CreditsLine *cLine = *drawIt;
		y = cLine->m_pos.y = cLine->m_pos.y + (m_scrollRate * directionMultiplyer);
		lastHeight = cLine->m_height;
		yTest = y + ((lastHeight + CREDIT_SPACE_OFFSET) * offsetEndMultiplyer);
		if(((m_scrollDown && (yTest > end)) || (!m_scrollDown && (yTest < end))))
		{
			TheDisplayStringManager->freeDisplayString(cLine->m_displayString);
			TheDisplayStringManager->freeDisplayString(cLine->m_secondDisplayString);
			cLine->m_displayString = NULL;
			cLine->m_secondDisplayString = NULL;
			drawIt = m_displayedCreditLineList.erase(drawIt);
		}
		else
			drawIt++;
	}
	
	y= y + ((lastHeight + CREDIT_SPACE_OFFSET) * offsetStartMultiplyer);
	
	// is it time to add a new string?
	if(!((m_scrollDown && (yTest >= start)) || (!m_scrollDown && (yTest  <= start))))
		return;
	
	if(m_displayedCreditLineList.size() == 0 && m_creditLineListIt == m_creditLineList.end())
		m_isFinished = TRUE;
	
	if(m_creditLineListIt == m_creditLineList.end())
		return;

	CreditsLine *cLine = *m_creditLineListIt;
	ICoord2D pos;
	switch (cLine->m_style) 
	{
	case CREDIT_STYLE_TITLE:
		{
			cLine->m_color = m_titleColor;
			
			if(TheGlobalLanguageData&& !cLine->m_text.isEmpty())
			{
				DisplayString *ds = TheDisplayStringManager->newDisplayString();
				if(!ds)
					return;
				ds->setFont(reinterpret_cast<FontLibraryBFMERetail *>(TheFontLibrary)->getFont(&reinterpret_cast<GlobalLanguageData *>( TheGlobalLanguageData )->m_creditsTitleFont.name,
														reinterpret_cast<GlobalLanguageData *>( TheGlobalLanguageData )->adjustFontSize(reinterpret_cast<GlobalLanguageData *>( TheGlobalLanguageData )->m_creditsTitleFont.size),
														reinterpret_cast<GlobalLanguageData *>( TheGlobalLanguageData )->m_creditsTitleFont.bold));
				ds->setText(cLine->m_text);
				ds->getSize(&pos.x,&pos.y);
				cLine->m_height = pos.y;
				cLine->m_pos.x = ((int*)this)[0x3c/4]/2 - pos.x/2 ;
				cLine->m_pos.y = start + (cLine->m_height * offsetStartMultiplyer);
				cLine->m_displayString = ds;
			}
		}
		break;
	case CREDIT_STYLE_POSITION:
		{
			cLine->m_color = m_positionColor;
			
			if(TheGlobalLanguageData && !cLine->m_text.isEmpty())
			{
				DisplayString *ds = TheDisplayStringManager->newDisplayString();
				if(!ds)
					return;
				ds->setFont(reinterpret_cast<FontLibraryBFMERetail *>(TheFontLibrary)->getFont(&reinterpret_cast<GlobalLanguageData *>( TheGlobalLanguageData )->m_creditsPositionFont.name,
														reinterpret_cast<GlobalLanguageData *>( TheGlobalLanguageData )->adjustFontSize(reinterpret_cast<GlobalLanguageData *>( TheGlobalLanguageData )->m_creditsPositionFont.size),
														reinterpret_cast<GlobalLanguageData *>( TheGlobalLanguageData )->m_creditsPositionFont.bold));
				ds->setText(cLine->m_text);
				ds->getSize(&pos.x,&pos.y);
				cLine->m_height = pos.y;
				cLine->m_pos.x = ((int*)this)[0x3c/4]/2 - pos.x/2 ;
				cLine->m_pos.y = start + (cLine->m_height * offsetStartMultiplyer);
				cLine->m_displayString = ds;
			}
		}
		break;
	case CREDIT_STYLE_NORMAL:
	 {
			cLine->m_color = m_normalColor;
			
			if(TheGlobalLanguageData && !cLine->m_text.isEmpty())
			{
				DisplayString *ds = TheDisplayStringManager->newDisplayString();
				if(!ds)
					return;
				ds->setFont(reinterpret_cast<FontLibraryBFMERetail *>(TheFontLibrary)->getFont(&reinterpret_cast<GlobalLanguageData *>( TheGlobalLanguageData )->m_creditsNormalFont.name,
														reinterpret_cast<GlobalLanguageData *>( TheGlobalLanguageData )->adjustFontSize(reinterpret_cast<GlobalLanguageData *>( TheGlobalLanguageData )->m_creditsNormalFont.size),
														reinterpret_cast<GlobalLanguageData *>( TheGlobalLanguageData )->m_creditsNormalFont.bold));
				ds->setText(cLine->m_text);
				ds->getSize(&pos.x,&pos.y);
				cLine->m_height = pos.y;
				cLine->m_pos.x = ((int*)this)[0x3c/4]/2 - pos.x/2 ;
				cLine->m_pos.y = start + (cLine->m_height * offsetStartMultiplyer);
				cLine->m_displayString = ds;
			}
		}
		break;
	case CREDIT_STYLE_COLUMN:
		{
			cLine->m_color = m_normalColor;
			
			if(TheGlobalLanguageData && !cLine->m_text.isEmpty())
			{
				DisplayString *ds = TheDisplayStringManager->newDisplayString();
				if(!ds)
					return;
				ds->setFont(reinterpret_cast<FontLibraryBFMERetail *>(TheFontLibrary)->getFont(&reinterpret_cast<GlobalLanguageData *>( TheGlobalLanguageData )->m_creditsNormalFont.name,
														reinterpret_cast<GlobalLanguageData *>( TheGlobalLanguageData )->adjustFontSize(reinterpret_cast<GlobalLanguageData *>( TheGlobalLanguageData )->m_creditsNormalFont.size),
														reinterpret_cast<GlobalLanguageData *>( TheGlobalLanguageData )->m_creditsNormalFont.bold));
				ds->setText(cLine->m_text);
				ds->getSize(&pos.x,&pos.y);
				cLine->m_height = pos.y;
				cLine->m_pos.x = ((int*)this)[0x3c/4]/2 - pos.x/2 ;
				cLine->m_pos.y = start + (cLine->m_height * offsetStartMultiplyer);
				cLine->m_displayString = ds;
			}
			if(TheGlobalLanguageData && !cLine->m_secondText.isEmpty())
			{
				DisplayString *ds = TheDisplayStringManager->newDisplayString();
				if(!ds)
					return;
				ds->setFont(reinterpret_cast<FontLibraryBFMERetail *>(TheFontLibrary)->getFont(&reinterpret_cast<GlobalLanguageData *>( TheGlobalLanguageData )->m_creditsNormalFont.name,
														reinterpret_cast<GlobalLanguageData *>( TheGlobalLanguageData )->adjustFontSize(reinterpret_cast<GlobalLanguageData *>( TheGlobalLanguageData )->m_creditsNormalFont.size),
														reinterpret_cast<GlobalLanguageData *>( TheGlobalLanguageData )->m_creditsNormalFont.bold));
				ds->setText(cLine->m_secondText);
				ds->getSize(&pos.x,&pos.y);
				cLine->m_height = pos.y;
				cLine->m_pos.x = ((int*)this)[0x3c/4]/2 - pos.x/2 ;
				cLine->m_pos.y = start + (cLine->m_height * offsetStartMultiplyer);
				cLine->m_secondDisplayString = ds;
				
			}
		}
		break;
	case CREDIT_STYLE_BLANK:
		{
			cLine->m_height = m_normalFontHeight;
			cLine->m_pos.y = start + (cLine->m_height * offsetStartMultiplyer);
		}
		break;
	}

	m_displayedCreditLineList.push_back(cLine);

	if(m_creditLineListIt != m_creditLineList.end())
		m_creditLineListIt++;
	
}

