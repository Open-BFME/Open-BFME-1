// cl: /DNDEBUG /MD /EHs-c-
// TerrainLogic P48 radius clear, retail 0x001A6410.

typedef float Real;

extern "C" double sqrt(double value);
#pragma intrinsic(sqrt)

static Real squareP48ClearNear(Real value)
{
	return value * value;
}

static Real squareVolatileP48ClearNear(const volatile Real &value)
{
	return value * value;
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct Coord2DP48ClearNear
{
	Coord2DP48ClearNear(Real initialX, Real initialY) : x(initialX), y(initialY) {}
	Real length() const
	{
		return (Real)sqrt(squareVolatileP48ClearNear(x) + squareP48ClearNear(y));
	}
	Real x;
	Real y;
	Real unused;
};

struct TerrainLogicP48Rec
{
	Real x;
	Real y;
	Real z;
	int key;
	int m10;
	int m14;
	char m18;
	char pad19[0x0F];
	int amount;
	char m2c;
	char m2d;
	char pad2e[2];
};

class TerrainVisualNotify_001A6410
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void notify(int key);
};

struct GameLogicFrame_001A6410
{
	char pad[0x3C];
	int frame;
};

class TerrainLogicP48ClearNear
{
public:
	void clearNear(const Coord3D *position, Real radius);

private:
	char m_pad[0x55C];
	TerrainLogicP48Rec *m_begin;
	TerrainLogicP48Rec *m_end;
	char m_pad564[0x18F0 - 0x564];
	int m_frameStamp;
};

void TerrainLogicP48ClearNear::clearNear(const Coord3D *position, Real radius)
{
	TerrainLogicP48Rec *record = m_begin;
	while (record != m_end)
	{
		register int key = record->key;
		if (key != 0)
		{
			Coord2DP48ClearNear delta(position->x, position->y);
			delta.x -= record->x;
			delta.y -= record->y;
			if (delta.length() <= radius)
			{
				record->x = 0;
				record->y = 0;
				record->z = 0;
				record->key = 0;
				record->m10 = 0;
				record->m14 = 0;
				record->m18 = 0;
				record->amount = 1;
				record->m2c = 1;
				record->m2d = 1;
				TerrainVisualNotify_001A6410 *visual =
					*(TerrainVisualNotify_001A6410 **)0x012F7014;
				visual->notify(key);
				GameLogicFrame_001A6410 *logic =
					*(GameLogicFrame_001A6410 **)0x012F0898;
				m_frameStamp = logic->frame;
			}
		}
		record++;
	}
}
