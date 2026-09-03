// cl: /DNDEBUG /MD /EHsc
// readable body of ?calcTimeToBuild@UpgradeTemplate@@QBEHPAVPlayer@@@Z: Code/GameEngine/Source/Common/System/Upgrade.cpp

class Player;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Upgrade.h
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
