// cl: /DNDEBUG /MD /EHsc

// Retail ILT 000348EC reaches the matched signed-int handler at 001C9A10.
class Gen001C9A10
{
public:
	void handle(int player);
};

// Retail ILT 00017D5F reaches the matched nullary member at 002A8CE0.
class SpecialAbilityUpdate
{
public:
	void startUnpacking();
};

struct Rva0026DE30ModuleData
{
	unsigned char m_lead[0x220];
	unsigned int m_add220;
	unsigned char m_gap224[0x254 - 0x224];
	unsigned int m_add254;
	unsigned int m_mode;
};

struct Rva0026DE30LogicView
{
	unsigned char m_lead[0x3c];
	unsigned int m_frame;
};

// Retail's GameLogic singleton (0x012F0898) is EA's `GameLogic *TheGameLogic`
// (mangled ?TheGameLogic@@3PAVGameLogic@@A, defined in GameLogic.cpp).  This TU
// keeps its own partial view of the object and casts at each use.
class GameLogic;

extern GameLogic *TheGameLogic;

class Rva0025FA10HeroModeUpdate
{
public:
	void applyModeClear();

private:
	unsigned char m_lead[4];
	Rva0026DE30ModuleData *m_data;
	Gen001C9A10 *m_object;
	unsigned char m_gap[0x20];
	unsigned int m_endFrame;
};

// ?applyModeClear@Rva0025FA10HeroModeUpdate@@QAEXXZ
void Rva0025FA10HeroModeUpdate::applyModeClear()
{
	((SpecialAbilityUpdate *)this)->startUnpacking();
	Rva0026DE30ModuleData *data = m_data;
	unsigned int mode = data->m_mode;
	Gen001C9A10 *object = m_object;
	if (mode == 1)
		object->handle(0x12);
	else if (mode == 2)
		object->handle(0x13);
	m_endFrame = data->m_add220 + data->m_add254 +
		((Rva0026DE30LogicView *)TheGameLogic)->m_frame;
}
