// cl: /DNDEBUG /MD /EHsc

class Rva0025FA10Object
{
public:
	void clearCondition(int condition);
};

struct Rva0026DE30ModuleData
{
	unsigned char m_lead[0x220];
	unsigned int m_add220;
	unsigned char m_gap224[0x254 - 0x224];
	unsigned int m_add254;
	unsigned int m_mode;
};

struct GameLogic
{
	unsigned char m_lead[0x3c];
	unsigned int m_frame;
};

extern GameLogic *TheGameLogic;

class Rva0025FA10HeroModeUpdate
{
public:
	void begin();
	void applyModeClear();

private:
	unsigned char m_lead[4];
	Rva0026DE30ModuleData *m_data;
	Rva0025FA10Object *m_object;
	unsigned char m_gap[0x20];
	unsigned int m_endFrame;
};

// ?applyModeClear@Rva0025FA10HeroModeUpdate@@QAEXXZ
void Rva0025FA10HeroModeUpdate::applyModeClear()
{
	begin();
	Rva0026DE30ModuleData *data = m_data;
	unsigned int mode = data->m_mode;
	Rva0025FA10Object *object = m_object;
	if (mode == 1)
		object->clearCondition(0x12);
	else if (mode == 2)
		object->clearCondition(0x13);
	m_endFrame = data->m_add220 + data->m_add254 + TheGameLogic->m_frame;
}
