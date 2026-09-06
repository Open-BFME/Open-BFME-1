// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: near-twin of ??1SlaveWatcherBehavior (0x00207580,
// SlaveWatcherBehaviorDestructorThunk.cpp) and of ?d_002d3080 (0x002D3080,
// Rva002D3080Destructor.cpp). Same UpdateModule chain plus one extra
// interface base (vtable at +0x20, no intervening field-holder class), and a
// guarded cleanup call on TheAudioClientUpdate passing a field at +0x24, then
// marking that field done (=1) -- unlike Rva002D3080 which leaves its field
// untouched after the call. The GameLogic::findObjectByID id argument is not
// a stored member of this module (unlike SlaveWatcherBehavior's m_slaveID);
// it is read from the owning Object's own field at +0x7c. Address-derived
// name: real identity unknown.

class BfmeX1011;

enum DamageType
{
	DAMAGE_SNIPER = 8
};

enum DeathType
{
	DEATH_RVA1FEB50 = 0x16
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void kill(DamageType, DeathType);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Object *findObjectByID(int);
};

extern GameLogic *TheGameLogic;

class Gen_dtor_0110A4F4
{
public:
	virtual ~Gen_dtor_0110A4F4();

protected:
	const void *m_moduleData;
	Object *m_object;
};

class BehaviorModuleInterface
{
public:
	virtual void getBehaviorModuleInterface() = 0;
};

class UpdateModuleInterface
{
public:
	virtual void updateModuleInterface() = 0;
};

class BehaviorModule : public Gen_dtor_0110A4F4, public BehaviorModuleInterface
{
public:
	virtual ~BehaviorModule() {}
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	virtual ~UpdateModule() {}

private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_indexInUpdate;
};

class Rva001FEB50ExtraInterface
{
public:
	virtual void extraInterface() = 0;
};

class AudioClientUpdateSub
{
public:
	virtual void unused00(); virtual void unused01(); virtual void unused02(); virtual void unused03();
	virtual void unused04(); virtual void unused05(); virtual void unused06(); virtual void unused07();
	virtual void unused08(); virtual void unused09(); virtual void unused10(); virtual void unused11();
	virtual void unused12(); virtual void unused13(); virtual void unused14(); virtual void unused15();
	virtual void unused16(); virtual void unused17(); virtual void unused18();
	virtual void removeAudioEvent(unsigned int audioEvent);
};

extern AudioClientUpdateSub *TheAudioClientUpdate;

// upstream layout: real header unknown; address-derived shape
class Rva001FEB50
	: public UpdateModule, public Rva001FEB50ExtraInterface
{
public:
	virtual ~Rva001FEB50();

private:
	unsigned int m_field24;
};

// ?d_001feb50@@YAXXZ
Rva001FEB50::~Rva001FEB50()
{
	if (m_object)
	{
		int id = *reinterpret_cast<int *>(reinterpret_cast<char *>(m_object) + 0x7c);
		Object *found = TheGameLogic->findObjectByID(id);
		if (found)
			found->kill(DAMAGE_SNIPER, DEATH_RVA1FEB50);
	}

	if (TheAudioClientUpdate)
	{
		TheAudioClientUpdate->removeAudioEvent(m_field24);
		m_field24 = 1;
	}
}
