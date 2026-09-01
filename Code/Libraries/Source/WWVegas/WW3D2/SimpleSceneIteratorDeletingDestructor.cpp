// cl: /DNDEBUG /MD /EHsc

class SceneIterator
{
public:
	virtual ~SceneIterator() {}
};

class RenderObjClass;

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

protected:
	SimpleSceneIterator(RefMultiListClass<RenderObjClass> *render_list);

private:
	RefMultiListClass<RenderObjClass> *m_render_list;
	void *m_current;
};

__declspec(noinline) SimpleSceneIterator::SimpleSceneIterator(
	RefMultiListClass<RenderObjClass> *render_list) :
	m_render_list(render_list),
	m_current(render_list->m_first)
{
}

__declspec(noinline) SimpleSceneIterator::~SimpleSceneIterator() {}

void Force_SimpleSceneIterator_Deleting_Destructor(SimpleSceneIterator *iterator)
{
	delete iterator;
}
