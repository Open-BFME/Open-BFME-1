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

class SimpleSceneClass;

class SimpleSceneIterator : public SceneIterator
{
public:
	virtual ~SimpleSceneIterator() {}

protected:
	SimpleSceneIterator(RefMultiListClass<RenderObjClass> *render_list) :
		m_render_list(render_list),
		m_current(render_list->m_first)
	{
	}

private:
	RefMultiListClass<RenderObjClass> *m_render_list;
	void *m_current;

	friend class SimpleSceneClass;
};

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
