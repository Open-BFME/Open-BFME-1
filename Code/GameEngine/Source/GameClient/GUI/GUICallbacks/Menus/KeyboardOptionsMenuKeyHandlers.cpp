// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stringbaseascii /Ireference/shims/displaystring /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /ICode/Libraries/Source/WWVegas/WWLib
// stlport
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE

#include "string_base.h"

#define UNICODESTRING_H
class AsciiString;

class UnicodeString
{
public:
	static UnicodeString TheEmptyString;

	UnicodeString() { m_text = 0; }
	UnicodeString( const UnicodeString &that )
	{
		((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase( *(const StringBase<unsigned short> *)&that );
	}
	explicit UnicodeString( const unsigned short *str )
	{
		((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase( str );
	}
	~UnicodeString();

	UnicodeString &operator=( const UnicodeString &that )
	{
		((StringBase<unsigned short> *)this)->set( *(const StringBase<unsigned short> *)&that );
		return *this;
	}

	int getLength() const { return ((const StringBase<unsigned short> *)this)->getLength(); }
	unsigned short getCharAt( int index ) const
	{
		return m_text ? ((const unsigned short *)((const char *)m_text + 8))[index] : 0;
	}
	const unsigned short *str() const { return ((const StringBase<unsigned short> *)this)->str(); }
	void set( const UnicodeString &that ) { ((StringBase<unsigned short> *)this)->set( *(const StringBase<unsigned short> *)&that ); }
	void concat( const UnicodeString &that )
	{
		const int length = that.m_text ? *(const unsigned short *)((const char *)that.m_text + 4) : 0;
		static const unsigned short empty[1] = { 0 };
		const unsigned short *text = that.m_text ? (const unsigned short *)((const char *)that.m_text + 8) : empty;
		((StringBase<unsigned short> *)this)->concat( text, length );
	}
	int compare( const UnicodeString &that ) const { return ((const StringBase<unsigned short> *)this)->compare( *(const StringBase<unsigned short> *)&that ); }
	int compareNoCase( const UnicodeString &that ) const { return ((const StringBase<unsigned short> *)this)->compareNoCase( *(const StringBase<unsigned short> *)&that ); }

private:
	unsigned short *m_text;
};

inline bool operator==( const UnicodeString &a, const UnicodeString &b )
{
	return a.compare( b ) == 0;
}

#include "PreRTS.h"

#include "GameClient/DisplayString.h"

class GameWindow;

typedef struct _EntryData
{
	DisplayString *text;
	DisplayString *sText;
	DisplayString *constructText;
	Bool secretText;
	Bool numericalOnly;
	Bool alphaNumericalOnly;
	Bool aSCIIOnly;
	Short maxTextLen;
	Bool receivedUnichar;
	Bool drawTextFromStart;
	GameWindow *constructList;
	void *bfmeEntryPad;
	UnsignedShort charPos;
	UnsignedShort conCharPos;
} EntryData;

extern Bool shiftDown;
extern Bool altDown;
extern Bool ctrlDown;
extern Bool absolute;
extern UnicodeString alt;
extern UnicodeString ctrl;
extern UnicodeString shift;

void setKeyDown( UnicodeString mod, Bool b );

void doKeyUp( EntryData *e, UnicodeString mod )
{
	char c = e->text->getText().getCharAt( e->text->getTextLength() - 1 );
	if( c == '+' )
	{
		if( altDown && ctrlDown && shiftDown )
		{
			if( mod == shift )
			{
				UnicodeString temp = alt;
				((StringBase<unsigned short> *)&temp)->concat( *(const StringBase<unsigned short> *)&ctrl );
				e->text->setText( temp );
				e->charPos = e->text->getTextLength();
				setKeyDown( mod, false );
			}
			else if( mod == alt )
			{
				UnicodeString temp = ctrl;
				((StringBase<unsigned short> *)&temp)->concat( *(const StringBase<unsigned short> *)&shift );
				e->text->setText( temp );
				e->charPos = e->text->getTextLength();
				setKeyDown( mod, false );
			}
			else if( mod == ctrl )
			{
				UnicodeString temp = alt;
				((StringBase<unsigned short> *)&temp)->concat( *(const StringBase<unsigned short> *)&shift );
				e->text->setText( temp );
				e->charPos = e->text->getTextLength();
				setKeyDown( mod, false );
			}
		}
		else if( altDown && ctrlDown )
		{
			if( mod == alt )
			{
				e->text->setText( ctrl );
				e->charPos = e->text->getTextLength();
				setKeyDown( mod, false );
			}
			else if( mod == ctrl )
			{
				e->text->setText( ctrl );
				e->charPos = e->text->getTextLength();
				setKeyDown( mod, false );
			}
		}
		else if( altDown && shiftDown )
		{
			if( mod == alt )
			{
				e->text->setText( shift );
				e->charPos = e->text->getTextLength();
				setKeyDown( mod, false );
			}
			else if( mod == shift )
			{
				e->text->setText( alt );
				e->charPos = e->text->getTextLength();
				setKeyDown( mod, false );
			}
		}
		else if( ctrlDown && shiftDown )
		{
			if( mod == ctrl )
			{
				e->text->setText( shift );
				e->charPos = e->text->getTextLength();
				setKeyDown( mod, false );
			}
			else if( mod == shift )
			{
				e->text->setText( ctrl );
				e->charPos = e->text->getTextLength();
				setKeyDown( mod, false );
			}
		}
		else
		{
			e->text->setText( UnicodeString::TheEmptyString );
			e->sText->setText( UnicodeString::TheEmptyString );
			e->charPos = e->text->getTextLength();
			setKeyDown( mod, false );
		}
	}
	else
	{
		absolute = true;
	}
}

void doKeyDown( EntryData *e, UnicodeString mod )
{
	if( e->text->getTextLength() <= 1 )
	{
		e->text->setText( mod );
		e->sText->setText( mod );
		e->charPos = e->text->getTextLength();
		setKeyDown( mod, true );
	}
	else
	{
		char c = e->text->getText().getCharAt( e->text->getTextLength() - 1 );
		if( c != '+' && absolute )
		{
			e->text->setText( mod );
			e->sText->setText( mod );
			e->charPos = e->text->getTextLength();
			setKeyDown( shift, false );
			setKeyDown( alt, false );
			setKeyDown( ctrl, false );
			setKeyDown( mod, true );
			absolute = false;
		}
		else
		{
			if( mod == shift && shiftDown )
			{
			}
			else if( mod == ctrl && ctrlDown )
			{
			}
			else if( mod == alt && altDown )
			{
			}
			else if( altDown && ctrlDown )
			{
				UnicodeString temp = alt;
				((StringBase<unsigned short> *)&temp)->concat( *(const StringBase<unsigned short> *)&ctrl );
				((StringBase<unsigned short> *)&temp)->concat( *(const StringBase<unsigned short> *)&mod );
				e->text->setText( temp );
				e->charPos = e->text->getTextLength();
				setKeyDown( mod, true );
			}
			else if( altDown && shiftDown )
			{
				UnicodeString temp = alt;
				((StringBase<unsigned short> *)&temp)->concat( *(const StringBase<unsigned short> *)&ctrl );
				((StringBase<unsigned short> *)&temp)->concat( *(const StringBase<unsigned short> *)&shift );
				e->text->setText( temp );
				e->charPos = e->text->getTextLength();
				setKeyDown( mod, true );
			}
			else if( altDown )
			{
				UnicodeString temp = alt;
				((StringBase<unsigned short> *)&temp)->concat( *(const StringBase<unsigned short> *)&mod );
				e->text->setText( temp );
				e->charPos = e->text->getTextLength();
				setKeyDown( mod, true );
			}
			else if( ctrlDown && shiftDown )
			{
				UnicodeString temp = alt;
				((StringBase<unsigned short> *)&temp)->concat( *(const StringBase<unsigned short> *)&ctrl );
				((StringBase<unsigned short> *)&temp)->concat( *(const StringBase<unsigned short> *)&shift );
				e->text->setText( temp );
				e->charPos = e->text->getTextLength();
				setKeyDown( mod, true );
			}
			else if( ctrlDown )
			{
				if( mod == alt )
				{
					UnicodeString temp = mod;
					((StringBase<unsigned short> *)&temp)->concat( *(const StringBase<unsigned short> *)&ctrl );
					e->text->setText( temp );
					e->charPos = e->text->getTextLength();
					setKeyDown( mod, true );
				}
				else
				{
					UnicodeString temp = ctrl;
					((StringBase<unsigned short> *)&temp)->concat( *(const StringBase<unsigned short> *)&mod );
					e->text->setText( temp );
					e->charPos = e->text->getTextLength();
					setKeyDown( mod, true );
				}
			}
			else if( shiftDown )
			{
				UnicodeString temp = mod;
				((StringBase<unsigned short> *)&temp)->concat( *(const StringBase<unsigned short> *)&shift );
				e->text->setText( temp );
				e->charPos = e->text->getTextLength();
				setKeyDown( mod, true );
			}
		}
	}
}
