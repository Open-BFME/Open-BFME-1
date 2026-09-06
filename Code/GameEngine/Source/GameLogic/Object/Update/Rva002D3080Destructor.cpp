// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: near-twin of ??1FlammableUpdate (0x00293440,
// FlammableUpdateDestructor.cpp); same UpdateModule chain, but this class adds
// one more interface base (extra vtable at +0x28) and guards its cleanup call
// on TheAudioClientUpdate (not TheAudio), passing a field at +0x2c rather than
// clearing a handle at +0x34 afterward.

class Gen_dtor_00113f20
{
public:
	virtual ~Gen_dtor_00113f20();

private:
	const void *m_moduleData;
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

class ObjectModule : public Gen_dtor_00113f20
{
private:
	void *m_object;
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
public:
	virtual ~BehaviorModule() {}
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_indexInUpdate;

public:
	virtual ~UpdateModule() {}
};

class DamageModuleInterface
{
public:
	virtual void onDamage() = 0;
};

class Rva002D3080ExtraInterface
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

class Rva002D3080WithField : public UpdateModule, public DamageModuleInterface
{
protected:
	int m_field24;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FlammableUpdate.h (near-twin)
class Rva002D3080
	: public Rva002D3080WithField, public Rva002D3080ExtraInterface
{
public:
	virtual ~Rva002D3080();

private:
	unsigned int m_field2c;
};

// ?d_002d3080@@YAXXZ
Rva002D3080::~Rva002D3080()
{
	if (TheAudioClientUpdate)
		TheAudioClientUpdate->removeAudioEvent(m_field2c);
}
