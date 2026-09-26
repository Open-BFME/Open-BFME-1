// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
// Retail 0x007023C0.  The caller at 0x006C8890 reaches this body through
// the pinned BfmeI1015B::bfmeDo1015B thunk at 0x000020CC.  The object stores
// 4,000 0x30-byte slots beginning at this+4, followed by the count and a
// changed flag.

struct BfmeI1015BPoint
{
	float x;
	float y;
	float z;

	void set(float ax, float ay, float az)
	{
		x = ax;
		y = ay;
		z = az;
	}

	void set(const BfmeI1015BPoint *other)
	{
		x = other->x;
		y = other->y;
		z = other->z;
	}

	void sub(const BfmeI1015BPoint *other)
	{
		x -= other->x;
		y -= other->y;
		z -= other->z;
	}

	float lengthSqr() const
	{
		return x * x + y * y + z * z;
	}
};

struct BfmeI1015BSlot
{
	void *object;
	int pad04;
	BfmeI1015BPoint position;
	int state;
	int pad18;
	int pad1c;
	int value20;
	int value24;
	int value28;
	float value2c;
};

struct BfmeI1015BObject
{
	virtual void release();
	int references;
};

__forceinline BfmeI1015BObject *bfmeObjectAt(const void *address)
{
	__asm { }
	return *reinterpret_cast<BfmeI1015BObject * const *>(address);
}

class BfmeI1015B
{
public:
	void bfmeDo1015B(int pointBits, int radiusBits);

	char pad[4];
	BfmeI1015BSlot slots[4000];
	int count;
	bool changed;
};

void BfmeI1015B::bfmeDo1015B(int pointBits, int radiusBits)
{
	const BfmeI1015BPoint &center =
		*reinterpret_cast<const BfmeI1015BPoint *>(pointBits);
	const float &radius = *reinterpret_cast<const float *>(&radiusBits);

	int index = 0;
	if (count > 0)
	{
		float *position = &slots[0].position.z;
		do
		{
			if (*reinterpret_cast<volatile int *>(
				reinterpret_cast<char *>(position) - 0x10) == 0)
				goto skip;
			BfmeI1015BPoint delta;
			BfmeI1015BPoint pointValue;
			pointValue.set(&center);
			delta.set(position[-2], position[-1], position[0]);
			delta.sub(&pointValue);
			if (delta.lengthSqr() < radius * radius)
			{
				*reinterpret_cast<volatile float *>(position - 2) = 0.0f;
				*reinterpret_cast<volatile float *>(position - 1) = 0.0f;
				*reinterpret_cast<volatile float *>(position) = 0.0f;
				BfmeI1015BObject *object = bfmeObjectAt(
					reinterpret_cast<char *>(position) - 0x10);
				*reinterpret_cast<int *>(
					reinterpret_cast<char *>(position) + 0x4) = -1;
				if (object != 0)
				{
					if (--object->references == 0)
						object->release();
					*reinterpret_cast<BfmeI1015BObject * volatile *>(
						reinterpret_cast<char *>(position) - 0x10) = 0;
				}
				*reinterpret_cast<int *>(
					reinterpret_cast<char *>(position) + 0x10) = 0;
				*reinterpret_cast<int *>(
					reinterpret_cast<char *>(position) + 0x14) = 0;
				*reinterpret_cast<int *>(
					reinterpret_cast<char *>(position) + 0x18) = 0;
				*reinterpret_cast<float *>(
					reinterpret_cast<char *>(position) + 0x1c) = 1.0f;
				changed = true;
			}
		skip:
			++index;
			position = reinterpret_cast<float *>(
				reinterpret_cast<char *>(position) + 0x30);
		} while (index < count);
	}
}
