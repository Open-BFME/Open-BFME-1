// cl: /DNDEBUG /MD /EHsc

class SceneIterator
{
public:
	virtual ~SceneIterator() {}
};

class SimpleSceneIterator : public SceneIterator
{
public:
	virtual ~SimpleSceneIterator();
};

__declspec(noinline) SimpleSceneIterator::~SimpleSceneIterator() {}

void Force_SimpleSceneIterator_Vtable()
{
	SimpleSceneIterator iterator;
}

void Force_SimpleSceneIterator_Deleting_Destructor(SimpleSceneIterator *iterator)
{
	delete iterator;
}
