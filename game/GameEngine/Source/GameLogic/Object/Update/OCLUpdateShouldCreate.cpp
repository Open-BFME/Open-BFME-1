// cl: /O2 /Ob0

class GameLogic
{
public:
	unsigned char m_beforeFrame[0x3C];
	unsigned int m_frame;
};

extern GameLogic *TheGameLogic;

class Object
{
public:
	unsigned char m_beforeStatusBits[0x90];
	unsigned char m_statusBits;
};

class OCLUpdate
{
protected:
	unsigned char shouldCreate();

private:
	unsigned int m_moduleStorage[2];
	Object *m_object;
	unsigned int m_beforeNextCreationFrame[5];
	unsigned int m_nextCreationFrame;
};

unsigned char OCLUpdate::shouldCreate()
{
	if ((unsigned int)TheGameLogic->m_frame < m_nextCreationFrame)
		return 0;

	unsigned char statusBits = m_object->m_statusBits;
	statusBits >>= 2;
	statusBits = ~statusBits;
	statusBits &= 1;

	return statusBits;
}
