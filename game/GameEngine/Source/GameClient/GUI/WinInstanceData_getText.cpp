// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

// WinInstanceData::getTooltipText (0x00479AB0) and getText (0x00479B00): Zero
// Hour's WinInstanceData.h inlines, compiled here because BFME's DisplayString
// has getText at vtable slot 2 (+0x08) where Zero Hour's header puts it at
// +0x0C. Evidence: W3DDisplayString's table 0x0111FEA8 (slot 0 is
// ??_GW3DDisplayString, 0x006F4F20) has DisplayString::getText (0x00410080)
// in slot 2. The display strings are this+0x19C (text) and +0x1A0 (tooltip).

#include "unicode_string.h"
#include "string_base.h"

inline UnicodeString::UnicodeString(const UnicodeString &stringSrc)
{
	((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(
		*(const StringBase<unsigned short> *)&stringSrc);
}

// The canonical WWLib header omits this static member (see
// SkirmishBattleHonorsConstructor.cpp for the same spelling).
extern UnicodeString BFMEUnicodeEmptyStringMutable;
#pragma comment(linker, "/alternatename:?BFMEUnicodeEmptyStringMutable@@3VUnicodeString@@A=?TheEmptyString@UnicodeString@@2V1@A")

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/DisplayString.h
class DisplayString
{
public:
	virtual void displayStringSlot0( void ) = 0;
	virtual void displayStringSlot1( void ) = 0;
	virtual UnicodeString getText( void ) = 0;				///< vtable +0x08
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/WinInstanceData.h
class WinInstanceData
{
public:
	UnicodeString getTooltipText( void );
	UnicodeString getText( void );

private:
	char m_unmodelled000[0x19c];
	DisplayString *m_text;									///< this+0x19C
	DisplayString *m_tooltip;								///< this+0x1A0
};

// ?getTooltipText@WinInstanceData@@QAE?AVUnicodeString@@XZ
UnicodeString WinInstanceData::getTooltipText( void )
{
	if( m_tooltip )
		return m_tooltip->getText();
	return BFMEUnicodeEmptyStringMutable;
}

// ?getText@WinInstanceData@@QAE?AVUnicodeString@@XZ
UnicodeString WinInstanceData::getText( void )
{
	if( m_text )
		return m_text->getText();
	return BFMEUnicodeEmptyStringMutable;
}
