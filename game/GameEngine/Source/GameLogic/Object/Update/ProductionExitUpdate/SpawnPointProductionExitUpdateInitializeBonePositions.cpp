// cl: /DNDEBUG /MD /GX- /O2 /Ob2
// Reloc-named body of SpawnPointProductionExitUpdate::initializeBonePositions,
// incremental-link target of the 5-byte thunk at 0x0003B566.
// Retail 0x002D18F0, 1457 bytes: 10x Matrix3D on the stack, getObject at
// [this+8], getDrawable vslot +0x28, ehvec_ctor of three 16-byte rows at
// ILT 0x0000AE5C, then unrolled Make_Identity stores. m_bonesInitialized is
// [this+0x24]. BFME getPristineBonePositions takes six stack args.

enum { MAX_SPAWN_POINTS = 10 };

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct BfmeAsciiStringData
{
	unsigned short m_refCount;
	unsigned short m_numCharsAllocated;
	unsigned short m_len;
	unsigned short m_pad;
};

class AsciiString
{
public:
	const char *str(void) const { return m_data ? (const char *)(m_data + 1) : ""; }

private:
	BfmeAsciiStringData *m_data;
};

class SpawnBoneRow
{
public:
	SpawnBoneRow();
	void Set(float x, float y, float z, float w)
	{
		X = x;
		Y = y;
		Z = z;
		W = w;
	}

	float X;
	float Y;
	float Z;
	float W;
};

class Matrix3D
{
public:
	void Make_Identity(void)
	{
		Row[0].Set(1.0f, 0.0f, 0.0f, 0.0f);
		Row[1].Set(0.0f, 1.0f, 0.0f, 0.0f);
		Row[2].Set(0.0f, 0.0f, 1.0f, 0.0f);
	}

	float Get_X_Translation(void) const { return Row[0].W; }
	float Get_Y_Translation(void) const { return Row[1].W; }
	float Get_Z_Rotation(void) const;

	SpawnBoneRow Row[3];
};

class Drawable
{
public:
	int getPristineBonePositions(const char *boneNamePrefix, int startIndex,
		Coord3D *positions, Matrix3D *transforms, int maxBones, int extra) const;
};

class Object
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
	virtual Drawable *getDrawable(void);
	void convertBonePosToWorldPos(const Coord3D *bonePos, const Matrix3D *boneTransform,
		Coord3D *worldPos, Matrix3D *worldTransform) const;
};

class SpawnPointProductionExitUpdateModuleData
{
public:
	unsigned char m_pad[8];
	AsciiString m_spawnPointBoneNameData;
};

class SpawnPointInitializeBonePositionsShim
{
public:
	void init();

private:
	void *m_vptr;
	const SpawnPointProductionExitUpdateModuleData *m_moduleData;
	Object *m_object;
	unsigned char m_updatePad[0x18];
	bool m_bonesInitialized;
	int m_spawnPointCount;
	Coord3D m_worldCoordSpawnPoints[MAX_SPAWN_POINTS];
	float m_worldAngleSpawnPoints[MAX_SPAWN_POINTS];
};

void SpawnPointInitializeBonePositionsShim::init()
{
	Object *me = m_object;
	Drawable *myDrawable = me->getDrawable();

	if (myDrawable == 0)
		return;

	Matrix3D boneTransforms[MAX_SPAWN_POINTS];
	for (int matrixIndex = 0; matrixIndex < MAX_SPAWN_POINTS; matrixIndex++)
		boneTransforms[matrixIndex].Make_Identity();

	m_spawnPointCount = myDrawable->getPristineBonePositions(
		m_moduleData->m_spawnPointBoneNameData.str(), 1, 0, boneTransforms, MAX_SPAWN_POINTS, 0);

	for (matrixIndex = 0; matrixIndex < m_spawnPointCount; matrixIndex++)
	{
		Matrix3D *currentTransform = &(boneTransforms[matrixIndex]);
		me->convertBonePosToWorldPos(0, currentTransform, 0, currentTransform);

		m_worldCoordSpawnPoints[matrixIndex].x = currentTransform->Get_X_Translation();
		m_worldCoordSpawnPoints[matrixIndex].y = currentTransform->Get_Y_Translation();
		m_worldCoordSpawnPoints[matrixIndex].z = 0;

		m_worldAngleSpawnPoints[matrixIndex] = currentTransform->Get_Z_Rotation();
	}

	m_bonesInitialized = true;
}
