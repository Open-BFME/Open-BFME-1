#pragma once
//
// BFME's MultiplayerSettings, which is NOT Zero Hour's.
//
// MultiplayerColorDefinition below is unchanged from ZH, and retail agrees:
// INI::parseMultiplayerColorDefinition at 0x000C2690 reaches m_rgbValue at +4
// and m_rgbValueNight at +0x14, which is exactly where ZH's
// AsciiString/RGBColor/Color/RGBColor/Color ordering puts them.
//
// MultiplayerSettings is a different shape, and two independent readings of the
// image fix it:
//
//   * its size. INI::parseMultiplayerSettingsDefinition news the singleton with
//     `push 0x88; call operator new`, so the object is exactly 136 bytes. ZH's
//     compiles to 0x90.
//   * the offsets its INI fields write to, decoded from the retail FieldParse
//     table at 0x0107F718 -- see docs/ini_schema.md, which reads them out of the
//     image rather than inferring them.
//
// Those offsets say BFME reordered the class rather than appending to it:
// StartCountdownTimer and MaxBeaconsPerPlayer sit at 0x10/0x14 where ZH has
// 0x0C/0x10, and ZH's two InitialCredits ints (m_initialCreditsMin/Max) have
// become five at 0x1C -- VeryLow, Low, Medium, High, VeryHigh, one per money
// setting the lobby offers.
//
// Everything from 0x30 on is deliberately anonymous. The colour list, its count
// and the observer/random colours live there, but no INI field writes into them
// so nothing in the image fixes their individual offsets; only the total does.
// Naming them would be invention, and since every member address here is a DIR32
// the verifier fills in from the target, invented offsets would still
// byte-verify. The pad is the honest version.
//
#include "GameClient/Color.h"

struct FieldParse;
class MultiplayerSettings;

class MultiplayerColorDefinition
{
public:
	MultiplayerColorDefinition();
	static const FieldParse m_colorFieldParseTable[];
	const FieldParse *getFieldParse( void ) const { return m_colorFieldParseTable; }

	inline AsciiString getTooltipName(void) const { return m_tooltipName; };
	inline RGBColor getRGBValue(void) const { return m_rgbValue; };
	inline RGBColor getRGBNightValue(void) const { return m_rgbValueNight; };
	inline Color getColor(void) const { return m_color; }
	inline Color getNightColor(void) const { return m_colorNight; }
	void setColor( RGBColor rgb );
	void setNightColor( RGBColor rgb );

	MultiplayerColorDefinition * operator =(const MultiplayerColorDefinition& other);

private:
	AsciiString m_tooltipName;		// 0x00
	RGBColor m_rgbValue;			// 0x04
	Color m_color;					// 0x10
	RGBColor m_rgbValueNight;		// 0x14
	Color m_colorNight;				// 0x20
};

typedef std::map<Int, MultiplayerColorDefinition> MultiplayerColorList;

class MultiplayerSettings : public SubsystemInterface
{
public:

	MultiplayerSettings( void );

	virtual void init() { }
	virtual void update() { }
	virtual void reset() { }

	static const FieldParse m_multiplayerSettingsFieldParseTable[];
	const FieldParse *getFieldParse( void ) const { return m_multiplayerSettingsFieldParseTable; }

	MultiplayerColorDefinition * getColor(Int which);
	MultiplayerColorDefinition * findMultiplayerColorDefinitionByName(AsciiString name);
	MultiplayerColorDefinition * newMultiplayerColorDefinition(AsciiString name);

	inline Int getStartCountdownTimerSeconds( void ) { return m_startCountdownTimerSeconds; }
	inline Int getMaxBeaconsPerPlayer( void ) { return m_maxBeaconsPerPlayer; }
	inline Bool isShroudInMultiplayer( void ) { return m_isShroudInMultiplayer; }
	inline Bool showRandomPlayerTemplate( void ) { return m_showRandomPlayerTemplate; }
	inline Bool showRandomStartPos( void ) { return m_showRandomStartPos; }
	inline Bool showRandomColor( void ) { return m_showRandomColor; }

	// checkForDuplicateColors (0x00386520) inlines this and reaches m_numColors
	// through [ecx+0x3c] and the tree's node count through [ecx+0x34]. Those are
	// literal displacements, not DIR32 slots, so unlike the rest of the pad below
	// these two offsets are fixed by the image and naming them is not invention.
	inline Int getNumColors( void )
	{
		if (m_numColors == 0) {
			m_numColors = m_colorList.size();
		}
		return m_numColors;
	}

private:
	// The SubsystemInterface base is 8 bytes -- vptr plus its AsciiString
	// m_name at 0x04 -- so the first member of our own is at 0x08.
	char m_unknown08[ 0x08 ];					// 0x08
	Int m_startCountdownTimerSeconds;			// 0x10  StartCountdownTimer
	Int m_maxBeaconsPerPlayer;					// 0x14  MaxBeaconsPerPlayer
	Bool m_isShroudInMultiplayer;				// 0x18  UseShroud
	Bool m_showRandomPlayerTemplate;			// 0x19  ShowRandomPlayerTemplate
	Bool m_showRandomStartPos;					// 0x1A  ShowRandomStartPos
	Bool m_showRandomColor;						// 0x1B  ShowRandomColor
	Int m_initialCredits[ 5 ];					// 0x1C  VeryLow Low Medium High VeryHigh
	MultiplayerColorList m_colorList;			// 0x30  node count lands at 0x34
	Int m_numColors;							// 0x3c
	char m_unknown40[ 0x88 - 0x40 ];			// 0x40  observer/random colours
};

// singleton
extern MultiplayerSettings *TheMultiplayerSettings;
