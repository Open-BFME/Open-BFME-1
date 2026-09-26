// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: TransitionDamageFX constructor.

#include <string.h>

class Thing;
class ModuleData;
class Object;

extern "C" char TransitionDamageFX_vtbl0;
extern "C" char TransitionDamageFX_vtblC;
extern "C" char TransitionDamageFX_vtbl10;

class PB_DeepBase
{
public:
	PB_DeepBase(Thing *, const ModuleData *);
	virtual ~PB_DeepBase();

protected:
	void *m_f04;
	Object *m_object;
};

class TransitionDamageFXIface1
{
public:
	virtual void slot();
};

class TransitionDamageFXIface2
{
public:
	virtual void slot();
};

class __declspec(novtable) TransitionDamageFX : public PB_DeepBase,
	public TransitionDamageFXIface1,
	public TransitionDamageFXIface2
{
public:
	TransitionDamageFX(Thing *, const ModuleData *);
	virtual ~TransitionDamageFX();

private:
	unsigned int m_formationData[0x30];
	volatile unsigned int m_fD4;
	volatile unsigned int m_fD8;
	volatile unsigned int m_fDC;
};

// ??0TransitionDamageFX@@QAE@PAVThing@@PBVModuleData@@@Z
TransitionDamageFX::TransitionDamageFX(Thing *thing, const ModuleData *moduleData)
	: PB_DeepBase(thing, moduleData)
{
	*(void *volatile *)this = &TransitionDamageFX_vtbl0;
	*(void *volatile *)((char *)this + 0x0c) = &TransitionDamageFX_vtblC;
	*(void *volatile *)((char *)this + 0x10) = &TransitionDamageFX_vtbl10;
	m_fD4 = 0;
	m_fD8 = 0;
	m_fDC = 0;
	memset(m_formationData, 0, sizeof(m_formationData));
}
