// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: TensileFormationUpdate constructor.

#include <string.h>

class Thing;
class ModuleData;
class Object;

extern "C" char TensileFormationUpdate_vtbl0;
extern "C" char TensileFormationUpdate_vtblC;
extern "C" char TensileFormationUpdate_vtbl10;

class PB_DeepBase
{
public:
	PB_DeepBase(Thing *, const ModuleData *);
	virtual ~PB_DeepBase();

protected:
	void *m_f04;
	Object *m_object;
};

class TensileFormationUpdateIface1
{
public:
	virtual void slot();
};

class TensileFormationUpdateIface2
{
public:
	virtual void slot();
};

class __declspec(novtable) TensileFormationUpdate : public PB_DeepBase,
	public TensileFormationUpdateIface1,
	public TensileFormationUpdateIface2
{
public:
	TensileFormationUpdate(Thing *, const ModuleData *);
	virtual ~TensileFormationUpdate();

private:
	unsigned int m_formationData[0x30];
	volatile unsigned int m_fD4;
	volatile unsigned int m_fD8;
	volatile unsigned int m_fDC;
};

// ??0TensileFormationUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
TensileFormationUpdate::TensileFormationUpdate(Thing *thing, const ModuleData *moduleData)
	: PB_DeepBase(thing, moduleData)
{
	*(void *volatile *)this = &TensileFormationUpdate_vtbl0;
	*(void *volatile *)((char *)this + 0x0c) = &TensileFormationUpdate_vtblC;
	*(void *volatile *)((char *)this + 0x10) = &TensileFormationUpdate_vtbl10;
	m_fD4 = 0;
	m_fD8 = 0;
	m_fDC = 0;
	memset(m_formationData, 0, sizeof(m_formationData));
}
