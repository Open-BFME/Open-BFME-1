// cl: /DNDEBUG /MD /EHsc
// readable body of ?Register@SimpleSceneClass@@UAEXPAVRenderObjClass@@W4RegType@SceneClass@@@Z: Code/Libraries/Source/WWVegas/WW3D2/scene.cpp

// The Add mirror of Unregister: five cases on RegType over the same 24-byte
// scene lists running from +0x5C, confirmed by Add_Render_Object,
// Remove_Render_Object and Unregister all indexing that same table.
//
// Three shapes appear. The +0x74 and +0xA4 arms insert at the head and take a
// reference when the node was not already in the list; +0x8C does the same
// through Internal_Add_Tail; +0xBC and +0xD4 insert without taking a reference,
// which is what lets those two tail call.
//
// The reference test is written `== true` because retail compares with cmp al,1
// rather than test al,al.
//
// The list primitives are called directly rather than through the Add wrappers
// the real headers declare. Written as wrappers the compiler declines to inline
// them and emits an out-of-line call per arm, which is not what retail has --
// there the whole body is one flat switch over Internal_Add. The bytes decide
// the shape; the wrapper is where the name lives, not where the code does.
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
	// The primitives stay protected so they mangle as I-- , which is how the
	// ledger already carries them. Friendship is what makes them reachable from
	// a scene rather than from a list, and it does not touch the mangling.
	friend class SimpleSceneClass;

protected:
	bool Internal_Add(MultiListObjectClass *obj, bool onlyonce = true);
	bool Internal_Add_Tail(MultiListObjectClass *obj, bool onlyonce = true);

private:
	unsigned char m_head[24];
};

class RenderObjBase
{
public:
	virtual ~RenderObjBase();
	int m_refCount;

	void Add_Ref(void) { m_refCount++; }
};

// The node base is the second base, so every upcast to it is null preserving --
// that is the test/lea/xor sequence in front of each call.
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
	virtual void Register(RenderObjClass *obj, SceneClass::RegType for_what);

private:
	unsigned char m_pad[0x58];
	GenericMultiListClass m_list5C;
	GenericMultiListClass m_list74;
	GenericMultiListClass m_list8C;
	GenericMultiListClass m_listA4;
	GenericMultiListClass m_listBC;
	GenericMultiListClass m_listD4;
};

// ?Register@SimpleSceneClass@@UAEXPAVRenderObjClass@@W4RegType@SceneClass@@@Z
void SimpleSceneClass::Register(RenderObjClass *obj, SceneClass::RegType for_what)
{
	switch (for_what) {
	case 0:
		if (m_list74.Internal_Add(obj, true) == true) {
			obj->Add_Ref();
		}
		break;
	case 1:
		if (m_list8C.Internal_Add_Tail(obj, true) == true) {
			obj->Add_Ref();
		}
		break;
	case 2:
		if (m_listA4.Internal_Add(obj, true) == true) {
			obj->Add_Ref();
		}
		break;
	case 3:
		m_listBC.Internal_Add(obj, true);
		break;
	case 4:
		m_listD4.Internal_Add(obj, true);
		break;
	}
}
