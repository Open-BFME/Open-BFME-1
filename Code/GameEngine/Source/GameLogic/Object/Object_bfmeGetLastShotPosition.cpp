// cl: /DNDEBUG /MD /EHsc

union BfmeFiringPositionWord
{
	float f;
	volatile unsigned int u;
};

struct BfmeFiringPosition
{
	BfmeFiringPosition() {}
	BfmeFiringPosition(const BfmeFiringPosition &other)
	{
		x.u = other.x.u;
		y.u = other.y.u;
		z.u = other.z.u;
	}
	BfmeFiringPositionWord x;
	BfmeFiringPositionWord y;
	BfmeFiringPositionWord z;
};

class BfmeFiringTracker
{
public:
	BfmeFiringPosition bfmeGetLastShotPosition() const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	BfmeFiringPosition bfmeGetLastShotPosition() const;

private:
	unsigned char m_pad[0x1ec];
	BfmeFiringTracker *m_firingTracker;
};

BfmeFiringPosition Object::bfmeGetLastShotPosition() const
{
	volatile float scratch = 0.0f;
	BfmeFiringPosition empty;
	empty.x.f = 0.0f;
	empty.y.f = 0.0f;
	empty.z.f = 0.0f;
	return m_firingTracker ? m_firingTracker->bfmeGetLastShotPosition() : empty;
}
