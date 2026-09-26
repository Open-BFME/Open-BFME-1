// Gen_001DCF50::canEnter supplies the context and invokes this callback.
enum Relationship
{
	Relationship_Zero = 0
};

class Object
{
public:
	Relationship getRelationship(const Object *other) const;
};

struct IterUser001DCF20
{
	Object *object;
	unsigned char flag;
};

void iterRel001DCF20(Object *contained, void *userData)
{
	IterUser001DCF20 *context = (IterUser001DCF20 *)userData;
	if (context->object->getRelationship(contained) == 0)
		context->flag = 1;
}
