// ?getCollapseHeight@StructureCollapseRetailLayout@@QAEMXZ
// partial score=0.74 date=2026-09-02
// cl: /DNDEBUG /MD

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

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
	StructureCollapseTemplate *getTemplate()
	{
		char *slot = reinterpret_cast<char *>( this );
		slot += 4;
		return *reinterpret_cast<StructureCollapseTemplate *volatile *>( slot );
	}
};

static __forceinline StructureCollapseTemplate *getStructureCollapseTemplate(
	StructureCollapseObject *object)
{
	char *slot = reinterpret_cast<char *>(object);
	slot += 4;
	return *reinterpret_cast<StructureCollapseTemplate *volatile *>(slot);
}

static __forceinline bool structureCollapseTemplateExists(StructureCollapseTemplate *t)
{
	return t != 0;
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

	Real height = t->m_geometry.getMaxHeightAbovePosition();
	if( height < md->m_minCollapseHeight )
		return m_moduleData->m_minCollapseHeight;

	StructureCollapseTemplate *t2 = m_object->getTemplate();
	if( !structureCollapseTemplateExists( t2 ) )
		return t2->m_geometry.getMaxHeightAbovePosition();
	StructureCollapseTemplate *o2 = t2->m_nextOverride;
	if( o2 )
		t2 = o2->friend_getFinalOverride();
	return t2->m_geometry.getMaxHeightAbovePosition();
}
