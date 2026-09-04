// ?getCollapseHeight@StructureCollapseRetailLayout@@QAEMXZ
// partial score=0.75 date=2026-09-04
// ?getCollapseHeight@StructureCollapseRetailLayout@@QAEMXZ
// partial score=0.75 date=2026-09-04
// cl: /DNDEBUG /MD /EHsc

typedef float Real;
typedef unsigned char Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Geometry.h
class GeometryInfo
{
public:
	Real getMaxHeightAbovePosition() const;
};

class StructureCollapseTemplate
{
public:
	unsigned char m_vtable[4];
	StructureCollapseTemplate *m_nextOverride;
	unsigned char m_unmodelled_08[0x60 - 8];
	GeometryInfo m_geometry;
};

class StructureCollapseObject
{
public:
	unsigned char m_vtable[4];
	StructureCollapseTemplate *m_template;
	StructureCollapseTemplate *getTemplate() const
	{
		const char *slot = reinterpret_cast<const char *>(this);
		slot += 4;
		return const_cast<StructureCollapseTemplate *>(*reinterpret_cast<
			StructureCollapseTemplate *const volatile *>(slot));
	}
};

class StructureCollapseModuleData
{
public:
	unsigned char m_unmodelled_000[0xf4];
	Real m_minCollapseHeight;
};

extern void j_000022bb();
typedef StructureCollapseTemplate *(__fastcall *OverrideCall)(
	StructureCollapseTemplate *);

static __forceinline StructureCollapseTemplate *getStructureCollapseTemplate(
	StructureCollapseObject *object)
{
	char *slot = reinterpret_cast<char *>(object);
	slot += 4;
	return *reinterpret_cast<StructureCollapseTemplate *volatile *>(slot);
}

class StructureCollapseObjectModule
{
protected:
	virtual ~StructureCollapseObjectModule();
	StructureCollapseModuleData *m_moduleData;
	StructureCollapseObject *m_object;

	StructureCollapseObject *getObject() volatile
	{
		return m_object;
	}
};

class StructureCollapseRetailLayout : public StructureCollapseObjectModule
{
public:
	Real getCollapseHeight();
};

static __forceinline StructureCollapseTemplate *getStructureCollapseTemplateAgain(
	volatile StructureCollapseRetailLayout *self)
{
	StructureCollapseObject *object = *reinterpret_cast<
		StructureCollapseObject *volatile *>(
		reinterpret_cast<volatile char *>(self) + 8);
	volatile char *slot = reinterpret_cast<volatile char *>(object);
	slot += 4;
	return *reinterpret_cast<StructureCollapseTemplate *volatile *>(slot);
}

static __forceinline StructureCollapseTemplate *getStructureCollapseTemplateAt(
	StructureCollapseObject *object)
{
	volatile char *slot = reinterpret_cast<volatile char *>(object);
	slot += 4;
	return *reinterpret_cast<StructureCollapseTemplate *volatile *>(slot);
}

// ?getCollapseHeight@StructureCollapseRetailLayout@@QAEMXZ
Real StructureCollapseRetailLayout::getCollapseHeight()
{
	StructureCollapseTemplate *t = getObject()->getTemplate();
	StructureCollapseModuleData *md;
	if (t)
	{
		md = m_moduleData;
		StructureCollapseTemplate *o = t->m_nextOverride;
		if (o)
			t = ((OverrideCall)j_000022bb)(o);
	}
	else
	{
		md = m_moduleData;
	}

	Real height = t->m_geometry.getMaxHeightAbovePosition();
	if (height < md->m_minCollapseHeight)
		return m_moduleData->m_minCollapseHeight;

	StructureCollapseTemplate *t2 = getObject()->getTemplate();
	if (t2)
		goto have_second_template;
	return t2->m_geometry.getMaxHeightAbovePosition();

have_second_template:
	StructureCollapseTemplate *o2 = t2->m_nextOverride;
	if (o2)
		t2 = ((OverrideCall)j_000022bb)(o2);
	return t2->m_geometry.getMaxHeightAbovePosition();
}
