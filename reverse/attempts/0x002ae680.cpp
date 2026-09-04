// ?getCollapseHeight@StructureCollapseRetailLayout@@QAEMXZ
// partial score=0.74 date=2026-09-04
// ?getCollapseHeight@StructureCollapseRetailLayout@@QAEMXZ
// partial score=0.74 date=2026-09-02
// cl: /DNDEBUG /MD

typedef float Real;

class GeometryInfo
{
public:
	Real getMaxHeightAbovePosition() volatile const;
};

class StructureCollapseTemplate
{
public:
	virtual ~StructureCollapseTemplate();
	StructureCollapseTemplate *friend_getFinalOverride();

	StructureCollapseTemplate *m_nextOverride;
	unsigned char m_unmodelled_08[ 0x60 - 8 ];
	GeometryInfo m_geometry;
};

class StructureCollapseObject
{
public:
	void *m_vtable;
	StructureCollapseTemplate *m_template;
};

static __forceinline StructureCollapseTemplate *getStructureCollapseTemplate(
	StructureCollapseObject *object)
{
	char *slot = reinterpret_cast<char *>(object);
	slot += 4;
	return *reinterpret_cast<StructureCollapseTemplate *volatile *>(slot);
}

class StructureCollapseModuleData
{
public:
	unsigned char m_unmodelled_000[ 0xF4 ];
	Real m_minCollapseHeight;
};

class StructureCollapseRetailLayout
{
public:
	Real getCollapseHeight();

private:
	void *m_vtable;
	StructureCollapseModuleData *m_moduleData;
	StructureCollapseObject *m_object;
};

static __forceinline StructureCollapseTemplate *getSecondCollapseTemplate(
	volatile StructureCollapseRetailLayout *self)
{
	StructureCollapseObject *object = *reinterpret_cast<
		StructureCollapseObject *volatile *>(
			reinterpret_cast<volatile char *>(self) + 8);
	volatile char *slot = reinterpret_cast<volatile char *>(object);
	slot += 4;
	return *reinterpret_cast<StructureCollapseTemplate *volatile *>(slot);
}

Real StructureCollapseRetailLayout::getCollapseHeight()
{
	StructureCollapseTemplate *t = getStructureCollapseTemplate( m_object );
	StructureCollapseModuleData *md;
	if( t )
	{
		md = m_moduleData;
		StructureCollapseTemplate *o = t->m_nextOverride;
		if( o )
			t = o->friend_getFinalOverride();
	}
	else
	{
		md = m_moduleData;
	}

	StructureCollapseTemplate *t2;
	Real height = t->m_geometry.getMaxHeightAbovePosition();
	if( height < md->m_minCollapseHeight )
		return m_moduleData->m_minCollapseHeight;

	t2 = getSecondCollapseTemplate( this );
	if( !t2 )
		return t2->m_geometry.getMaxHeightAbovePosition();
	StructureCollapseTemplate *o2 = t2->m_nextOverride;
	if( o2 )
		t2 = o2->friend_getFinalOverride();
	return t2->m_geometry.getMaxHeightAbovePosition();
}
