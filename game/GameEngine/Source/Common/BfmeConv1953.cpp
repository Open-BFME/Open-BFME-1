#include "../GameLogic/ScriptEngine/game_logic_dispatch.h"

class Module;
#define OBJECT_TU_MEMBERS \
protected: \
	Module *findModule(NameKeyType key) const; \
	friend class BfmeHostERI;
#include "../GameLogic/Object/object.h"
#undef OBJECT_TU_MEMBERS

class BfmeStateERI
{
public:
	unsigned char m_bfmeHeadERI[0xcc];
	unsigned char m_bfmeFlagsERI;
};

// ILT 0x000022BB reaches Overridable::getFinalOverride at 0x00087A80.
class Overridable
{
public:
	const Overridable *getFinalOverride() const;
};

class BfmeAERI
{
public:
	unsigned char m_bfmeHeadERI[4];
	Overridable *m_bfmeBERI;
};

// ILT 0x00040DC2 reaches StealthUpdate::markAsDetected at 0x002AD380.
class StealthUpdate
{
public:
	void markAsDetected(unsigned int frames, bool propagate);
};

class BfmeThingERI
{
public:
	unsigned char m_bfmeHeadERI[4];
	BfmeAERI *m_bfmeAERI;
};

class BfmeNodeERI
{
public:
	BfmeNodeERI *m_bfmeNextERI;
	unsigned char m_bfmeMidERI[4];
	BfmeThingERI *m_bfmeThingERI;
};

// NameKeyGenerator.cpp defines the singleton at retail VA 0x012ED600.
extern NameKeyGenerator *TheNameKeyGenerator;

class BfmeHostERI
{
public:
	void bfmeSweepERI();

	unsigned char m_bfmeHeadERI[0x99c];
	BfmeNodeERI *m_bfmeListERI;
};

void BfmeHostERI::bfmeSweepERI()
{
	BfmeNodeERI *n = m_bfmeListERI->m_bfmeNextERI;

	while (n != m_bfmeListERI)
	{
		BfmeThingERI *thing = n->m_bfmeThingERI;

		n = n->m_bfmeNextERI;
		BfmeAERI *a = thing->m_bfmeAERI;
		BfmeStateERI *st = (BfmeStateERI *)a;

		if (a != 0)
		{
			Overridable *b = a->m_bfmeBERI;

			if (b != 0)
				st = (BfmeStateERI *)b->getFinalOverride();
		}

		if ((st->m_bfmeFlagsERI & 2) == 0)
			continue;

		static int s_bfmeKeyERI =
			TheNameKeyGenerator->nameToKey("StealthUpdate");

		StealthUpdate *mod = (StealthUpdate *)((Object *)thing)->findModule(
			(NameKeyType)s_bfmeKeyERI);

		if (mod != 0)
			mod->markAsDetected(0, true);
	}
}
