// cl: /DNDEBUG /MD

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

struct BfmeVector3
{
	float x;
	float y;
	float z;
};

class Matrix3D
{
public:
	float m[12];

	__forceinline Matrix3D &operator=(const Matrix3D &other)
	{
		m[0] = other.m[0];
		m[1] = other.m[1];
		m[2] = other.m[2];
		m[3] = other.m[3];
		m[4] = other.m[4];
		m[5] = other.m[5];
		m[6] = other.m[6];
		m[7] = other.m[7];
		m[8] = other.m[8];
		m[9] = other.m[9];
		m[10] = other.m[10];
		m[11] = other.m[11];
		return *this;
	}
};

class ModelConditionFlags
{
public:
	unsigned int m_bits[10];

	void clearAndSet(const ModelConditionFlags &clear,
		const ModelConditionFlags &set);
};

class ObjectDrawInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18();
	virtual void replaceModelConditionState(const ModelConditionFlags &,
		bool, unsigned int);
};

class DrawModule
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26();
	virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34();
	virtual void slot35(); virtual void slot36(); virtual void slot37();
	virtual void slot38();
	virtual ObjectDrawInterface *getObjectDrawInterface();
};

class BfmeVec3EP
{
public:
	BfmeVec3EP &operator=(const BfmeVec3EP &other)
	{
		m_bfmeX = other.m_bfmeX;
		m_bfmeY = other.m_bfmeY;
		m_bfmeZ = other.m_bfmeZ;
		return *this;
	}

	float m_bfmeX;
	float m_bfmeY;
	float m_bfmeZ;
};

class Gen_001C1D60
{
public:
	unsigned char m_unreconstructed_000[8];
	Matrix3D m_transform;
	Coord3D m_position;
	unsigned char m_unreconstructed_03C[0x0F4];
	Matrix3D m_alternateTransform;
	unsigned char m_unreconstructed_168[4];
	Coord3D m_alternatePosition;
	Coord3D m_rowPosition;
	bool m_useAlternateTransform;
	bool m_useAlternatePosition;
	bool m_useAlternateRow;
};

extern void j_0003b9fd(void);

typedef void (Gen_001C1D60::*BfmeGetRowThunk)(Coord3D *);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameEngine.h
class GameEngine
{
public:
	unsigned char m_unreconstructed_000[0x38];
	float m_interpolationFactor;
};

extern GameEngine *TheGameEngine;

extern BfmeVector3 *__stdcall bfmeVec3Hermite(
	BfmeVector3 *result,
	const Coord3D *position0,
	const Coord3D *tangent0,
	const Coord3D *position1,
	const Coord3D *tangent1,
	float factor);

class BFMERopeDrawableGetPositionShim
{
private:
	unsigned char m_unreconstructed_000[8];
	Matrix3D m_transform;
	Coord3D m_basePosition;
	unsigned char m_unreconstructed_044[0x0FC - 0x044];
	Gen_001C1D60 *m_object;
	unsigned char m_unreconstructed_100[0x150 - 0x100];
	DrawModule **m_drawModules;
	unsigned char m_unreconstructed_154[0x200 - 0x154];
	Matrix3D m_unreconstructed_200;
	Coord3D m_interpolatedPosition;
	int m_unreconstructed_23C;
	unsigned char m_unreconstructed_240[0x250 - 0x240];
	ModelConditionFlags m_conditionState;
	ModelConditionFlags m_clearMask;
	ModelConditionFlags m_setMask;
	unsigned char m_unreconstructed_2C8[0x31C - 0x2C8];
	Matrix3D m_transformCache;
	Matrix3D m_currentTransform;
	Coord3D m_position0;
	Coord3D m_tangent0;
	Coord3D m_position1;
	Coord3D m_tangent1;
	unsigned char m_unreconstructed_3AC[0x3B3 - 0x3AC];
	bool m_isModelDirty;
	bool m_interpolationReady;

	void bfmeRebuild(int force);

public:
	const Coord3D *get() const;
};

const Coord3D *BFMERopeDrawableGetPositionShim::get() const
{
	if (!m_object)
		return &m_basePosition;

	BFMERopeDrawableGetPositionShim *self =
		const_cast<BFMERopeDrawableGetPositionShim *>(this);
	if (!m_interpolationReady)
		self->bfmeRebuild(0);

	Coord3D interpolated;
	BfmeVector3 result;
	bfmeVec3Hermite(
		&result,
		&m_position0,
		&m_tangent0,
		&m_position1,
		&m_tangent1,
		TheGameEngine->m_interpolationFactor);

	interpolated.x = result.x;
	interpolated.y = result.y;
	interpolated.z = result.z;
	self->m_interpolatedPosition = interpolated;
	return &m_interpolatedPosition;
}

// ?bfmeRebuild@BFMERopeDrawableGetPositionShim@@AAEXH@Z
void BFMERopeDrawableGetPositionShim::bfmeRebuild(int force)
{
	Gen_001C1D60 *object = m_object;

	m_interpolationReady = true;
	m_unreconstructed_23C = -1;
	if (object == 0)
	{
		m_currentTransform = m_transform;
		m_transformCache = m_currentTransform;
		m_tangent1 = m_basePosition;
		m_position1 = m_basePosition;
		*reinterpret_cast<Coord3D *>(&m_tangent0) = m_basePosition;
		m_position0 = m_basePosition;
		return;
	}

	if ((unsigned char)force)
	{
		m_transformCache = object->m_transform;
		m_transformCache = object->m_transform;
		m_currentTransform = object->m_transform;
		m_position0 = object->m_position;
		*reinterpret_cast<Coord3D *>(&m_tangent0) = object->m_position;
		m_unreconstructed_200 = object->m_transform;
		m_interpolatedPosition = object->m_position;

		if (m_isModelDirty)
		{
			m_conditionState.clearAndSet(m_clearMask, m_setMask);
			for (DrawModule **module = m_drawModules; *module != 0; ++module)
			{
				DrawModule *drawModule = *module;
				ObjectDrawInterface *drawInterface =
					drawModule->getObjectDrawInterface();
				if (drawInterface != 0)
					drawInterface->replaceModelConditionState(
						m_conditionState, false, 0);
			}
			m_isModelDirty = false;
		}
		goto finish;
	}

	const Matrix3D *transform = object->m_useAlternateTransform
		? &object->m_alternateTransform : &object->m_transform;
	m_transformCache = *transform;
	m_currentTransform = object->m_transform;

	const Coord3D *position = object->m_useAlternatePosition
		? &object->m_alternatePosition : &object->m_position;
	m_position0 = *position;
	union BfmeThunkCast
	{
		void (*freeFunction)(void);
		BfmeGetRowThunk memberFunction;
	};
	BfmeThunkCast thunk;
	thunk.freeFunction = &j_0003b9fd;
	(object->*thunk.memberFunction)(&m_tangent0);

finish:
	m_position1 = object->m_position;
	m_tangent1 = object->m_useAlternateRow
		? object->m_rowPosition : object->m_position;
}
