// cl: /DNDEBUG /MD /EHsc

typedef unsigned int UnsignedInt;

enum UpdateSleepTime
{
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

class BodyModuleInterface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
};

class Object
{
};

class ObjectRecoveryHelper
{
public:
	virtual UpdateSleepTime update();
};

UpdateSleepTime ObjectRecoveryHelper::update()
{
	Object *object = *reinterpret_cast<Object **>(
		reinterpret_cast<unsigned char *>(this) - 8);
	BodyModuleInterface *body = *reinterpret_cast<BodyModuleInterface **>(
		reinterpret_cast<unsigned char *>(object) + 0x200);
	body->slot0c();
	return UPDATE_SLEEP_FOREVER;
}
