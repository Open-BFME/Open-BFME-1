// cl: /DNDEBUG /MD /EHs-c-
// RVA-derived type: method of a subobject at Object+0x64.  The body is the
// ZH PartitionData::attachToObject ghost-object predicate (KINDOF_IMMOBILE
// plus a W3DDefaultDraw scan on the template draw-module vector at +0x2A0).
// TheGhostObjectManager at 0x012EF4FC vslot +0x1C takes the host Object*
// (this-0x64); a non-null result is returned skipped past its vptr.

typedef int Int;
typedef bool Bool;

extern "C" int __cdecl strcmp(const char *, const char *);

class Overridable
{
public:
	Overridable *getFinalOverride();

	void *m_vtable;
	Overridable *m_nextOverride;
};

class BFMERetailAsciiString
{
public:
	~BFMERetailAsciiString() { releaseBuffer(); }

	const char *str() const
	{
		return m_data ? m_data + 8 : "";
	}

private:
	void releaseBuffer();
	char *m_data;
};

struct ModuleNugget
{
	char m_bytes[20];
};

class ModuleInfo
{
public:
	BFMERetailAsciiString getNthName(Int i) const;

	Int getCount() const
	{
		return (Int)(m_end - m_begin);
	}

	ModuleNugget *m_begin;
	ModuleNugget *m_end;
	ModuleNugget *m_cap;
};

class ThingTemplate : public Overridable
{
public:
	unsigned char m_pad08[0xc8 - 0x08];
	unsigned char m_kindOf;
	unsigned char m_pad_c9[0x2a0 - 0xc9];
	ModuleInfo m_drawModuleInfo;
};

class GlobalData
{
public:
	unsigned char m_pad[0xcf4];
	unsigned char m_ghostObjectsEnabled;
};

class Object;

class GhostObjectManager
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void *addGhostObject(Object *object);
};

extern GlobalData *TheWritableGlobalData;
extern GhostObjectManager *TheGhostObjectManager;

class Rva001CA550
{
public:
	void *getGhostObject();
};

void *Rva001CA550::getGhostObject()
{
	if (TheWritableGlobalData->m_ghostObjectsEnabled == 0)
		return 0;

	ThingTemplate *thing = *(ThingTemplate **)((char *)this - 0x60);
	if (thing != 0 && thing->m_nextOverride != 0)
		thing = (ThingTemplate *)thing->m_nextOverride->getFinalOverride();
	if (thing->m_kindOf & 4)
	{
		ThingTemplate *drawThing;
		ThingTemplate *raw = *(ThingTemplate **)((char *)this - 0x60);
		if (raw == 0)
			drawThing = 0;
		else
		{
			if (raw->m_nextOverride != 0)
				raw = (ThingTemplate *)raw->m_nextOverride->getFinalOverride();
			drawThing = raw;
		}

		ModuleInfo *drawMod = &drawThing->m_drawModuleInfo;
		Bool makeGhostObject = true;
		for (Int i = 0; i < (Int)(drawMod->m_end - drawMod->m_begin); ++i)
		{
			if (strcmp(drawMod->getNthName(i).str(), "W3DDefaultDraw") == 0)
			{
				makeGhostObject = false;
				break;
			}
		}
		if (makeGhostObject)
		{
			void *ghost = TheGhostObjectManager->addGhostObject(
				(Object *)((char *)this - 0x64));
			if (ghost != 0)
				return (char *)ghost + 4;
		}
	}
	return 0;
}
