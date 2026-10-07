// cl: /DNDEBUG /MD /EHsc
//
// AIUncontrollableCower scalar-deleting destructor at retail RVA 0x00182320
// (30 bytes): slot 0 of vtable 0x010991D0, reached through ILT 0x0000C38D.
// Constructor 0x001744C0 installs that table after State's constructor has taken
// the literal "AICowerState", which is why the class was once filed as
// AICowerState. The table's own class-name slot (slot 2, 0x00174500) returns
// "AIUncontrollableCower"; AICowerState's table 0x01098408 returns "AICowerState".

class AIUncontrollableCower
{
public:
	virtual ~AIUncontrollableCower();

private:
	friend void forceAIUncontrollableCowerDeletingDestructor();
};

void forceAIUncontrollableCowerDeletingDestructor()
{
	AIUncontrollableCower value;
}
