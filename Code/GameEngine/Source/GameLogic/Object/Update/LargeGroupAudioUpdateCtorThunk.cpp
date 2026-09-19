// cl: /DNDEBUG /MD /EHsc
// ModuleFactory's 0x68-byte allocation fixes the BFME-only layout. The two
// small state blocks explain the retail constructor's repeated zero stores.

#include <string.h>

class Thing;
class ModuleData;
class Object;

class LGAU_DeepBase
{
public:
    LGAU_DeepBase(Thing *, const ModuleData *);
    virtual ~LGAU_DeepBase();

protected:
    const ModuleData *m_moduleData;
    Object *m_object;
};

class LGAU_Iface1 { public: virtual void slot(); };
class LGAU_Iface2 { public: virtual void slot(); };

class LGAU_UpdateModule : public LGAU_DeepBase,
                          public LGAU_Iface1,
                          public LGAU_Iface2
{
public:
    LGAU_UpdateModule(Thing *thing, const ModuleData *moduleData)
        : LGAU_DeepBase(thing, moduleData),
          m_indexInLogic(-1), m_updateState(-1),
          m_nextCallFrameAndPhase(0)
    {
    }

private:
    unsigned int m_nextCallFrameAndPhase;
    int m_indexInLogic;
    int m_updateState;
};

class LGAU_Interface { public: virtual void slot(); };

class LGAU_State3A
{
public:
    LGAU_State3A() : m_f00(0), m_f04(0), m_f08(0) {}

private:
    unsigned int m_f00;
    unsigned int m_f04;
    unsigned int m_f08;
};

class LGAU_State10
{
public:
    __forceinline LGAU_State10()
    {
        memset(this, 0, sizeof(*this));
    }

private:
    unsigned int m_f00;
    unsigned int m_f04;
    unsigned int m_f08;
    unsigned int m_f0c;
    unsigned int m_f10;
    unsigned int m_f14;
    unsigned int m_f18;
    unsigned int m_f1c;
    unsigned int m_f20;
    unsigned int m_f24;
};

class LGAU_State3B
{
public:
    __forceinline LGAU_State3B() { memset(this, 0, sizeof(*this)); }

private:
    unsigned int m_f00;
    unsigned int m_f04;
    unsigned int m_f08;
};

class LargeGroupAudioUpdate : public LGAU_UpdateModule,
                              public LGAU_Interface
{
public:
    LargeGroupAudioUpdate(Thing *, const ModuleData *);

private:
    LGAU_State3A m_state24;
    LGAU_State10 m_state30;
    LGAU_State3B m_state58;
    bool m_f64;
    bool m_f65;
};

// ??0LargeGroupAudioUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
LargeGroupAudioUpdate::LargeGroupAudioUpdate(
    Thing *thing, const ModuleData *moduleData)
    : LGAU_UpdateModule(thing, moduleData)
{
    m_f64 = false;
    m_f65 = false;
}
