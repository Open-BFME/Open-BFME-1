// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

#include "PreRTS.h"
#include "Common/ThingTemplate.h"
#include "Common/ThingFactory.h"

class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

class Object;

class RespawnUpdateModuleData
{
public:
	unsigned char m_pad[0xb0];
	AsciiString m_spawnTemplateName;
};

class RespawnUpdate
{
public:
	ThingTemplate *getSpawnTemplate();

private:
	void *m_vtbl;
	RespawnUpdateModuleData *m_moduleData;
	Object *m_object;
	unsigned char m_gap[0x28 - 0x0c];
	ThingTemplate *m_cachedTemplate;
};

// ?getSpawnTemplate@RespawnUpdate@@QAEPAVThingTemplate@@XZ
ThingTemplate *RespawnUpdate::getSpawnTemplate()
{
	if (m_cachedTemplate == (ThingTemplate *)-1)
	{
		ThingTemplate *t = (ThingTemplate *)((BfmeThingFactory *)TheThingFactory)->findTemplate(
			m_moduleData->m_spawnTemplateName);
		m_cachedTemplate = t;
		if (!t)
		{
			Object *obj = m_object;
			volatile unsigned char *raw = (volatile unsigned char *)obj;
			raw += 4;
			t = *(ThingTemplate * volatile *)raw;
			if (!t)
			{
				m_cachedTemplate = t;
				return t;
			}
			// Overridable keeps its private m_nextOverride immediately after the +0 vptr.
			const Overridable *next = *(const Overridable *const *)((const char *)t + 4);
			if (next)
				t = (ThingTemplate *)(const void *)next->getFinalOverride();
			m_cachedTemplate = t;
		}
	}
	return m_cachedTemplate;
}
