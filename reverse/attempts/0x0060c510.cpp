// ?applyTo@Gen0060CBB0@@AAEXIPAUGen0060CBB0Pair@@@Z
// partial score=0.95 date=2026-09-02
// cl: /DNDEBUG /MD /GX- /O2 /Ob2

struct Gen0060CBB0Pair
{
	float first;
	float second;
};

struct Gen0060CBB0Coord3D
{
	float x;
	float y;
	float z;

	Gen0060CBB0Coord3D()
	{
	}

	Gen0060CBB0Coord3D(const Gen0060CBB0Coord3D &other)
		: x(other.x), y(other.y), z(other.z)
	{
	}

};

class Gen0060C510Target
{
public:
	virtual ~Gen0060C510Target();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void setPosition(Gen0060CBB0Coord3D position);

	void getPosition(Gen0060CBB0Coord3D *position);
};

class Gen0060CBB0
{
private:
	void applyTo(unsigned int targetValue, Gen0060CBB0Pair *point);
};

void Gen0060CBB0::applyTo(unsigned int targetValue, Gen0060CBB0Pair *point)
{
	Gen0060C510Target *target = (Gen0060C510Target *)targetValue;
	if (target != 0) {
		Gen0060CBB0Coord3D position;
		target->getPosition(&position);
		position.y = point->second;
		position.x = point->first;
		target->setPosition(position);
	}
}
