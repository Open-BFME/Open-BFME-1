// cl: /DNDEBUG /MD /EHsc
// readable body of ?Unregister@SimpleSceneClass@@UAEXPAVRenderObjClass@@W4RegType@SceneClass@@@Z: Code/Libraries/Source/WWVegas/WW3D2/scene.cpp

// Five-case switch on RegType, each arm removing the object from one scene list.
// The lists are 24 bytes each and contiguous from +0x5C, which the Add and Remove
// conversions in this class already established: +0x5C, +0x74, +0x8C, +0xA4,
// +0xBC, +0xD4, +0xEC.
//
// The first three arms call an out-of-line Remove, the last two inline it into
// Internal_Remove with the pointer adjustment visible -- a null-preserving upcast
// to the list-node base at offset 8. That difference is what says the two groups
// are different list types: a Ref-counting one whose Remove is not inline, and a
// plain one whose Remove is.
class RenderObjClass;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/multilist.h
class MultiListObjectClass
{
public:
	void *m_prev;
	void *m_next;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/multilist.h
class GenericMultiListClass
{
protected:
	bool Internal_Remove(MultiListObjectClass *obj);

private:
	unsigned char m_head[24];
};

template <class T>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/multilist.h
class MultiListClass : public GenericMultiListClass
{
public:
	bool Remove(T *obj) { return Internal_Remove(obj); }
};

template <class T>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/multilist.h
class RefMultiListClass : public MultiListClass<T>
{
public:
	bool Remove(T *obj);
};

class RenderObjBase
{
public:
	virtual ~RenderObjBase();
	int m_refCount;
};

class RenderObjClass : public RenderObjBase, public MultiListObjectClass
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/scene.h
class SceneClass
{
public:
	enum RegType { };
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/scene.h
class SimpleSceneClass
{
public:
	virtual void Unregister(RenderObjClass *obj, SceneClass::RegType for_what);

private:
	unsigned char m_pad[0x58];
	RefMultiListClass<RenderObjClass> m_list5C;
	RefMultiListClass<RenderObjClass> m_list74;
	RefMultiListClass<RenderObjClass> m_list8C;
	RefMultiListClass<RenderObjClass> m_listA4;
	MultiListClass<RenderObjClass> m_listBC;
	MultiListClass<RenderObjClass> m_listD4;
};

// ?Unregister@SimpleSceneClass@@UAEXPAVRenderObjClass@@W4RegType@SceneClass@@@Z
void SimpleSceneClass::Unregister(RenderObjClass *obj, SceneClass::RegType for_what)
{
	switch (for_what) {
	case 0:
		m_list74.Remove(obj);
		break;
	case 1:
		m_list8C.Remove(obj);
		break;
	case 2:
		m_listA4.Remove(obj);
		break;
	case 3:
		m_listBC.Remove(obj);
		break;
	case 4:
		m_listD4.Remove(obj);
		break;
	}
}
