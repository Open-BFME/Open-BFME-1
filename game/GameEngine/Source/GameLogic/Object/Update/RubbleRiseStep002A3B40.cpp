// cl: /O2 /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib
// Retail 0x002A3B40 (1009 bytes). The source-path literal and calls to
// RubbleRiseUpdate::doPhaseStuff prove the family. This address-derived
// type represents the secondary interface at complete-module+0x10.
// Module-data fields come from RubbleRiseUpdateBuildFieldParse.cpp; state
// offsets agree with RubbleRiseUpdateXfer.cpp. Object's 40-byte condition
// mask starts at +0x110; this routine toggles indices 58 and 59.
// Native Vector3 argument order and Matrix3D copying reproduce the x87
// spills. Retail finishes at height >= target, including exact equality.
// 0x520E is bound by its existing ILT symbol: the named ledger owner is
// StructureCollapseUpdate, so no new semantic claim is made for that call.

#include "matrix3d.h"
struct Coord3D
{
	float x, y, z;
};
class Drawable
{
  public:
	char m_pad00[0x198];
	Matrix3D matrix;
	const Matrix3D *getInstanceMatrix() const
	{
		return &matrix;
	}
	void setInstanceMatrix(const Matrix3D *, bool);
};
class Thing
{
  public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0c();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual void v1c();
	virtual void v20();
	virtual void v24();
	virtual Drawable *getDrawable() const;
	char m_pad04[0x38 - 4];
	Coord3D m_cachedPos;
	float m_cachedAngle;
	const Coord3D *getPosition() const
	{
		return &m_cachedPos;
	}
	void setPosition(const Coord3D *);
	void setOrientation(float);
};
class Body3B40
{
  public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0c();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual void v1c();
	virtual void v20();
	virtual void v24();
	virtual void v28();
};
struct Conditions3B40
{
	unsigned words[10];
	unsigned test(int i) const
	{
		return words[i >> 5] & (1u << (i & 31));
	}
	void set(int i)
	{
		words[i >> 5] |= 1u << (i & 31);
	}
	void reset(int i)
	{
		words[i >> 5] &= ~(1u << (i & 31));
	}
};
class Object : public Thing
{
  public:
	char m_pad48[0x110 - 0x48];
	Conditions3B40 flags;
	char m_pad138[0x200 - 0x138];
	Body3B40 *body;
	void notifyModelConditionChanged();
};
class Gen_001BEC20
{
  public:
	int bfmeScale() const;
};
class GameLogic
{
  public:
	char m_pad00[0x3c];
	unsigned m_frame;
};
extern GameLogic *TheGameLogic;
class GlobalData
{
  public:
	char m_pad00[0x1ac];
	float m_gravity;
};
extern GlobalData *TheWritableGlobalData;
class TerrainLogic
{
  public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0c();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual float height(float, float, int, void *, bool);
};
extern TerrainLogic *TheTerrainLogic;
int GetGameLogicRandomValue(int, int, char *, int);
float GetGameLogicRandomValueReal(float, float, char *, int);
float GetGameClientRandomValueReal(float, float, char *, int);
#define FILEPATH                                                                                   \
	"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\RubbleRiseUpdate.cpp"
enum RubbleRisePhaseType
{
	Phase0,
	Phase1,
	Phase2,
	Phase3
};
class RubbleRiseUpdate
{
  protected:
	void doPhaseStuff(RubbleRisePhaseType, const Coord3D *);

  public:
	void phase(RubbleRisePhaseType p, const Coord3D *pos)
	{
		doPhaseStuff(p, pos);
	}
};
extern void j_0000520e();
struct RubbleData3B40
{
	char m_pad00[0x3c];
	int m_minBurstDelay, m_maxBurstDelay, m_bigBurstFrequency;
	float m_rubbleRiseDamping, m_rubbleHeight, m_maxShudder;
};
class RubbleRiseStep002A3B40
{
  public:
	unsigned update();
	char m_pad00[0x18];
	unsigned m_nextRiseFrame, m_riseState;
	float m_riseVelocity, m_currentHeight, m_rubbleHeight;
	Coord3D m_risePosition;
	RubbleRiseUpdate *root()
	{
		return (RubbleRiseUpdate *)((char *)this - 16);
	}
};
unsigned RubbleRiseStep002A3B40::update()
{
	const RubbleData3B40 *data = *(RubbleData3B40 **)((char *)this - 12);
	Object *obj = *(Object **)((char *)this - 8);
	Drawable *drawable = obj->getDrawable();
	if (m_riseState == 0 && drawable && obj->flags.test(58))
	{
		root()->phase(Phase0, obj->getPosition());
		m_riseState = 1;
		Vector3 shudder(GetGameClientRandomValueReal(-data->m_maxShudder, data->m_maxShudder,
													 (char *)FILEPATH, 157),
						GetGameClientRandomValueReal(-data->m_maxShudder, data->m_maxShudder,
													 (char *)FILEPATH, 157),
						0);
		Matrix3D matrix = *obj->getDrawable()->getInstanceMatrix();
		matrix.Set_Translation(shudder);
		drawable->setInstanceMatrix(&matrix, true);
		m_riseState = 1;
		root()->phase(Phase2, obj->getPosition());
		unsigned frame = TheGameLogic->m_frame;
		m_nextRiseFrame =
			frame + GetGameLogicRandomValue(data->m_minBurstDelay, data->m_maxBurstDelay,
											(char *)FILEPATH, 171);
		m_riseVelocity =
			-TheWritableGlobalData->m_gravity * (1.0 - data->m_rubbleRiseDamping) * 20.0;
		m_rubbleHeight = TheTerrainLogic->height(obj->m_cachedPos.x, obj->m_cachedPos.y,
												 ((Gen_001BEC20 *)obj)->bfmeScale(), 0, true);
		m_currentHeight = 0;
		m_risePosition = *obj->getPosition();
	}
	if (m_riseState == 1 && drawable)
	{
		unsigned frame = TheGameLogic->m_frame;
		Vector3 shift(GetGameLogicRandomValueReal(-data->m_maxShudder, data->m_maxShudder,
												  (char *)FILEPATH, 196),
					  GetGameLogicRandomValueReal(-data->m_maxShudder, data->m_maxShudder,
												  (char *)FILEPATH, 196),
					  (m_currentHeight += m_riseVelocity));
		Coord3D position;
		position.x = shift.X + m_risePosition.x;
		position.y = shift.Y + m_risePosition.y;
		position.z = shift.Z + m_risePosition.z;
		obj->setPosition(&position);
		if (frame >= m_nextRiseFrame)
		{
			const Coord3D *burstPosition = obj->getPosition();
			if (GetGameLogicRandomValue(1, data->m_bigBurstFrequency, (char *)FILEPATH, 205) == 1)
				root()->phase(Phase2, burstPosition);
			else
				root()->phase(Phase1, burstPosition);
			m_nextRiseFrame += GetGameLogicRandomValue(data->m_minBurstDelay, data->m_maxBurstDelay,
													   (char *)FILEPATH, 214);
		}
		if (m_currentHeight >= m_rubbleHeight - m_risePosition.z)
		{
			Coord3D finalPosition = {m_risePosition.x, m_risePosition.y, m_rubbleHeight};
			obj->setPosition(&finalPosition);
			m_riseState = 2;
			root()->phase(Phase3, obj->getPosition());
			union {
				void (*f)();
				void (RubbleRiseUpdate::*m)();
			} call;
			call.f = j_0000520e;
			(root()->*call.m)();
			if (obj->flags.test(58))
			{
				obj->flags.reset(58);
				obj->notifyModelConditionChanged();
			}
			if (!obj->flags.test(59))
			{
				obj->flags.set(59);
				obj->notifyModelConditionChanged();
			}
			obj->setOrientation(obj->m_cachedAngle);
			obj->body->v28();
			Matrix3D matrix = *obj->getDrawable()->getInstanceMatrix();
			matrix.Set_Translation(Vector3(0, 0, 0));
			obj->getDrawable()->setInstanceMatrix(&matrix, true);
			return 0x3fffffff;
		}
	}
	return 1;
}
