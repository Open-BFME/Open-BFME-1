// cl: /DNDEBUG /MD /EHsc
// Zero Hour TunnelContain::onDelete against BFME's retail object and tracker
// offsets.

class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/TunnelTracker.h
class TunnelTracker
{
public:
	void onTunnelDestroyed(const Object *object);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	TunnelTracker *getTunnelSystem() { return m_tunnelSystem; }

	private:
	unsigned char m_unreconstructed_000[0x22c];
	TunnelTracker *m_tunnelSystem;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Player *getControllingPlayer() const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/TunnelContain.h
class TunnelContain
{
public:
	virtual void onDelete();

private:
	Object *getObject() const { return m_object; }

	unsigned char m_unreconstructed_004[4];
	Object *m_object;
	unsigned char m_unreconstructed_00c[0xd5 - 0x0c];
	bool m_isCurrentlyRegistered;
};

// ?onDelete@TunnelContain@@UAEXXZ
void TunnelContain::onDelete()
{
	if (!m_isCurrentlyRegistered)
		return;

	Player *owningPlayer = getObject()->getControllingPlayer();
	if (owningPlayer == 0)
		return;

	TunnelTracker *tunnelTracker = owningPlayer->getTunnelSystem();
	if (tunnelTracker == 0)
		return;

	tunnelTracker->onTunnelDestroyed(getObject());
	m_isCurrentlyRegistered = false;
}
