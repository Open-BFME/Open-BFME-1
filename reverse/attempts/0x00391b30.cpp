// ?findControlBarOverride@GameLogic@@QBE_NABVAsciiString@@HAAPBVCommandButton@@@Z
// partial score=0.98 date=2026-09-01
// cl: /DNDEBUG /MD /EHsc

#include <string.h>

class CommandButton;

extern const char g_NAMEKEY_empty_string;

struct BfmeAsciiStringBuffer
{
	char header[8];
	char data[1];
};

class AsciiString
{
public:
	AsciiString( const char *text );
	~AsciiString();

	const char *str() const
	{
		return m_buffer ? m_buffer->data : &g_NAMEKEY_empty_string;
	}

private:
	BfmeAsciiStringBuffer *m_buffer;
};

struct BfmeControlBarOverrideNode
{
	unsigned char m_unmodelled[8];
	const CommandButton *m_button;
};

class BfmeControlBarOverrideMap
{
public:
	BfmeControlBarOverrideNode *find( const AsciiString &key ) const;
};

class GameLogic
{
public:
	bool findControlBarOverride( const AsciiString &commandSetName, int slot,
		const CommandButton *&commandButton ) const;

private:
	unsigned char m_unmodelled[0x20];
	BfmeControlBarOverrideMap m_controlBarOverrides;
};

// ?findControlBarOverride@GameLogic@@QBE_NABVAsciiString@@HAAPBVCommandButton@@@Z
bool GameLogic::findControlBarOverride( const AsciiString &commandSetName, int slot,
	const CommandButton *&commandButton ) const
{
	char buffer[256];
	buffer[0] = '0' + slot;
	strcpy( &buffer[1], commandSetName.str() );

	BfmeControlBarOverrideNode *entry = m_controlBarOverrides.find( AsciiString( buffer ) );
	if( entry )
	{
		commandButton = entry->m_button;
		return true;
	}

	return false;
}
