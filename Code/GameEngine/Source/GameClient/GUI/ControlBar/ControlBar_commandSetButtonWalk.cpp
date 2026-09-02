// cl: /DNDEBUG /MD /EHsc
// Walk a named CommandSet's 20 buttons and run the +0x138 pointer walk on each.

class AsciiString
{
};

class Overridable
{
public:
	virtual ~Overridable();
	Overridable *friend_getFinalOverride();
	Overridable *m_nextOverride;
};

class CommandButton
{
public:
	void Rva0049B240();
};

class CommandSet : public Overridable
{
public:
	const CommandButton *getCommandButton( int i ) const;
};

class ControlBar
{
public:
	void commandSetButtonWalk( const AsciiString &name );

private:
	CommandSet *findNonConstCommandSet( const AsciiString &name );
};

void ControlBar::commandSetButtonWalk( const AsciiString &name )
{
	CommandSet *set = findNonConstCommandSet( name );
	if ( !set )
		return;
	if ( set->m_nextOverride )
		set = (CommandSet *)set->m_nextOverride->friend_getFinalOverride();
	if ( !set )
		return;
	for ( int i = 0; i < 20; ++i )
	{
		const CommandButton *btn = set->getCommandButton( i );
		if ( btn )
			( (CommandButton *)btn )->Rva0049B240();
	}
}
