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
	SimpleSceneIterator(RefMultiListClass<RenderObjClass> *render_list);

private:
	RefMultiListClass<RenderObjClass> *m_render_list;
	void *m_current;
};

// The retail constructor and deleting destructor are emitted by Create_Iterator.
__declspec(noinline) SimpleSceneIterator::~SimpleSceneIterator() {}
