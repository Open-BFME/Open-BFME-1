// ?postDraw@InGameUI@@UAEXXZ
// partial score=0.987715 date=2026-09-26
// ?postDraw@InGameUI@@UAEXXZ
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Retail ?postDraw@InGameUI@@UAEXXZ at 0x004469F0, 3333 bytes.
//
// Identity: InGameUI vtable 0x010F5B38 slot 75 (+0x12C, VA 0x010F5C64) holds
// ILT 0x00446DAD, which jumps here; the same ILT sits at the same slot of the
// derived table at 0x011206BC.  The body is Zero Hour's InGameUI::postDraw in
// BFME dress: the six-entry message ring, the superweapon timers ("GUI:%s",
// "%ls: ", "%d:%2.2d"), the named timers ("%s %d") and the RMB scroll anchor
// with its two static colours 0xFF00FF00/0xFF000000.

#include "ascii_string.h"
#include "unicode_string.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef float Real;
typedef unsigned char UnsignedByte;
typedef int Color;
typedef unsigned short WideChar;

inline UnicodeString::UnicodeString() { m_text = 0; }
inline UnicodeString::UnicodeString(const wchar_t *s)
{
	((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase((const unsigned short *)s);
}
inline UnicodeString::UnicodeString(const UnicodeString &that)
{
	((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(*(const StringBase<unsigned short> *)&that);
}
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short> *)this)->releaseBuffer(); }
template <> inline const char *StringBase<char>::str() const {return m_data?m_data->data:"";}
template <> inline const unsigned short *StringBase<unsigned short>::str() const {return m_data?m_data->data:(const unsigned short*)L"";}

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <map>
#include <list>

#define SLOT(n) virtual void slot##n() = 0;

class GameFont
{
public:
	UnsignedByte pad[0x10];
	Int height;							///< +0x10
};

// DisplayString, retail slot numbers.
class DisplayString
{
public:
	SLOT(0)
	virtual void setText(UnicodeString text) = 0;			///< +0x04
	SLOT(2) SLOT(3) SLOT(4) SLOT(5)
	virtual void setFont(GameFont *font) = 0;				///< +0x18
	virtual GameFont *getFont() = 0;						///< +0x1C
	SLOT(8) SLOT(9)
	virtual void setColors(Color color, Color dropColor) = 0;	///< +0x28
	SLOT(11) SLOT(12) SLOT(13)
	virtual void draw(Int x, Int y, Int a, Int b) = 0;		///< +0x38
	virtual void getSize(Int *width, Int *height) = 0;		///< +0x3C
	virtual Int getWidth(Int charPos) = 0;					///< +0x40

	void drawColored(Int x, Int y, Color color, Color dropColor)
	{
		setColors(color, dropColor);
		draw(x, y, 1, 1);
	}
};

class Display
{
public:
	SLOT(0) SLOT(1) SLOT(2) SLOT(3) SLOT(4) SLOT(5) SLOT(6) SLOT(7) SLOT(8) SLOT(9) SLOT(10)
	virtual UnsignedInt getWidth() = 0;						///< +0x2C
	virtual UnsignedInt getHeight() = 0;					///< +0x30
	SLOT(13) SLOT(14) SLOT(15) SLOT(16) SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21)
	SLOT(22) SLOT(23) SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29) SLOT(30)
	SLOT(31) SLOT(32) SLOT(33) SLOT(34) SLOT(35) SLOT(36) SLOT(37) SLOT(38) SLOT(39)
	SLOT(40) SLOT(41) SLOT(42) SLOT(43)
	virtual void beginDraw() = 0;							///< +0xB0
	SLOT(45) SLOT(46) SLOT(47)
	virtual void drawFillRectF(Real x, Real y, Real w, Real h, Color color) = 0;	///< +0xC0
	SLOT(49) SLOT(50) SLOT(51) SLOT(52) SLOT(53) SLOT(54)
	virtual void endDraw() = 0;								///< +0xDC

	void drawFillRect(Real x, Real y, Real w, Real h, Color color)
	{
		beginDraw();
		drawFillRectF(x, y, w, h, color);
		endDraw();
	}
};

class View
{
public:
	SLOT(0) SLOT(1) SLOT(2) SLOT(3) SLOT(4) SLOT(5) SLOT(6) SLOT(7) SLOT(8) SLOT(9)
	SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15) SLOT(16)
	virtual Int getHeight() = 0;							///< +0x44
};

class Rva004469F0Slot7
{
public:
	SLOT(0) SLOT(1) SLOT(2) SLOT(3) SLOT(4) SLOT(5) SLOT(6)
	virtual void slot7call() = 0;							///< +0x1C
};

struct ICoord2D { Int x, y; };
struct Coord2D { Real x, y; };

class LookAtTranslator
{
public:
	SLOT(0) SLOT(1)
	virtual const ICoord2D *getRMBScrollAnchor() = 0;		///< +0x08
};

class GameTextInterface
{
public:
	SLOT(0) SLOT(1) SLOT(2) SLOT(3) SLOT(4) SLOT(5) SLOT(6) SLOT(7) SLOT(8) SLOT(9)
	virtual UnicodeString fetch(const char *label, Bool *exists = 0) = 0;	///< +0x28
};

class Object;
typedef std::hash_map<Int,Object*,std::hash<Int>,std::equal_to<Int> > ObjectPtrHash;
class GameLogic {
public:
 __declspec(noinline) Object *findObjectByID(Int id) {
  if(id==0)return 0;
  ObjectPtrHash::iterator it=m_objHash.find(id);
  if(it==m_objHash.end())return 0;
  return (*it).second;
 }
 UnsignedByte pad[0x3c]; UnsignedInt m_frame;
 UnsignedInt getFrame(){return m_frame;}
 UnsignedByte rva40[0xb0-0x40]; ObjectPtrHash m_objHash;
};

class SpecialPowerTemplate;
class SpecialPowerModuleInterface
{
public:
	SLOT(0)
	virtual Bool isReady() const = 0;						///< +0x04
	SLOT(2) SLOT(3)
	virtual UnsignedInt getReadyFrame() const = 0;			///< +0x10
};

class Object
{
public:
	SpecialPowerModuleInterface *getSpecialPowerModule(const SpecialPowerTemplate *t) const;
	UnsignedByte pad[0x90];
	UnsignedByte m_status;									///< +0x90
};

class Overridable {
public:
 Overridable *friend_getFinalOverride() {
  if(m_nextOverride) return m_nextOverride->friend_getFinalOverride();
  return this;
 }
 const Overridable *friend_getFinalOverride() const {
  if(m_nextOverride) return m_nextOverride->friend_getFinalOverride();
  return this;
 }
 UnsignedByte pad[4]; Overridable *m_nextOverride;
};

class SpecialPowerTemplate : public Overridable
{
public:
	UnsignedByte pad2[0x115 - 8];
	Bool isSharedNSync() const {
  const SpecialPowerTemplate *self=this;
  return ((const SpecialPowerTemplate*)self->friend_getFinalOverride())->m_sharedNSync;
 }
 Bool m_sharedNSync;										///< +0x115
};

class SuperweaponInfo
{
public:
	void setFont(const AsciiString &font, Int pointSize, Bool bold);
	void setText(const UnicodeString &name, const UnicodeString &time);
	void drawName(Int x, Int y, Color color, Color dropColor);
	void drawTime(Int x, Int y, Color color, Color dropColor);

	UnsignedByte pad0[4];
	DisplayString *m_nameDisplayString;						///< +0x04
	DisplayString *m_timeDisplayString;						///< +0x08
	Color m_color;											///< +0x0C
	const SpecialPowerTemplate *m_powerTemplate;			///< +0x10
	UnsignedByte pad14[4];
	Int m_id;												///< +0x18
	UnsignedInt m_timestamp;								///< +0x1C
	Bool m_hiddenByScript;									///< +0x20
	Bool m_hiddenByScience;									///< +0x21
	Bool m_ready;											///< +0x22
	Bool m_forceUpdateText;									///< +0x23
};

struct NamedTimerInfo
{
	UnsignedByte pad0[8];
	UnicodeString timerText;								///< +0x08
	DisplayString *displayString;							///< +0x0C
	Int timestamp;											///< +0x10
	Color color;											///< +0x14
	Bool isCountdown;										///< +0x18
};

struct ScriptCounter { Int m_value; };

class ScriptEngine
{
public:
	ScriptCounter *getCounter(AsciiString name);
};

class GlobalLanguageData
{
public:
	Int adjustFontSize(Int size);
};

class FontLibrary
{
public:
	GameFont *getFont(AsciiString *name, Real pointSize, UnsignedByte bold);
};

extern Display *TheDisplay;
extern View *TheTacticalView;
extern GameLogic *TheBfmeGameLogic;
extern GameTextInterface *TheGameText;
extern ScriptEngine *TheScriptEngine;
extern GlobalLanguageData *g_bfmeGlobalWR;
extern FontLibrary *TheFontLibrary;
extern LookAtTranslator *g_bfmeSingletonVVD;

void GameGetColorComponents(Color color, UnsignedByte *r, UnsignedByte *g, UnsignedByte *b, UnsignedByte *a);
inline Color GameMakeColor(UnsignedByte r, UnsignedByte g, UnsignedByte b, UnsignedByte a)
{
	return (a << 24) | (r << 16) | (g << 8) | b;
}

typedef std::list<SuperweaponInfo*> SuperweaponList;
typedef std::map<AsciiString,SuperweaponList> SuperweaponMap;
typedef std::map<AsciiString,NamedTimerInfo*> NamedTimerMap;

struct UIMessage
{
	UnicodeString fullText;
	DisplayString *displayString;
	UnsignedInt timestamp;
	Color color;
};

class InGameUI
{
public:
	virtual void postDraw();

	UnsignedByte pad0[0x8];
	Bool m_superweaponHiddenByScript;								///< +0x00C
	UnsignedByte pad1[0x56c - 0xd];
	UIMessage m_uiMessages[6];								///< +0x56C
	SuperweaponMap m_superweapons[32];						///< +0x5CC

	Coord2D m_superweaponPosition;	///< +0x74C
	Real m_superweaponFlashDuration;						///< +0x754
	AsciiString m_superweaponNormalFont;					///< +0x758
	Int m_superweaponNormalPointSize;						///< +0x75C
	Bool m_superweaponNormalBold;							///< +0x760
	AsciiString m_superweaponReadyFont;						///< +0x764
	Int m_superweaponReadyPointSize;						///< +0x768
	Bool m_superweaponReadyBold;							///< +0x76C
	UnsignedInt m_superweaponLastFlashFrame;				///< +0x770
	Color m_superweaponFlashColor;							///< +0x774
	Bool m_superweaponUsedFlashColor;						///< +0x778
	NamedTimerMap m_namedTimers;								///< +0x77C header
	Coord2D m_namedTimerPosition;	///< +0x788
	Bool m_namedTimerCentered;								///< +0x790
	Real m_namedTimerFlashDuration;							///< +0x794
	UnsignedInt m_namedTimerLastFlashFrame;					///< +0x798
	Color m_namedTimerFlashColor;							///< +0x79C
	Bool m_namedTimerUsedFlashColor;						///< +0x7A0
	Bool m_showNamedTimers;									///< +0x7A1
	AsciiString m_namedTimerNormalFont;						///< +0x7A4
	Int m_namedTimerNormalPointSize;						///< +0x7A8
	Bool m_namedTimerNormalBold;							///< +0x7AC
	UnsignedByte pad4[7];
	AsciiString m_namedTimerReadyFont;						///< +0x7B4 (7B0 unused)
	Int m_namedTimerReadyPointSize;							///< +0x7B8
	Bool m_namedTimerReadyBold;								///< +0x7BC
	UnsignedByte pad5[0x81c - 0x7bd];
	Rva004469F0Slot7 *m_81C;									///< +0x81C
	UnsignedByte pad6[0x839 - 0x820];
	Bool m_messagesOn;										///< +0x839
	UnsignedByte pad7[0x844 - 0x83a];
	ICoord2D m_messagePosition;	///< +0x844
	UnsignedByte pad8[0x12bc - 0x84c];
	Bool m_drawRMBScrollAnchor;								///< +0x12BC
};

void InGameUI::postDraw()
{
 Int startX,startY;
	if (m_messagesOn)
	{
		Int i, x, y;
		Color dropColor;
		UnsignedByte r, g, b, a;
		y = m_messagePosition.y;
		for (i = 6 - 1; i >= 0; i--)
		{
			DisplayString *ds = m_uiMessages[i].displayString;
			if (ds)
			{
				x = m_messagePosition.x;
				if (x < 0)
				{
					Int width, height;
					ds->getSize(&width, &height);
					x += TheDisplay->getWidth() - width;
				}
				GameGetColorComponents(m_uiMessages[i].color, &r, &g, &b, &a);
				dropColor=GameMakeColor(0,0,0,a);
				ds->setColors(m_uiMessages[i].color, dropColor);
				ds->draw(x, y, 1, 1);
				y += ds->getFont()->height;
			}
		}
	}

	m_81C->slot7call();

	if (TheBfmeGameLogic->getFrame() > 0 && !m_superweaponHiddenByScript)
	{
		startX = (Int)(m_superweaponPosition.x * TheDisplay->getWidth());
		startY = (Int)(m_superweaponPosition.y * TheDisplay->getHeight());
		Int bottomMargin = (Int)((Real)TheTacticalView->getHeight() * 0.82f);
		Bool marginExceeded = false;

		for (Int i = 0; i < 32 && !marginExceeded; ++i)
		{
			for (SuperweaponMap::iterator mapIt=m_superweapons[i].begin(); mapIt!=m_superweapons[i].end() && !marginExceeded; ++mapIt)
			{
				AsciiString templateName = mapIt->first;
				for (SuperweaponList::iterator listIt=mapIt->second.begin();listIt!=mapIt->second.end();++listIt)
				{
					SuperweaponInfo *info = *listIt;
					if (info && !info->m_hiddenByScript && !info->m_hiddenByScience)
					{
						if (startY >= bottomMargin)
						{
							UnicodeString ellipsis;
							ellipsis.format(L"...");
							info->m_nameDisplayString->setText(ellipsis);
							info->m_timeDisplayString->setText(ellipsis);
							info->setFont(m_superweaponReadyFont, m_superweaponNormalPointSize, m_superweaponNormalBold);
							Color color = m_superweaponFlashColor ? m_superweaponFlashColor : info->m_color;
							info->m_timeDisplayString->setColors(color, GameMakeColor(0, 0, 0, 255));
							info->m_timeDisplayString->draw(startX - info->m_nameDisplayString->getWidth(-1), startY, 1, 1);
							marginExceeded = true;
							break;
						}

						Object *owningObject = TheBfmeGameLogic->findObjectByID(info->m_id);
						if (!owningObject || (owningObject->m_status & 4))
							continue;
						SpecialPowerModuleInterface *module = owningObject->getSpecialPowerModule(info->m_powerTemplate);
						if (!module)
							continue;

						Bool isReady = module->isReady();
						UnsignedInt readySecs;
						if (module->getReadyFrame() < TheBfmeGameLogic->getFrame())
							readySecs = 0;
						else
							readySecs = (module->getReadyFrame() - TheBfmeGameLogic->getFrame()) / 5;

						if (readySecs != info->m_timestamp || isReady != info->m_ready || info->m_forceUpdateText)
						{
							if (isReady)
								info->setFont(m_superweaponReadyFont, m_superweaponReadyPointSize, m_superweaponReadyBold);
							else if (info->m_timestamp == 0)
								info->setFont(m_superweaponNormalFont, m_superweaponNormalPointSize, m_superweaponNormalBold);

							info->m_ready = isReady;
							Int min = (Int)readySecs / 60;
							info->m_timestamp = readySecs;
							info->m_forceUpdateText = false;
							Int sec = readySecs - min * 60;
							AsciiString strIndex;
							strIndex.format("GUI:%s", templateName.str());
							UnicodeString name, time;
							name.format(L"%ls: ", TheGameText->fetch(strIndex.str()).str());
							time.format(L"%d:%2.2d", min, sec);
							info->setText(name, time);
						}

						if (isReady && m_superweaponFlashDuration != 0.0f)
						{
							if (TheBfmeGameLogic->getFrame() >= m_superweaponLastFlashFrame + (Int)m_superweaponFlashDuration)
							{
								m_superweaponUsedFlashColor = !m_superweaponUsedFlashColor;
								m_superweaponLastFlashFrame = TheBfmeGameLogic->getFrame();
							}
							info->drawName(startX, startY, m_superweaponUsedFlashColor ? 0 : m_superweaponFlashColor, GameMakeColor(0, 0, 0, 255));
							info->drawTime(startX, startY, m_superweaponUsedFlashColor ? 0 : m_superweaponFlashColor, GameMakeColor(0, 0, 0, 255));
						}
						else
						{
							info->drawName(startX, startY, 0, GameMakeColor(0, 0, 0, 255));
							info->drawTime(startX, startY, 0, GameMakeColor(0, 0, 0, 255));
						}

						startY = (Int)(info->m_nameDisplayString->getFont()->height + (Real)startY);

						if (info->m_powerTemplate->isSharedNSync())
							break;
					}
				}
			}
		}
	}

	if (TheBfmeGameLogic->getFrame() > 0 && m_showNamedTimers)
	{
		Bool reverseXDir = !m_namedTimerCentered && m_namedTimerPosition.x >= 0.5f;
		startX = (Int)(m_namedTimerPosition.x * TheDisplay->getWidth());
		startY = (Int)(m_namedTimerPosition.y * TheDisplay->getHeight());
		for (NamedTimerMap::iterator mapIt=m_namedTimers.begin();mapIt!=m_namedTimers.end();++mapIt)
		{
			AsciiString timerName = mapIt->first;
			NamedTimerInfo *info = mapIt->second;
			if (info)
			{
				UnicodeString line;
				Int framesLeft = 0;
				ScriptCounter *counter = TheScriptEngine->getCounter(timerName);
				if (counter)
					framesLeft = counter->m_value;
				UnsignedInt readyFrame = TheBfmeGameLogic->getFrame();
				if (framesLeft > 0)
					readyFrame += framesLeft;
				Int readySecs = (Int)((readyFrame - TheBfmeGameLogic->getFrame()) * (1.0f / 5.0f));
				if ((info->isCountdown && readySecs != info->timestamp) || (!info->isCountdown && framesLeft != info->timestamp))
				{
					if (!readySecs && info->isCountdown)
						info->displayString->setFont(TheFontLibrary->getFont(&m_namedTimerReadyFont,
							(Real)g_bfmeGlobalWR->adjustFontSize(m_namedTimerReadyPointSize), m_namedTimerReadyBold));
					else if (info->timestamp == 0 || info->isCountdown)
						info->displayString->setFont(TheFontLibrary->getFont(&m_namedTimerNormalFont,
							(Real)g_bfmeGlobalWR->adjustFontSize(m_namedTimerNormalPointSize), m_namedTimerNormalBold));

					Int min = readySecs / 60;
					Int sec = readySecs - min * 60;
					if (!info->isCountdown)
					{
						line.format(L"%s %d", info->timerText.str(), framesLeft);
						info->timestamp = framesLeft;
					}
					else
					{
						info->timestamp = readySecs;
						UnicodeString separator(L":");
						if (g_bfmeGlobalWR)
							separator.translate(*(AsciiString *)((UnsignedByte *)g_bfmeGlobalWR + 0x10));
						if (sec >= 10)
							line.format(L"%s %d%s%d", info->timerText.str(), min, separator.str(), sec);
						else
							line.format(L"%s %d%s0%d", info->timerText.str(), min, separator.str(), sec);
					}
					info->displayString->setText(line);
				}

				Int drawX = startX;
				if (m_namedTimerCentered)
					drawX -= info->displayString->getWidth(-1) / 2;
				else if (reverseXDir)
					drawX -= info->displayString->getWidth(-1);

				if (!readySecs && info->isCountdown)
				{
					if (m_namedTimerFlashDuration != 0.0f)
					{
						if (TheBfmeGameLogic->getFrame() >= m_namedTimerLastFlashFrame + (Int)m_namedTimerFlashDuration)
						{
							m_namedTimerUsedFlashColor = !m_namedTimerUsedFlashColor;
							m_namedTimerLastFlashFrame = TheBfmeGameLogic->getFrame();
						}
                        info->displayString->setColors(m_namedTimerUsedFlashColor ? info->color : m_namedTimerFlashColor, GameMakeColor(0,0,0,255));
                        info->displayString->draw(drawX,startY,1,1);
					}
					else
					{
						{
						info->displayString->setColors(info->color, GameMakeColor(0, 0, 0, 255));
						info->displayString->draw(drawX, startY, 1, 1);
						}
					}
				}
				else
				{
					{
					info->displayString->setColors(info->color, GameMakeColor(0, 0, 0, 255));
					info->displayString->draw(drawX, startY, 1, 1);
					}
				}
				startY -= info->displayString->getFont()->height;
			}
		}
	}

	if (g_bfmeSingletonVVD && m_drawRMBScrollAnchor)
	{
		const ICoord2D *anchor = g_bfmeSingletonVVD->getRMBScrollAnchor();
		if (anchor)
		{
			static const Color mainColor = GameMakeColor(0, 255, 0, 255);
			static const Color dropColor = GameMakeColor(0, 0, 0, 255);
			TheDisplay->drawFillRect(anchor->x - 9, anchor->y - 3, 19, 7, dropColor);
			TheDisplay->drawFillRect(anchor->x - 3, anchor->y - 9, 7, 19, dropColor);
			TheDisplay->drawFillRect(anchor->x - 8, anchor->y - 2, 17, 5, mainColor);
			TheDisplay->drawFillRect(anchor->x - 2, anchor->y - 8, 5, 17, mainColor);
		}
	}
}
