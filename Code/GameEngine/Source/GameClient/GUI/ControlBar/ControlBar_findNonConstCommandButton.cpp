// cl: /DNDEBUG /MD /EHsc
// readable body of ?findNonConstCommandButton@ControlBar@@IAEPAVCommandButton@@ABVAsciiString@@@Z: Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar.cpp
// Open-BFME: ControlBar::findNonConstCommandButton, retail 0x004A01B0,
// 151 bytes.
//
// The reference's four lines.  The body is in ControlBar.cpp too, but there the
// string comparison is a call; retail inlines it, so the class is spelled here
// instead and the comparison written where the compiler can see it.
//
// The string is Code/Libraries/Source/WWVegas/WWLib/string_base.h's shape --
// ref count, length and capacity ahead of the characters, so the length is the
// word at data+4 and the text starts at data+8 -- and the comparison is that
// file's own compare(): memcmp over the shorter length, then the length
// difference.
//
// Offsets: the button list at ControlBar+0x28, a button's name at +0x0C, its
// next at +0x14, and the override chain at +0x04, whose getFinalOverride is the
// one out-of-line call left in the body.

#define _DLL
#include <string.h>

typedef int Int;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	Int compare(const char *str, Int len) const
	{
		const Int myLen = m_data ? m_data->length : 0;
		const char *data = m_data ? &m_data->data[0] : "";
		Int result = memcmp(data, str, myLen < len ? myLen : len);
		if (result != 0)
			return result;
		return myLen - len;
	}

	Int compare(const AsciiString &str) const
	{
		const Int len = str.m_data ? str.m_data->length : 0;
		const char *data = str.m_data ? &str.m_data->data[0] : "";
		return compare(data, len);
	}

private:
	struct Header {
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		char data[1];
	};

	Header *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	const Overridable *getFinalOverride(void) const;	// ILT 0x000022BB
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class CommandButton
{
public:
	const AsciiString &getName(void) const { return m_name; }
	const CommandButton *getNext(void) const { return m_next; }

	// One level of the override walk is inline here: only a button that has an
	// override at +0x04 reaches the out-of-line chain walk.
	const CommandButton *getFinalOverride(void) const
	{
		if (m_override)
			return (const CommandButton *)m_override->getFinalOverride();
		return this;
	}

private:
	unsigned char m_unmodelled_000[4];			// +0x00
	const Overridable *m_override;				// +0x04
	unsigned char m_unmodelled_008[0x0C - 0x08];
	AsciiString m_name;					// +0x0C
	unsigned char m_unmodelled_010[0x14 - 0x10];
	const CommandButton *m_next;				// +0x14
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class ControlBar
{
protected:
	CommandButton *findNonConstCommandButton( const AsciiString& name );

private:
	unsigned char m_unmodelled_000[0x28];
	const CommandButton *m_commandButtons;			// +0x28
};

CommandButton *ControlBar::findNonConstCommandButton( const AsciiString& name )
{

	for( const CommandButton *command = m_commandButtons; command; command = command->getNext() )
		if( command->getName().compare( name ) == 0 )
			return const_cast<CommandButton*>((const CommandButton*)command->getFinalOverride());

	return 0;  // not found

}  // end findCommandButton
