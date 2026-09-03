// cl: /DNDEBUG /MD /EHsc
// readable body of ?Remove_All_Render_Objects@SimpleSceneClass@@UAEXXZ: Code/Libraries/Source/WWVegas/WW3D2/scene.cpp
// BFME's SimpleSceneClass has a larger pre-list layout than the Zero Hour class.

class RenderObjClass;

struct BfmeSceneListNode
{
	unsigned char unused[0x0c];
	unsigned char *object_link;
};

struct BfmeSceneList
{
	void *unused;
	BfmeSceneListNode *head;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/scene.h
class SimpleSceneClass
{
public:
	virtual void slot_0(void);
	virtual void slot_1(void);
	virtual void Add_Render_Object(RenderObjClass *obj);
	virtual void Remove_Render_Object(RenderObjClass *obj);
	virtual void Remove_All_Render_Objects(void);

private:
	RenderObjClass *Peek_Render_Head(void) const
	{
		if (render_list.head ==
			reinterpret_cast<const BfmeSceneListNode *>(&render_list))
			return 0;
		if (render_list.head->object_link == 0)
			return 0;
		return reinterpret_cast<RenderObjClass *>(
			render_list.head->object_link - 8);
	}

	unsigned char pad_to_render_list[0x5c];
	BfmeSceneList render_list;
};

// ?Remove_All_Render_Objects@SimpleSceneClass@@UAEXXZ
void SimpleSceneClass::Remove_All_Render_Objects(void)
{
	RenderObjClass *obj;
	while ((obj = Peek_Render_Head()) != 0)
		Remove_Render_Object(obj);
}
