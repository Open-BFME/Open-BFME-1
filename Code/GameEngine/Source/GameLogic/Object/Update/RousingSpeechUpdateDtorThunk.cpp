// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include <list>

class Thing;
class ModuleData;

class Gen_dtor_00113f20
{
public:
    virtual ~Gen_dtor_00113f20();

private:
    unsigned char m_pad[8];
};

class SpecialAbilityUpdateBaseInterface1
{
public:
    virtual void slot();
};

class SpecialAbilityUpdateBaseInterface2
{
public:
    virtual void slot();

private:
    unsigned char m_pad[0xC];
};

class SpecialAbilityUpdateObjectModule : public Gen_dtor_00113f20
{
};

class SpecialAbilityUpdateBehaviorModule : public SpecialAbilityUpdateObjectModule,
    public SpecialAbilityUpdateBaseInterface1
{
public:
    virtual ~SpecialAbilityUpdateBehaviorModule() {}
};

class SpecialAbilityUpdateUpdateModule : public SpecialAbilityUpdateBehaviorModule,
    public SpecialAbilityUpdateBaseInterface2
{
public:
    virtual ~SpecialAbilityUpdateUpdateModule() {}
};

class SpecialAbilityUpdateInterface
{
public:
    virtual void slot();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventRTS.h
class AudioEventRTS
{
public:
    virtual ~AudioEventRTS();

private:
    unsigned char m_pad[0x94];
};

class Gen_dtor_002aaec0 : public SpecialAbilityUpdateUpdateModule,
    public SpecialAbilityUpdateInterface
{
public:
	Gen_dtor_002aaec0(Thing *, const ModuleData *);
    virtual ~Gen_dtor_002aaec0();

private:
    unsigned char m_pad[0x10];
    AudioEventRTS m_prepSoundLoop;
    _STL::list<int> m_specialObjectIDList;
    unsigned char m_tail[0x18];
};

class RousingSpeechUpdate : public Gen_dtor_002aaec0
{
public:
	RousingSpeechUpdate(Thing *, const ModuleData *);
    virtual ~RousingSpeechUpdate();

private:
    _STL::list<int> m_speechObjectIDList;
    unsigned int m_a;
    unsigned char m_b;
    unsigned int m_c;
    unsigned int m_d;
};

RousingSpeechUpdate::RousingSpeechUpdate(Thing *thing, const ModuleData *data)
	: Gen_dtor_002aaec0(thing, data), m_a(0), m_b(0), m_c(0), m_d(0)
{
	m_speechObjectIDList.clear();
}

// ??1RousingSpeechUpdate@@UAE@XZ
RousingSpeechUpdate::~RousingSpeechUpdate()
{
	m_speechObjectIDList.clear();
}
