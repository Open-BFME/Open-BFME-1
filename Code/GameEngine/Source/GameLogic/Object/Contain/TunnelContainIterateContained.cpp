// ?iterateContained@TunnelContain@@UAEXP6AXPAVObject@@PAX@Z1_N@Z
// Converted from reverse/attempts/0x0022f1b0.cpp.
// cl: /DNDEBUG /MD /EHsc

class Object;
typedef void (*ContainIterateFunc)(Object *, void *);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/TunnelTracker.h
class TunnelTracker
{
public:
	void iterateContained(ContainIterateFunc func, void *userData, bool reverse);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
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
	virtual void iterateContained(ContainIterateFunc func, void *userData, bool reverse);

private:
	Object *getObject() const
	{
		return *reinterpret_cast<Object *const *>(
			reinterpret_cast<const unsigned char *>(this) - 0x18);
	}
};

void TunnelContain::iterateContained(ContainIterateFunc func, void *userData, bool reverse)
{
	unsigned int packed = *reinterpret_cast<unsigned int *>(&reverse);
	if (packed & 1)
	{
		Player *owningPlayer = getObject()->getControllingPlayer();
		owningPlayer->m_tunnelSystem->iterateContained(
			func, userData, ((packed >> 3) & 1) != 0);
	}
}
