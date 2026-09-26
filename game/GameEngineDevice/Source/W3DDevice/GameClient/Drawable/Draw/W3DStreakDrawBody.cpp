// cl: /O2 /EHsc
// W3DStreakDraw helper at retail 0x0077D6B0.
// The inline x87 block preserves the retail stack slot for distance.

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Vector3
{
public:
	float X;
	float Y;
	float Z;
};

struct BfmeVecOH
{
	float x;
	float y;
	float z;
};

union StreakWidth
{
	float value;
	int raw;
};

class BFMERopeDrawable
{
public:
	const Coord3D *getPosition() const;

	char m_pad[0xb0];
	float m_scaleBase;
	float m_scaleFactor;
};

class BfmeStreakObject
{
};

class Gen_009559f0
{
public:
	int m();
};

class BfmeThingOH
{
public:
	void bfmeGetOH(unsigned int at, BfmeVecOH *out, int *also);
};

class Bitmap2DObjClass
{
public:
	void Add_Point(const Vector3 &point, float width);
	void Delete_Point(unsigned int point_idx);
};

struct Rva00955BC0Vec
{
	float x;
	float y;
	float z;
};

class Rva00955BC0
{
public:
	void set(const Rva00955BC0Vec *value);
};

extern void d_00955a00(void);

class Gen_00955a00Call
{
public:
	void setPoint(unsigned int at, const Vector3 &point, float width);
};

class W3DStreakDrawModuleData
{
public:
	char m_pad[8];
	float m_length;
	float m_initialWidth;
	float m_vectorX;
	float m_vectorY;
	float m_vectorZ;
	int m_segmentCount;
};

class W3DStreakDraw
{
public:
	void streakBody0077D6B0();

private:
	void *m_vtable;
	const W3DStreakDrawModuleData *m_moduleData;
	BFMERopeDrawable *m_drawable;
	BfmeStreakObject *volatile m_streak;
};

void W3DStreakDraw::streakBody0077D6B0()
{
	const W3DStreakDrawModuleData *data = m_moduleData;
	if (m_streak != 0)
	{
		const Vector3 *position = (const Vector3 *)m_drawable->getPosition();
		StreakWidth pointWidth;
		BfmeVecOH point;

		if (reinterpret_cast<Gen_009559f0 *>(m_streak)->m() == 0)
		{
			reinterpret_cast<Bitmap2DObjClass *>(m_streak)->Add_Point(*position, 0.0f);
		}
		else
		{
			if (reinterpret_cast<Gen_009559f0 *>(m_streak)->m() == 1)
			{
				reinterpret_cast<BfmeThingOH *>(m_streak)->bfmeGetOH(0, &point, &pointWidth.raw);

				const float x = position->X - point.x;
				const float y = position->Y - point.y;
				const float z = position->Z - point.z;
				volatile float square;
				volatile float distance;
				square = x * x + y * y + z * z;
				__asm {
					fld square
					fsqrt
					fstp distance
				}
				pointWidth.value = distance + pointWidth.value;
				reinterpret_cast<Bitmap2DObjClass *>(m_streak)->Add_Point(*position, pointWidth.value);
			}
			else
			{
				reinterpret_cast<BfmeThingOH *>(m_streak)->bfmeGetOH(
					reinterpret_cast<Gen_009559f0 *>(m_streak)->m() - 2,
					&point, &pointWidth.raw);

				const float x = position->X - point.x;
				const float y = position->Y - point.y;
				const float z = position->Z - point.z;
				volatile float distance;
				volatile float square;
				square = x * x + y * y + z * z;
				__asm {
					fld square
					fsqrt
					fstp distance
				}
				pointWidth.value = distance + pointWidth.value;

				typedef void (Gen_00955a00Call::*SetPoint)(
					unsigned int, const Vector3 &, float);
				union
				{
					void (*raw)(void);
					SetPoint member;
				} setPointCall;
				setPointCall.raw = ::d_00955a00;
				(reinterpret_cast<Gen_00955a00Call *>(m_streak)->*setPointCall.member)(
					reinterpret_cast<Gen_009559f0 *>(m_streak)->m() - 1,
					*position, pointWidth.value);
				if (data->m_length / (float)(unsigned int)data->m_segmentCount < distance)
				{
					reinterpret_cast<Bitmap2DObjClass *>(m_streak)->Add_Point(*position, pointWidth.value);
				}
				while (reinterpret_cast<Gen_009559f0 *>(m_streak)->m() >= 2)
				{
					StreakWidth pruningWidth;
					reinterpret_cast<BfmeThingOH *>(m_streak)->bfmeGetOH(1, &point, &pruningWidth.raw);
					if (!(pointWidth.value - data->m_length > pruningWidth.value))
					{
						break;
					}
					reinterpret_cast<Bitmap2DObjClass *>(m_streak)->Delete_Point(0);
				}
			}
		}

		float scale = m_drawable->m_scaleFactor * m_drawable->m_scaleBase;
		point.x = scale * data->m_vectorX;
		point.y = scale * data->m_vectorY;
		point.z = scale * data->m_vectorZ;
		reinterpret_cast<Rva00955BC0 *>(m_streak)->set(
			(const Rva00955BC0Vec *)&point);
	}
}
