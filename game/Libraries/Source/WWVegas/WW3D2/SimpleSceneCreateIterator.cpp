// cl: /DNDEBUG /MD /EHsc

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/scene.h
class RenderObjClass;

class SceneIterator
{
public:
	virtual ~SceneIterator() {}
	virtual void First() = 0;
	virtual void Next() = 0;
	virtual bool Is_Done() = 0;
	virtual RenderObjClass *Current_Item() = 0;
};

template <class T> class RefMultiListClass
{
public:
	void *m_unused[2];
	void *m_first;
};

class SimpleSceneClass;

class SimpleSceneIterator : public SceneIterator
{
public:
	virtual ~SimpleSceneIterator();
	// Retail vtable 0x00D3CF34: destructor, First, Next, Is_Done, Current_Item.
	virtual void First();
	virtual void Next();
	virtual bool Is_Done();
	virtual RenderObjClass *Current_Item();

protected:
	__forceinline SimpleSceneIterator(RefMultiListClass<RenderObjClass> *render_list) :
		m_render_list(render_list),
		m_current(render_list->m_first)
	{
	}

private:
	RefMultiListClass<RenderObjClass> *m_render_list;
	void *m_current;

	friend class SimpleSceneClass;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/scene.h
class SimpleSceneClass
{
public:
	virtual SceneIterator *Create_Iterator();

private:
	unsigned char m_before_render_list[0x58];
	RefMultiListClass<RenderObjClass> m_render_list;
};

SceneIterator *SimpleSceneClass::Create_Iterator()
{
	return new SimpleSceneIterator(&m_render_list);
}
