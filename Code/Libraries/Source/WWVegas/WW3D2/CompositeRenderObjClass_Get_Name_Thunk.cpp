// cl: /DNDEBUG /MD /EHsc

// Slot 27 of the HLodClass vtable. HLodClass derives from
// CompositeRenderObjClass and does not override Get_Name, so the slot carries
// the base implementation, which composite.h declares.
//
// Three things agree. Position: rendobj.h orders Class_ID, Get_Name, Set_Name,
// and this sits between Class_ID at slot 24 -- identified last pass by its
// CLASSID_HLOD return -- and Set_Name at slot 28. Member: the body reads +0xC8,
// which is the offset Set_Name writes. Neighbours: slots 29 and 30 are
// Get_Base_Model_Name and Set_Base_Model_Name of CompositeRenderObjClass, so the
// inherited implementations in this region are that class's.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/composite.h
class CompositeRenderObjClass
{
public:
	virtual ~CompositeRenderObjClass();
	virtual const char *Get_Name(void) const;

private:
	unsigned char m_head[0xC4];
	const char *m_name;
};

// ?Get_Name@CompositeRenderObjClass@@UBEPBDXZ
const char *CompositeRenderObjClass::Get_Name(void) const
{
	return m_name;
}
