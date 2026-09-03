// cl: /DNDEBUG /MD /EHsc
// Retail 0x002B7F40: switch on a 0/1 argument, then if the object at this-0x338
// has model-condition bit 0x100 set, clear it and notify.

typedef unsigned int UnsignedInt;

enum StateExitType
{
	EXIT_NORMAL = 0,
	EXIT_RESET = 1
};

class Object
{
public:
	void clearSnow()
	{
		UnsignedInt bits = m_modelConditionWord;
		if (bits & 0x100u)
		{
			m_modelConditionWord = bits & ~0x100u;
			notifyModelConditionChanged();
		}
	}

	void notifyModelConditionChanged();

private:
	unsigned char m_pad[0x118];
	UnsignedInt m_modelConditionWord;
};

class Rva002B7F40
{
public:
	void onExit(StateExitType status);
};

// ?onExit@Rva002B7F40@@QAEXW4StateExitType@@@Z
void Rva002B7F40::onExit(StateExitType status)
{
	switch (status)
	{
	case EXIT_NORMAL:
		(*(Object **)((char *)this - 0x338))->clearSnow();
		break;
	case EXIT_RESET:
		(*(Object **)((char *)this - 0x338))->clearSnow();
		break;
	}
}
