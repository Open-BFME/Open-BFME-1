// cl: /DNDEBUG /MD

typedef int Color;

class MultiplayerColorDefinition
{
public:
	Color getNightColor(void) const;

private:
	unsigned char m_beforeColorNight[0x20];
	Color m_colorNight;
};

// ?getNightColor@MultiplayerColorDefinition@@QBEHXZ
Color MultiplayerColorDefinition::getNightColor(void) const
{
	return m_colorNight;
}
