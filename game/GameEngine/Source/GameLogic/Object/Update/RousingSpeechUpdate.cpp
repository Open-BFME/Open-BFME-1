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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventRTS.h
class AudioEventRTS
{
public:
    virtual ~AudioEventRTS();

private:
    unsigned char m_pad[0x94];
};

// The named SpecialAbilityUpdate factory 0x001140C0 allocates 0xe8 bytes
// and calls ILT 0x00013462 -> its matched constructor 0x002A6360.
// RousingSpeech uses that route and destructor ILT 0x000243A7 -> 0x002AA910.
// Preserve the BFME view: sound at +34, list at +cc, derived data at +e8.
// The vendored Generals header puts other fields between sound and list;
// there is no compatible Code header to adopt for this member order.
class SpecialAbilityUpdate : public SpecialAbilityUpdateUpdateModule,
    public SpecialAbilityUpdateInterface
{
public:
	SpecialAbilityUpdate(Thing *, const ModuleData *);
    virtual ~SpecialAbilityUpdate();

private:
    unsigned char m_pad[0x10];
    AudioEventRTS m_prepSoundLoop;
    _STL::list<int> m_specialObjectIDList;
    unsigned char m_tail[0x18];
};

class RousingSpeechUpdate : public SpecialAbilityUpdate
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
	: SpecialAbilityUpdate(thing, data), m_a(0), m_b(0), m_c(0), m_d(0)
{
	m_speechObjectIDList.clear();
}

// ??1RousingSpeechUpdate@@UAE@XZ
RousingSpeechUpdate::~RousingSpeechUpdate()
{
	m_speechObjectIDList.clear();
}
