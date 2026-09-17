// Open-BFME5 conversions.

typedef int Int;

struct Coord3D
{
	float x, y, z;
};

struct BfmeQ1098
{
	char m_bfmePad[0xbd];
	char m_bfmebd;
};

class BfmeR1098
{
public:
	char bfmeOk1098(void);
	int bfmeEach1098(void *f, void *ctx);
	char m_bfmePad[4];
	BfmeQ1098 *m_bfme04;
};

class BfmeD1098
{
public:
	BfmeR1098 *bfmeLook1098(short *h);
	int bfmeStart1098(int a, int b, int c);
};

extern BfmeD1098 *g_bfmeD1098;

BfmeR1098 *bfmeGo1098A(short *h)
{
	while (*h) {
		BfmeR1098 *r = g_bfmeD1098->bfmeLook1098(h);

		if (r && r->bfmeOk1098() && r->m_bfme04 && r->m_bfme04->m_bfmebd)
			return r;
	}
	return 0;
}

class BfmeCtx1098
{
public:
	void bfmeInit1098(int a, int b);
	char m_bfmePad[0x0c];
	Coord3D m_bfmeCoord;
	char m_bfme18;
	char m_bfmePad1[3];
};

void __cdecl bfmeCb1098(void);

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Module;
class Overridable;
class PolygonTrigger;

class Rva00372210Vector
{
public:
	inline PolygonTrigger **begin() const
	{
		return m_begin;
	}
	inline int size() const
	{
		return (unsigned int)((char *)m_end - (char *)m_begin);
	}
private:
	PolygonTrigger **m_begin;
	PolygonTrigger **m_end;
};

class Object
{
public:
	char m_bfmeHead[4];
	Overridable *m_bfmeTemplate;
	Module *findModule(NameKeyType key) const;
	char m_bfmePad08[0xe0];
};

class Module
{
public:
	char m_bfmePad[0xe8];
	Rva00372210Vector m_triggers;
};

class PolygonTrigger
{
public:
	bool bfmeContainsPointAt0018FA20(Coord3D &point) const;
};

class Overridable
{
public:
	const Overridable *getFinalOverride() const;
	char m_bfmeHead[4];
	Overridable *m_nextOverride;
	char m_bfmePad[0xcc];
	unsigned int m_bfmeFlags;
};

class Rva00372210
{
public:
	static int __cdecl callback(Object *object,
		BfmeCtx1098 *context);
};

// ?callback@Rva00372210@@SAHPAVObject@@PAVBfmeCtx1098@@@Z
int __cdecl Rva00372210::callback(Object *objectParameter,
	BfmeCtx1098 *context)
{
	Object *object = objectParameter;
	Module *module;
	const Overridable *objectTemplate = object->m_bfmeTemplate;
	if (objectTemplate == 0)
	{
		objectTemplate = 0;
		goto templateDone;
	}
	if (objectTemplate->m_nextOverride != 0)
		objectTemplate = objectTemplate->m_nextOverride->getFinalOverride();
templateDone:
	PolygonTrigger *trigger;
	if ((objectTemplate->m_bfmeFlags & 0x00800000) == 0)
		return 1;

	static NameKeyType key =
		TheNameKeyGenerator->nameToKey((const char *)0x01083c50);
	module = object->findModule(key);
	if (module == 0)
		return 1;
	if ((module->m_triggers.size() & ~3) <= 0)
		return 1;
	BfmeCtx1098 *ctx = context;
	Int index = 0;

	do
	{
		if (index >= (unsigned int)(module->m_triggers.size() >> 2))
			trigger = 0;
		else
			trigger = *(module->m_triggers.begin() + index);
		if (trigger->bfmeContainsPointAt0018FA20(
			*(Coord3D *)context))
			return 0;

		if (!ctx->m_bfme18 &&
			trigger->bfmeContainsPointAt0018FA20(
			ctx->m_bfmeCoord))
			ctx->m_bfme18 = 1;
		++index;
	} while (index < module->m_triggers.size() >> 2);

	return 1;
}

char bfmeGo1098B(int a, int b, int c)
{
	BfmeCtx1098 ctx;
	int h;

	h = g_bfmeD1098->bfmeStart1098(a, 3, 0);
	ctx.bfmeInit1098(b, c);
	while ((short)h) {
		BfmeR1098 *r = g_bfmeD1098->bfmeLook1098((short *)&h);

		if (r && !r->bfmeEach1098((void *)bfmeCb1098, &ctx))
			return 0;
	}
	return ctx.m_bfme18;
}
