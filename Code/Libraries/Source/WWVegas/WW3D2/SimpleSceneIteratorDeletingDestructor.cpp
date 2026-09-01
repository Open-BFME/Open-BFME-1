// cl: /DNDEBUG /MD /EHsc

class SimpleSceneIterator
{
public:
	virtual ~SimpleSceneIterator();
};

__declspec(noinline) SimpleSceneIterator::~SimpleSceneIterator() {}

void Force_SimpleSceneIterator_Deleting_Destructor(SimpleSceneIterator *iterator)
{
	delete iterator;
}
