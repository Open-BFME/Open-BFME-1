// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;
typedef unsigned int UnsignedInt;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Coord3D() {}
	Coord3D(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
	Coord3D(const Coord3D &other)
		: x(other.x), y(other.y), z(other.z) {}
	~Coord3D() {}

	float x;
	float y;
	float z;
};

class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	int bfmeLayerForPosition(Object *object, Coord3D position);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AI
{
public:
	unsigned char m_pad[0x0c];
	Pathfinder *m_pathfinder;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	unsigned char m_pad[0x3c];
	UnsignedInt m_frame;
};

extern AI *TheAI;
extern GameLogic *TheGameLogic;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void bfmeExpireForcedGroundLayer();

private:
	unsigned char m_pad000[0x38];
	Coord3D m_position;
	unsigned char m_pad044[0x3a8 - 0x44];
	Bool m_forceGroundLayer;
	unsigned char m_pad3a9[3];
	UnsignedInt m_forceGroundLayerFrame;
};

void Object::bfmeExpireForcedGroundLayer()
{
	if (m_forceGroundLayer &&
		m_forceGroundLayerFrame + 13 <= TheGameLogic->m_frame)
	{
		Coord3D position(m_position);
		if (TheAI->m_pathfinder->bfmeLayerForPosition(
			this, position) == 1)
		{
			m_forceGroundLayer = false;
			m_forceGroundLayerFrame = static_cast<UnsignedInt>(-1);
		}
	}
}
