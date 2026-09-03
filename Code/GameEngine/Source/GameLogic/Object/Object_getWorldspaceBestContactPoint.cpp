// Byte-matched BFME Object world-space contact-point query.

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	void set(float setX, float setY, float setZ)
	{
		x = setX;
		y = setY;
		z = setZ;
	}

	float x;
	float y;
	float z;
};

struct Vector3
{
	Vector3() {}
	Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
	float X;
	float Y;
	float Z;
};

struct Vector4
{
	float X;
	float Y;
	float Z;
	float W;
};

class Matrix3D
{
public:
	void Get_Orthogonal_Inverse(Matrix3D &inverse) const;

	static __forceinline void Transform_Vector(
		const Matrix3D &matrix, const Vector3 &input, Vector3 *output)
	{
		Vector3 temporary;
		Vector3 *value;

		if (output == &input)
		{
			temporary = input;
			value = &temporary;
		}
		else
		{
			value = (Vector3 *)&input;
		}

		output->X = matrix.Row[0].X * value->X
			+ matrix.Row[0].Y * value->Y
			+ matrix.Row[0].Z * value->Z
			+ matrix.Row[0].W;
		output->Y = matrix.Row[1].X * value->X
			+ matrix.Row[1].Y * value->Y
			+ matrix.Row[1].Z * value->Z
			+ matrix.Row[1].W;
		output->Z = matrix.Row[2].X * value->X
			+ matrix.Row[2].Y * value->Y
			+ matrix.Row[2].Z * value->Z
			+ matrix.Row[2].W;
	}

	union
	{
		float m_rows[3][4];
		Vector4 Row[3];
	};
};

__forceinline Vector3 operator *(const Matrix3D &matrix, const Vector3 &input)
{
	float firstY;
	const float firstZ = matrix.Row[2].X * input.X;
	return Vector3(
		matrix.Row[0].X * input.X + matrix.Row[0].Y * input.Y
			+ matrix.Row[0].Z * input.Z + matrix.Row[0].W,
		(firstY = matrix.Row[1].X * input.X,
			firstY + matrix.Row[1].Y * input.Y
				+ matrix.Row[1].Z * input.Z + matrix.Row[1].W),
		firstZ + matrix.Row[2].Y * input.Y
			+ matrix.Row[2].Z * input.Z + matrix.Row[2].W);
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	const Overridable *getFinalOverride() const;
	void *m_vtable;
	Overridable *m_nextOverride;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	const char *str() const
	{
		return m_data ? m_data + 8 : "";
	}

private:
	char *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate : public Overridable
{
public:
	const AsciiString &getName() const { return m_name; }

private:
	unsigned char m_unreconstructed_008[0x20 - 0x08];
	AsciiString m_name;
};

enum BodyDamageType
{
	BODY_PRISTINE,
	BODY_DAMAGED,
	BODY_REALLYDAMAGED,
	BODY_RUBBLE
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BodyModule.h
class BodyModuleInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual BodyDamageType getDamageState() const = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Geometry.h
class GeometryInfo
{
public:
	Bool getBestContactPoint(Coord3D *pointOut, const Coord3D *callerPos,
		const char *label, Int preference, Int seed, Bool skipCollideTest) const;
	float getMaxHeightAbovePosition() const;

private:
	unsigned char m_unreconstructed[0x24];
};

extern unsigned char g_contactPointDebug;
extern void *g_contactPointDebugSink;

extern "C" int __cdecl fprintf(void *sink, const char *format, ...);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Bool getWorldspaceBestContactPoint(Coord3D *pointOut,
		const Coord3D *callerPos, const char *label, Int preference,
		Int seed, Bool skipCollideTest) const;

private:
	const ThingTemplate *getTemplate() const
	{
		const ThingTemplate *thingTemplate = m_template;
		if (thingTemplate)
		{
			Overridable *nextOverride = thingTemplate->m_nextOverride;
			if (nextOverride)
				thingTemplate = (const ThingTemplate *)nextOverride->getFinalOverride();
		}
		return thingTemplate;
	}

	BodyModuleInterface *getBodyModule() const { return m_body; }

	void *m_vtable;
	const ThingTemplate *m_template;
	Matrix3D m_transform;
	unsigned char m_unreconstructed_038[0x74 - 0x38];
	UnsignedInt m_id;
	unsigned char m_unreconstructed_078[0xAC - 0x78];
	GeometryInfo m_geometryInfo;
	unsigned char m_unreconstructed_0D0[0x200 - 0xD0];
	BodyModuleInterface *m_body;
};

Bool Object::getWorldspaceBestContactPoint(Coord3D *pointOut,
	const Coord3D *callerPos, const char *label, Int preference,
	Int seed, Bool skipCollideTest) const
{
	if (g_contactPointDebug && g_contactPointDebugSink)
	{
		const char *skipCollideTestString;
		UnsignedInt id = (skipCollideTestString =
			skipCollideTest ? "TRUE" : "FALSE", m_id);
		const ThingTemplate *thingTemplate = getTemplate();
		fprintf(g_contactPointDebugSink,
			"      Object::getWorldspaceBestContactPoint() BEGIN: Object %s(%d), callerPos=%g,%g,%g, pref=%d, seed=%d, skipCollideTest=%s",
			thingTemplate->getName().str(), id,
			callerPos->x, callerPos->y, callerPos->z,
			preference, seed, skipCollideTestString);
	}

	Vector3 localCallerVector;
	localCallerVector.X = callerPos->x;
	localCallerVector.Y = callerPos->y;
	localCallerVector.Z = callerPos->z;
	const Matrix3D *transform = &m_transform;
	Matrix3D inverseTransform;
	transform->Get_Orthogonal_Inverse(inverseTransform);
	float localY = inverseTransform.m_rows[1][0] * localCallerVector.X
		+ inverseTransform.m_rows[1][1] * localCallerVector.Y
		+ inverseTransform.m_rows[1][2] * localCallerVector.Z
		+ inverseTransform.m_rows[1][3];
	float localZ = inverseTransform.m_rows[2][0] * localCallerVector.X
		+ inverseTransform.m_rows[2][1] * localCallerVector.Y
		+ inverseTransform.m_rows[2][2] * localCallerVector.Z
		+ inverseTransform.m_rows[2][3];
	float localX = inverseTransform.m_rows[0][0] * localCallerVector.X
		+ inverseTransform.m_rows[0][1] * localCallerVector.Y
		+ inverseTransform.m_rows[0][2] * localCallerVector.Z
		+ inverseTransform.m_rows[0][3];
	localCallerVector.X = localX;
	localCallerVector.Y = localY;
	localCallerVector.Z = localZ;

	Coord3D localPoint;
	if (!m_geometryInfo.getBestContactPoint(&localPoint,
		(const Coord3D *)&localCallerVector,
		label, preference, seed, skipCollideTest))
	{
		if (g_contactPointDebug && g_contactPointDebugSink)
			fprintf(g_contactPointDebugSink,
				"Geometry.getBestContactPoint failed, return FALSE");
		return false;
	}

	BodyModuleInterface *body = getBodyModule();
	if (body && body->getDamageState() == BODY_RUBBLE)
		localPoint.z = m_geometryInfo.getMaxHeightAbovePosition();

	Vector3 worldPoint = *transform * *(const Vector3 *)&localPoint;
	pointOut->set(worldPoint.X, worldPoint.Y, worldPoint.Z);

	if (g_contactPointDebug && g_contactPointDebugSink)
	{
		fprintf(g_contactPointDebugSink,
			"Geometry.getBestContactPoint succeeded, pointOut=%g,%g,%g, return TRUE",
			pointOut->x, pointOut->y, pointOut->z);
	}

	return true;
}
