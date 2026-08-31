// cl: /DNDEBUG /MD /EHsc

class Player;

class UpgradeTemplate
{
public:
	int calcTimeToBuild(Player *player) const;

private:
	char m_bfmeLayout[0x18];
	float m_buildTime;
};

int UpgradeTemplate::calcTimeToBuild(Player *) const
{
	return m_buildTime * 30.0f;
}
