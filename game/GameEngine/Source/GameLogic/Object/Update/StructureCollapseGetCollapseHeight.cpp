// cl: /DNDEBUG /MD /EHsc

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class GeometryInfo
{
public:
	float getMaxHeightAbovePosition() const;
};

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *m_vtable;
	Overridable *m_override;
	unsigned char m_unreconstructed08[0x58];
	GeometryInfo m_geometryInfo;
};

class BfmeThing
{
public:
	void *m_vtable;
	Overridable *m_template;
};

class BfmeObject
{
public:
	unsigned char m_unreconstructed00[0xf4];
	float m_structureCollapseHeight;
};

class StructureCollapseRetailLayout
{
public:
	float getCollapseHeight();

private:
	void *m_vtable;
	BfmeObject *m_object;
	BfmeThing *m_thing;
};

__forceinline const Overridable *resolveFinalOverride(
	Overridable *volatile *templateSlot)
{
	Overridable *thingTemplate = *templateSlot;
	if (thingTemplate == 0)
		return 0;
	if (thingTemplate->m_override == 0)
		return thingTemplate;
	return thingTemplate->m_override->getFinalOverride();
}

// ?getCollapseHeight@StructureCollapseRetailLayout@@QAEMXZ
float StructureCollapseRetailLayout::getCollapseHeight()
{
	BfmeObject *object = m_object;
	const float geometryHeight = resolveFinalOverride(
		(Overridable *volatile *)&m_thing->m_template)->m_geometryInfo.getMaxHeightAbovePosition();
	if (geometryHeight < object->m_structureCollapseHeight)
		return m_object->m_structureCollapseHeight;

	const float result = resolveFinalOverride(
		(Overridable *volatile *)&m_thing->m_template)->m_geometryInfo.getMaxHeightAbovePosition();
	__asm { }
	return result;
}
