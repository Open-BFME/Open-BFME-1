// ?iterateContained@TunnelContain@@UAEXP6AXPAVObject@@PAX@Z1_N@Z
// partial score=0.98 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc
// Zero Hour TunnelContain::iterateContained adapted to BFME's adjusted
// ContainModuleInterface pointer and packed direction flags.

class Object;
typedef void (*ContainIterateFunc)(Object *, void *);

class TunnelTracker
{
public:
	void iterateContained(ContainIterateFunc func, void *userData, bool reverse);
};

struct PackedTunnelIterationFlags
{
	bool active : 1;
	bool unused : 2;
	bool reverse : 1;
};

class Player
{
public:
	unsigned char m_unreconstructed_000[0x22c];
	TunnelTracker *m_tunnelSystem;
};

class Object
{
public:
	Player *getControllingPlayer() const;
};

class TunnelContain
{
public:
	virtual void iterateContained(ContainIterateFunc func, void *userData, bool reverse);

private:
	Object *getObject() const
	{
		return *reinterpret_cast<Object *const *>(
			reinterpret_cast<const unsigned char *>(this) - 0x18);
	}
};

// ?iterateContained@TunnelContain@@UAEXP6AXPAVObject@@PAX@Z1_N@Z
void TunnelContain::iterateContained(ContainIterateFunc func, void *userData, bool reverse)
{
	unsigned int packed = *reinterpret_cast<unsigned int *>(&reverse);
	PackedTunnelIterationFlags &flags =
		*reinterpret_cast<PackedTunnelIterationFlags *>(&packed);
	if (flags.active)
	{
		Player *owningPlayer = getObject()->getControllingPlayer();
		owningPlayer->m_tunnelSystem->iterateContained(
			func, userData, flags.reverse);
	}
}
