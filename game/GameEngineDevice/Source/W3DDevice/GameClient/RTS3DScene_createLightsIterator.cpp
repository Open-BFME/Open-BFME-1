// cl: /DNDEBUG /MD /EHsc

class RenderObjClass;

template <class T>
class RefMultiListClass
{
public:
	char m_fields[8];
	void *m_head;
};

template <class T>
class RefMultiListIterator
{
public:
	RefMultiListIterator(RefMultiListClass<T> *list)
	{
		m_list = list;
		m_current = list->m_head;
	}

private:
	RefMultiListClass<T> *m_list;
	void *m_current;
};

class RTS3DScene
{
public:
	RefMultiListIterator<RenderObjClass> *createLightsIterator();

private:
	char m_fields[0x8c];
	RefMultiListClass<RenderObjClass> m_lightList;
};

RefMultiListIterator<RenderObjClass> *RTS3DScene::createLightsIterator()
{
	return new RefMultiListIterator<RenderObjClass>(&m_lightList);
}
