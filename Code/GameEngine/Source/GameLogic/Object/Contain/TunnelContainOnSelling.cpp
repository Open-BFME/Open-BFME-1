// cl: /DNDEBUG /MD /EHsc
// Zero Hour TunnelContain::onSelling against BFME's adjusted contain pointer,
// tracker layout, and registration flag.

class Object;

class TunnelTracker
{
public:
	void onTunnelDestroyed(const Object *object);
	int friend_getTunnelCount() const { return m_tunnelCount; }

private:
	unsigned char m_unreconstructed_000[0x14];
	int m_tunnelCount;
};

class Player
{
public:
	TunnelTracker *getTunnelSystem() { return m_tunnelSystem; }

private:
	unsigned char m_unreconstructed_000[0x22c];
	TunnelTracker *m_tunnelSystem;
};

class Object
{
public:
	Player *getControllingPlayer() const;
};

#define TUNNEL_SLOT(n) virtual void unused##n();

class TunnelContain
{
public:
	TUNNEL_SLOT(00) TUNNEL_SLOT(01) TUNNEL_SLOT(02) TUNNEL_SLOT(03)
	TUNNEL_SLOT(04) TUNNEL_SLOT(05) TUNNEL_SLOT(06) TUNNEL_SLOT(07)
	TUNNEL_SLOT(08) TUNNEL_SLOT(09) TUNNEL_SLOT(10) TUNNEL_SLOT(11)
	TUNNEL_SLOT(12) TUNNEL_SLOT(13) TUNNEL_SLOT(14) TUNNEL_SLOT(15)
	TUNNEL_SLOT(16) TUNNEL_SLOT(17) TUNNEL_SLOT(18) TUNNEL_SLOT(19)
	TUNNEL_SLOT(20) TUNNEL_SLOT(21) TUNNEL_SLOT(22) TUNNEL_SLOT(23)
	TUNNEL_SLOT(24) TUNNEL_SLOT(25) TUNNEL_SLOT(26) TUNNEL_SLOT(27)
	TUNNEL_SLOT(28) TUNNEL_SLOT(29) TUNNEL_SLOT(30) TUNNEL_SLOT(31)
	TUNNEL_SLOT(32) TUNNEL_SLOT(33) TUNNEL_SLOT(34) TUNNEL_SLOT(35)
	TUNNEL_SLOT(36)
	virtual void removeAllContained(bool exposeStealthUnits);
	virtual void onSelling();

private:
	Object *getObject() const
	{
		return *reinterpret_cast<Object *const *>(
			reinterpret_cast<const unsigned char *>(this) - 0x18);
	}

	unsigned char m_unreconstructed_004[0xb1];
	bool m_isCurrentlyRegistered;
};

#undef TUNNEL_SLOT

// ?onSelling@TunnelContain@@UAEXXZ
void TunnelContain::onSelling()
{
	Player *owningPlayer = getObject()->getControllingPlayer();
	if (owningPlayer == 0)
		return;

	TunnelTracker *tunnelTracker = owningPlayer->getTunnelSystem();
	if (tunnelTracker == 0)
		return;

	if (tunnelTracker->friend_getTunnelCount() == 1)
		removeAllContained(false);

	if (m_isCurrentlyRegistered)
	{
		tunnelTracker->onTunnelDestroyed(getObject());
		m_isCurrentlyRegistered = false;
	}
}
