// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void notifyModelConditionChanged();

	char m_pad[0x128];
	unsigned int m_flags;
};

class Rva0022BDE0Obj
{
public:
	void apply(Object *obj);
	void finish(Object *obj);
};

void Rva0022BDE0Obj::apply(Object *obj)
{
	if (obj)
	{
		if (*reinterpret_cast<unsigned char *>(&obj->m_flags) & 0x40)
		{
			obj->m_flags &= ~0x40u;
			obj->notifyModelConditionChanged();
		}
		finish(obj);
	}
}
