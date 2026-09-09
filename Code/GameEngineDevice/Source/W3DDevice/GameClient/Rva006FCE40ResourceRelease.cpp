// Retail 0x006FCE40 (105 bytes): detach, release and clear two resources.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// The +0x74 member is not proven to have the owner's 0x011207C0 table.
// 0x006FC970 installs that table in the owner at offset zero; this member is
// loaded from [owner+0x74].  Keep the member as a raw scene-like interface and
// call only the proven fourth vtable entry (table byte offset 0x0c).
// SceneClass/SimpleSceneClass retail tables independently identify slot 3 as
// Remove_Render_Object, but the producer/type of this +0x74 object is not
// established, so this view deliberately emits no scene vtable or 29-slot
// invented class.  The resource view records only the proven RefCountClass ABI:
// vptr at zero, refcount at +4, and Delete_This at vtable slot zero.

class Rva006FCE40Resource;

// This is a four-slot raw prefix solely to express the MSVC virtual-call ABI.
// The first three declarations are positional placeholders, not claimed
// methods.  No object is constructed here, so this TU emits no local vtable.
class __declspec(novtable) Rva006FCE40SceneView
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void remove_resource(Rva006FCE40Resource *resource);
};

class Rva006FCE40Resource
{
public:
	virtual void deleteThis();

	void release()
	{
		--m_refs;
		if (m_refs == 0)
			deleteThis();
	}

private:
	int m_refs;
};

class Rva006FCE40Owner
{
public:
	void releaseInterfaces();

private:
	char m_beforeScene[0x74];
	Rva006FCE40SceneView *m_scene;
	char m_betweenSceneAndFirst[0x0c];
	Rva006FCE40Resource *m_first;
	char m_betweenResources[0xb0];
	Rva006FCE40Resource *m_second;
};

void Rva006FCE40Owner::releaseInterfaces()
{
	if (m_scene != 0)
	{
		if (m_first != 0)
			m_scene->remove_resource(m_first);

		if (m_second != 0)
			m_scene->remove_resource(m_second);
	}

	if (m_first != 0)
	{
		m_first->release();
		m_first = 0;
	}

	if (m_second != 0)
	{
		m_second->release();
		m_second = 0;
	}
}
