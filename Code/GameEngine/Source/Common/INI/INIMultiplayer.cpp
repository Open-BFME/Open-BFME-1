// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/multiplayer /Ireference/shims/ini /Ireference/shims/iniexception /Ireference/shims/ini_noinline /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// readable body of ??0MultiplayerSettings@@: Code/GameEngine/Source/Common/MultiplayerSettings.cpp
//
// The "MultiplayerSettings" and "MultiplayerColor" blocks. Both are Zero Hour's
// INIMultiplayer.cpp bodies unchanged, and MultiplayerColorDefinition's layout
// is identical too: retail reaches m_rgbValue at +4 and m_rgbValueNight at +0x14,
// which is exactly where ZH's AsciiString/RGBColor/Color/RGBColor/Color ordering
// puts them.
//
// MultiplayerSettings itself is NOT ZH's -- retail news 0x88 bytes for it where
// ZH compiles to 0x90, and its INI fields land at different offsets. The BFME
// layout, decoded from the retail field table, is in reference/shims/multiplayer.
#include "PreRTS.h"
#include "Common/INI.h"
#include "GameClient/Color.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MultiplayerSettings.h
class MultiplayerColorDefinition
{
public:
	MultiplayerColorDefinition();
	static const FieldParse m_colorFieldParseTable[];
	const FieldParse *getFieldParse() const { return m_colorFieldParseTable; }
	AsciiString getTooltipName() const;
	RGBColor getRGBValue() const { return m_rgbValue; }
	RGBColor getRGBNightValue() const { return m_rgbValueNight; }
	void setColor( RGBColor rgb );
	void setNightColor( RGBColor rgb );
	MultiplayerColorDefinition *operator=( const MultiplayerColorDefinition &other );

private:
	AsciiString m_tooltipName;
	RGBColor m_rgbValue;
	Color m_color;
	RGBColor m_rgbValueNight;
	Color m_colorNight;
};

typedef std::map<Int, MultiplayerColorDefinition> MultiplayerColorList;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MultiplayerSettings.h
class MultiplayerSettings : public SubsystemInterface
{
public:
	MultiplayerSettings();
	virtual void init() {}
	virtual void update() {}
	virtual void reset() {}
	static const FieldParse m_multiplayerSettingsFieldParseTable[];
	const FieldParse *getFieldParse() const { return m_multiplayerSettingsFieldParseTable; }
	MultiplayerColorDefinition *findMultiplayerColorDefinitionByName( AsciiString name );
	MultiplayerColorDefinition *newMultiplayerColorDefinition( AsciiString name );
	Int getNumColors()
	{
		if( m_numColors == 0 ) m_numColors = m_colorList.size();
		return m_numColors;
	}

private:
	Int m_unknown08;
	Int m_unknown0C;
	Int m_startCountdownTimerSeconds;
	Int m_maxBeaconsPerPlayer;
	Bool m_isShroudInMultiplayer;
	Bool m_showRandomPlayerTemplate;
	Bool m_showRandomStartPos;
	Bool m_showRandomColor;
	Int m_initialCredits[ 5 ];
	MultiplayerColorList m_colorList;
	Int m_numColors;
	MultiplayerColorDefinition m_observerColor;
	MultiplayerColorDefinition m_randomColor;
};

extern MultiplayerSettings *TheMultiplayerSettings;

MultiplayerSettings::MultiplayerSettings()
{
	m_unknown08 = 0;
	m_startCountdownTimerSeconds = 0;
	m_numColors = 0;
	m_unknown0C = 10000;
	m_maxBeaconsPerPlayer = 3;
	m_isShroudInMultiplayer = true;
	m_showRandomPlayerTemplate = true;
	m_showRandomStartPos = true;
	m_showRandomColor = true;
	m_initialCredits[ 0 ] = 500;
	m_initialCredits[ 1 ] = 1000;
	m_initialCredits[ 2 ] = 1500;
	m_initialCredits[ 3 ] = 2000;
	m_initialCredits[ 4 ] = 2500;
}

void INI::parseMultiplayerSettingsDefinition( INI* ini )
{
	if( TheMultiplayerSettings )
	{
	}
	else
	{
		TheMultiplayerSettings = new MultiplayerSettings;
	}

	ini->initFromINI( TheMultiplayerSettings, TheMultiplayerSettings->getFieldParse() );
}

void INI::parseMultiplayerColorDefinition( INI* ini )
{
	const char *c;
	AsciiString name;
	MultiplayerColorDefinition *multiplayerColorDefinition;

	c = ini->getNextToken();
	// BFME assigns rather than calling set(c): retail inlines strlen and calls
	// the two-argument set, which is what operator=(const char *) expands to.
	name = c;

	multiplayerColorDefinition = TheMultiplayerSettings->findMultiplayerColorDefinitionByName( name );
	if( multiplayerColorDefinition == NULL )
		multiplayerColorDefinition = TheMultiplayerSettings->newMultiplayerColorDefinition( name );

	ini->initFromINI( multiplayerColorDefinition, multiplayerColorDefinition->getFieldParse() );

	multiplayerColorDefinition->setColor(multiplayerColorDefinition->getRGBValue());
	multiplayerColorDefinition->setNightColor(multiplayerColorDefinition->getRGBNightValue());
}
