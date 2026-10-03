// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void notifyModelConditionChanged();

	char m_pad[0x128];
	unsigned int m_flags;
};

// TransportContain::onRemoving is the ledger-owned body reached by the
// retail ILT for this call (0x00041E34 -> 0x0022E340).
class TransportContain
{
public:
	virtual void onRemoving(Object *object);
};

class Rva0022BDE0Obj
{
public:
	void apply(Object *obj);
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
		reinterpret_cast<TransportContain *>(this)->TransportContain::onRemoving(obj);
	}
}
