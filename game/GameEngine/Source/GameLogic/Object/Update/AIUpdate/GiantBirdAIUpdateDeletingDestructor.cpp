// cl: /DNDEBUG /MD /EHsc
//
// The module constructor at retail 0x002C2430 installs primary vtable
// 0x010C7F40.  Its first slot reaches the scalar deleting destructor at
// 0x002C2800, which calls the public complete destructor (matched at
// 0x002C2720) through ILT 0x00030792.

class GiantBirdAIUpdate;
void Force_GiantBirdAIUpdate_Deleting_Destructor(GiantBirdAIUpdate *update);

class GiantBirdAIUpdate
{
	friend void Force_GiantBirdAIUpdate_Deleting_Destructor(
		GiantBirdAIUpdate *update);

public:
	virtual ~GiantBirdAIUpdate();
};

void Force_GiantBirdAIUpdate_Deleting_Destructor(GiantBirdAIUpdate *update)
{
	GiantBirdAIUpdate value;
	(void)update;
}
