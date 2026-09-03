// cl: /DNDEBUG /MD /EHsc

class Rva0025FA10Object
{
public:
	bool hasCondition( int condition );
	void clearCondition( int condition );
};

struct Rva0025FA10ModuleData
{
	unsigned char m_lead[ 0x258 ];
	unsigned int m_duration;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
struct GameLogic
{
	unsigned char m_lead[ 0x3c ];
	unsigned int m_frame;
};

extern GameLogic *TheGameLogic;

class Rva0025FA10HeroModeUpdate
{
public:
	void update();
	void begin();

private:
	unsigned char m_lead[ 4 ];
	Rva0025FA10ModuleData *m_data;
	Rva0025FA10Object *m_object;
	unsigned char m_gap[ 0x20 ];
	unsigned int m_endFrame;
};

void Rva0025FA10HeroModeUpdate::update()
{
	begin();
	Rva0025FA10Object *object = m_object;
	Rva0025FA10ModuleData *data = m_data;
	if ( object->hasCondition( 0x1b ) )
		object->clearCondition( 0x1b );
	m_endFrame = TheGameLogic->m_frame + data->m_duration;
}
