// ?doDrawModule@W3DStreakDraw@@UAEXPBUMatrix3D@@@Z
// partial score=0.97 date=2026-09-10
// cl: /O2 /EHsc

#include <math.h>

extern "C" double __cdecl sqrt(double value);
#pragma intrinsic(sqrt)

struct Matrix3D;

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

struct BfmeStreakVector
{
	float x;
	float y;
	float z;
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
public:
	int m();
	void bfmeGetOH(unsigned int at, BfmeVecOH *out, int *also);
	void Add_Point(const Vector3 &point, float width);
	void Delete_Point(unsigned int point_idx);
	void setVector(const BfmeStreakVector *value);
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
	virtual void doDrawModule(const Matrix3D *transformMtx);

private:
	const W3DStreakDrawModuleData *m_moduleData;
	BFMERopeDrawable *m_drawable;
	BfmeStreakObject *volatile m_streak;
};

// ?doDrawModule@W3DStreakDraw@@UAEXPBUMatrix3D@@@Z
void W3DStreakDraw::doDrawModule(const Matrix3D *)
{
	const W3DStreakDrawModuleData *data = m_moduleData;
	if (m_streak != 0)
	{
		const Vector3 *position = (const Vector3 *)m_drawable->getPosition();
		StreakWidth pointWidth;
		BfmeVecOH point;

		if (m_streak->m() == 0)
		{
			m_streak->Add_Point(*position, 0.0f);
		}
		else
		{
			if (m_streak->m() == 1)
			{
				m_streak->bfmeGetOH(0, &point, &pointWidth.raw);

				const float x = position->X - point.x;
				const float y = position->Y - point.y;
				const float z = position->Z - point.z;
				volatile float distance;
				volatile float square;
				square = x * x + y * y + z * z;
				distance = (float)sqrt(square);
				pointWidth.value = distance + pointWidth.value;
				m_streak->Add_Point(*position, pointWidth.value);
			}
			else
			{
				m_streak->bfmeGetOH(
					m_streak->m() - 2,
					&point, &pointWidth.raw);

				const float x = position->X - point.x;
				const float y = position->Y - point.y;
				const float z = position->Z - point.z;
				volatile float square;
				volatile float distance;
				square = x * x + y * y + z * z;
				distance = (float)sqrt(square);
				pointWidth.value = distance + pointWidth.value;

				m_streak->setPoint(
					m_streak->m() - 1, *position, pointWidth.value);
				if (data->m_length / (float)(unsigned int)data->m_segmentCount <= distance)
				{
					m_streak->Add_Point(*position, pointWidth.value);
				}
				while (m_streak->m() >= 2)
				{
					StreakWidth pruningWidth;
					m_streak->bfmeGetOH(1, &point, &pruningWidth.raw);
					if (pointWidth.value - data->m_length < pruningWidth.value)
					{
						break;
					}
					m_streak->Delete_Point(0);
				}
			}
		}

		float scale = m_drawable->m_scaleFactor * m_drawable->m_scaleBase;
		point.x = scale * data->m_vectorX;
		point.y = scale * data->m_vectorY;
		point.z = scale * data->m_vectorZ;
		m_streak->setVector((const BfmeStreakVector *)&point);
	}
}
