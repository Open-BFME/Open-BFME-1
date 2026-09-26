// cl: /DNDEBUG /MD /EHsc
//
// ExperienceLevelSystem::init at retail RVA 0x0037D110.  The constructor at
// 0x00381480 installs vtable 0x010EA948, whose slot 1 is the subsystem init
// method.  The body is intentionally empty and occupies one retail byte.

class ExperienceLevelSystem
{
public:
	virtual void init();
};

// ?init@ExperienceLevelSystem@@UAEXXZ
void ExperienceLevelSystem::init()
{
}
