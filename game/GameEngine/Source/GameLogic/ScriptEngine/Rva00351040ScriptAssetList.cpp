// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Retail RVA 0x00351040 walks both ScriptAction chains and gathers the thing
// templates referenced by their action parameters and team unit records.
// The caller at 0x0033CA50 and the ScriptAction layout prove this body shape,
// but they do not prove a semantic owner, so the source keeps its address name.

#include "ascii_string.h"

typedef int Int;

class Parameter
{
public:
	Int m_type;
	Int m_initialized;
	Int m_int;
	float m_real;
	AsciiString m_string;
};

class Rva00351040Action
{
public:
	virtual void slot00();

	Int m_type;
	Int m_numParameters;
	Parameter *m_parameters[12];
	Rva00351040Action *m_next;
};

class BfmeResGH
{
public:
	void bfmeTwoGH(void *assets, void *context);
};

class ThingTemplate : public BfmeResGH
{
};

class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

extern BfmeThingFactory *TheThingFactory;

class TeamPrototype
{
};

class ScriptEngine
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual TeamPrototype *getTeamPrototypeNamed(AsciiString name);
};

extern ScriptEngine *TheScriptEngine;

struct Rva00351040UnitInfo
{
	Int m_minUnits;
	Int m_maxUnits;
	AsciiString m_name;
};

class Rva00351040TeamTemplateInfo
{
	virtual void slot00();

	public:
	Rva00351040UnitInfo m_units[7];
	Int m_numUnits;
	char m_betweenUnitsAndTransport[0x50];
	AsciiString m_transportUnit;
};

class Rva00351040TeamPrototypeView
{
public:
	Rva00351040TeamTemplateInfo *getTemplateInfo() const
	{
		return (Rva00351040TeamTemplateInfo *)&m_template;
	}

	private:
	char m_beforeTemplate[0x12c];
	Rva00351040TeamTemplateInfo m_template;
};

class Rva00351040StringView
{
public:
	bool isNotEmpty() const
	{
		return m_data != 0 && *((unsigned short *)((char *)m_data + 4)) != 0;
	}

private:
	void *m_data;
};

class Rva00351040Script
{
public:
	void collectAssets(void *assets, void *context);

private:
	char m_beforeActions[0x20];
	Rva00351040Action *m_action;
	Rva00351040Action *m_actionFalse;
};

static void collectAsset(const ThingTemplate *thing, void *assets, void *context)
{
	if (thing != 0)
		const_cast<ThingTemplate *>(thing)->bfmeTwoGH(assets, context);
}

void Rva00351040Script::collectAssets(void *assets, void *context)
{
	for (Int branch = 0; branch < 2; ++branch)
	{
		Rva00351040Action *action = branch ? m_action : m_actionFalse;
		while (action != 0)
		{
			switch (action->m_type)
			{
			case 0x22:
			{
				Parameter *parameter = action->m_numParameters > 0
					? action->m_parameters[0] : 0;
				Rva00351040TeamPrototypeView *team =
					(Rva00351040TeamPrototypeView *)
					TheScriptEngine->getTeamPrototypeNamed(
						*(AsciiString *)((char *)parameter + 0x10));
				if (team != 0)
				{
					Rva00351040TeamTemplateInfo *templateInfo =
						team->getTemplateInfo();
					if (templateInfo != 0)
					{
						if (((Rva00351040StringView *)&templateInfo->m_transportUnit)->isNotEmpty())
							collectAsset(TheThingFactory->findTemplate(
								templateInfo->m_transportUnit), assets, context);

						Rva00351040UnitInfo *unit = &templateInfo->m_units[0];
						for (Int i = 0; i < templateInfo->m_numUnits; ++i, ++unit)
						{
							collectAsset(TheThingFactory->findTemplate(unit->m_name), assets, context);
						}
					}
				}
				break;
			}

			case 0x28:
			case 0x139:
			{
				Parameter *parameter = action->m_numParameters > 1
					? action->m_parameters[1] : 0;
				const ThingTemplate *thing = TheThingFactory->findTemplate(
					*(AsciiString *)((char *)parameter + 0x10));
				collectAsset(thing, assets, context);
				break;
			}

			case 0x17:
			case 0x29:
			{
				Parameter *parameter = action->m_numParameters > 0
					? action->m_parameters[0] : 0;
				const ThingTemplate *thing = TheThingFactory->findTemplate(
					*(AsciiString *)((char *)parameter + 0x10));
				collectAsset(thing, assets, context);
				break;
			}
			}

			action = action->m_next;
		}
	}
}
