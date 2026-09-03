// cl: /DNDEBUG /MD /EHsc
// readable body of ?update@RiderChangeContain@@UAE?AW4UpdateSleepTime@@XZ: Code/GameEngine/Source/GameLogic/Object/Contain/RiderChangeContain.cpp
// Zero Hour RiderChangeContain::update against BFME's retail module layout.

typedef unsigned int UnsignedInt;

enum UpdateSleepTime
{
	UPDATE_SLEEP_INVALID = 0
};

enum DamageType
{
	DAMAGE_UNRESISTABLE = 8
};

enum DeathType
{
	DEATH_TOPPLED = 6
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void kill(DamageType damageType, DeathType deathType);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }

private:
	unsigned char m_unreconstructed_000[0x3c];
	UnsignedInt m_frame;
};

extern GameLogic *TheGameLogic;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/RiderChangeContain.h
class RiderChangeContainModuleData
{
public:
	unsigned char m_unreconstructed_000[0x30c];
	UnsignedInt m_scuttleFrames;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/TransportContain.h
class TransportContain
{
public:
	virtual UpdateSleepTime update();

protected:
	unsigned char m_unreconstructed_004[0xf4];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/RiderChangeContain.h
class RiderChangeContain : public TransportContain
{
public:
	virtual UpdateSleepTime update();

private:
	RiderChangeContainModuleData *getModuleData() const
	{
		return *reinterpret_cast<RiderChangeContainModuleData *const *>(
			reinterpret_cast<const unsigned char *>(this) - 0x0c);
	}

	Object *getObject() const
	{
		return *reinterpret_cast<Object *const *>(
			reinterpret_cast<const unsigned char *>(this) - 0x08);
	}

	UnsignedInt m_scuttledOnFrame;
};

// ?update@RiderChangeContain@@UAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime RiderChangeContain::update()
{
	if (m_scuttledOnFrame != 0)
	{
		RiderChangeContainModuleData *data = getModuleData();
		UnsignedInt now = TheGameLogic->getFrame();
		if (m_scuttledOnFrame + data->m_scuttleFrames <= now)
		{
			getObject()->kill(DAMAGE_UNRESISTABLE, DEATH_TOPPLED);
		}
	}

	return TransportContain::update();
}
