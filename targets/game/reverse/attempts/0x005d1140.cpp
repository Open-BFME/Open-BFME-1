// cl: /O2 /Ob2 /EHsc
// partial score=0.17 date=2026-09-26

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct Matrix3DRow
{
	float x;
	float y;
	float z;
	float w;
};

struct Matrix3D
{
	Matrix3DRow Row[3];

	__forceinline Matrix3D &operator=(const Matrix3D &other)
	{
		Row[0].x = other.Row[0].x;
		Row[0].y = other.Row[0].y;
		Row[0].z = other.Row[0].z;
		Row[0].w = other.Row[0].w;
		Row[1].x = other.Row[1].x;
		Row[1].y = other.Row[1].y;
		Row[1].z = other.Row[1].z;
		Row[1].w = other.Row[1].w;
		Row[2].x = other.Row[2].x;
		Row[2].y = other.Row[2].y;
		Row[2].z = other.Row[2].z;
		Row[2].w = other.Row[2].w;
		return *this;
	}

	static __forceinline float submul(const Matrix3DRow &row, float x, float y, float z)
	{
		return row.x * x + row.y * y + row.z * z;
	}

	__forceinline void mul(const Matrix3D &left, const Matrix3D &right)
	{
		float x = right.Row[0].x;
		float y = right.Row[1].x;
		float z = right.Row[2].x;
		Row[0].x = submul(left.Row[0], x, y, z);
		Row[1].x = submul(left.Row[1], x, y, z);
		Row[2].x = submul(left.Row[2], x, y, z);

		x = right.Row[0].y;
		y = right.Row[1].y;
		z = right.Row[2].y;
		Row[0].y = submul(left.Row[0], x, y, z);
		Row[1].y = submul(left.Row[1], x, y, z);
		Row[2].y = submul(left.Row[2], x, y, z);

		x = right.Row[0].z;
		y = right.Row[1].z;
		z = right.Row[2].z;
		Row[0].z = submul(left.Row[0], x, y, z);
		Row[1].z = submul(left.Row[1], x, y, z);
		Row[2].z = submul(left.Row[2], x, y, z);

		x = right.Row[0].w;
		y = right.Row[1].w;
		z = right.Row[2].w;
		Row[0].w = submul(left.Row[0], x, y, z) + left.Row[0].w;
		Row[1].w = submul(left.Row[1], x, y, z) + left.Row[1].w;
		Row[2].w = submul(left.Row[2], x, y, z) + left.Row[2].w;
	}
};

class GlobalData
{
public:
	unsigned char m_pad00[0xA7F];
	Bool m_useFX;
	unsigned char m_padA80[0x11];
	Bool m_particleUpdateTiming;
};

class ClientFrameSubsystem
{
public:
	#define BFME_VIRTUAL(n) virtual void slot##n();
	BFME_VIRTUAL(00) BFME_VIRTUAL(01) BFME_VIRTUAL(02) BFME_VIRTUAL(03)
	BFME_VIRTUAL(04) BFME_VIRTUAL(05) BFME_VIRTUAL(06) BFME_VIRTUAL(07)
	BFME_VIRTUAL(08) BFME_VIRTUAL(09) BFME_VIRTUAL(10)
	virtual void *findDrawableByID(UnsignedInt id);
	BFME_VIRTUAL(12) BFME_VIRTUAL(13) BFME_VIRTUAL(14) BFME_VIRTUAL(15)
	BFME_VIRTUAL(16) BFME_VIRTUAL(17) BFME_VIRTUAL(18) BFME_VIRTUAL(19)
	BFME_VIRTUAL(20) BFME_VIRTUAL(21) BFME_VIRTUAL(22) BFME_VIRTUAL(23)
	BFME_VIRTUAL(24) BFME_VIRTUAL(25)
	virtual UnsignedInt getFrame();
	#undef BFME_VIRTUAL
};

class GameLogic;

class BfmeParticleObject
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
	virtual void *getDrawable();
};

class AsciiString
{
public:
	void *m_data;
};

class Rva005D1140ParticleSystem
{
public:
	Bool update(Int localPlayerIndex);

	unsigned char m_pad00[0x7C];
	Int m_priority;
	unsigned char m_pad80[0x20];
	void *m_particleList;
	UnsignedInt m_particleCount;
	unsigned char m_padAC[8];
	float m_updateTime;
	UnsignedInt m_attachedToDrawableID;
	UnsignedInt m_attachedToObjectID;
	AsciiString m_attachBoneName;
	Matrix3D m_localTransform;
	Matrix3D m_transform;
	UnsignedInt m_burstDelayLeft;
	UnsignedInt m_delayLeft;
	UnsignedInt m_startTimestamp;
	UnsignedInt m_systemLifetimeLeft;
	unsigned char m_pad130[0x18];
	Coord3D m_pos;
	Coord3D m_lastPos;
	unsigned char m_pad160[0x10];
	void *m_masterSystem;
	unsigned char m_pad174[0x2C];
	void *m_controlParticle;
	Bool m_isLocalIdentity;
	Bool m_isIdentity;
	Bool m_isForever;
	Bool m_isStopped;
	Bool m_isDestroyed;
	Bool m_isFirstPosition;
	Bool m_isSaveable;
	unsigned char m_pad1AB;
	Bool m_skipParentTransform;
	unsigned char m_pad1AD[3];
};

extern GlobalData *TheWritableGlobalData;
extern ClientFrameSubsystem *TheGameClientClientUpdate;
extern GameLogic *TheGameLogic;

extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(__int64 *value);
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceFrequency(__int64 *value);

extern void j_00002153();
extern void j_0000e525();
extern void j_00017512();
extern void j_0001f253();
extern void j_0002b81e();
extern void j_0002d5c4();
extern void j_0002f766();
extern void j_0003e59f();
extern void j_0004484b();
extern void j_00044ebd();

// ?update@Rva005D1140ParticleSystem@@QAE_NH@Z
Bool Rva005D1140ParticleSystem::update(Int localPlayerIndex)
{
	__int64 frequency;
	__int64 start;
	Bool isShrouded;
	Bool noDrawable;
	Bool transformSet;
	Matrix3D boneTransform;
	Matrix3D *parentXfrm;
	void *drawable;

	m_updateTime = 0.0f;
	if (*reinterpret_cast<const Bool *>(reinterpret_cast<const char *>(TheWritableGlobalData) + 0xA91))
	{
		QueryPerformanceFrequency(&frequency);
		QueryPerformanceCounter(&start);
	}

	if (TheWritableGlobalData->m_useFX == false)
		return false;

	if (m_delayLeft != 0)
	{
		--m_delayLeft;
		if (m_delayLeft == 0)
			m_startTimestamp = TheGameClientClientUpdate->getFrame();
		return true;
	}

	if (m_masterSystem == 0)
	{
		isShrouded = false;
		noDrawable = false;
		transformSet = false;
		parentXfrm = 0;
		drawable = 0;
		if (m_attachedToDrawableID != 0)
		{
			drawable = TheGameClientClientUpdate->findDrawableByID(m_attachedToDrawableID);
			if (drawable == 0)
			{
				m_attachedToDrawableID = 0;
				((void (__fastcall *)(void *))j_0000e525)(this);
			}
			else
			{
				if (*reinterpret_cast<const Bool *>(reinterpret_cast<const char *>(drawable) + 0x3B1) == false)
					noDrawable = true;
				if (*reinterpret_cast<const Bool *>(reinterpret_cast<const char *>(drawable) + 0x3B0) != false)
					isShrouded = true;
				parentXfrm = reinterpret_cast<Matrix3D *>(((Int (__fastcall *)(void *))j_00017512)(drawable));
				m_lastPos = m_pos;
				m_pos.x = parentXfrm->Row[0].w;
				m_pos.y = parentXfrm->Row[1].w;
				m_pos.z = parentXfrm->Row[2].w;
			}
		}
		else if (m_attachedToObjectID != 0)
		{
			BfmeParticleObject *object = reinterpret_cast<BfmeParticleObject *>(
				((void * (__fastcall *)(void *, void *, Int))j_0001f253)(TheGameLogic, 0, m_attachedToObjectID));
			if (object == 0)
			{
				m_attachedToObjectID = 0;
				((void (__fastcall *)(void *))j_0000e525)(this);
			}
			else
			{
				isShrouded = ((Int (__fastcall *)(void *, void *, Int))j_0002b81e)(object, 0, localPlayerIndex) >= 3;
				drawable = object->getDrawable();
				if (drawable != 0)
				{
					if (*reinterpret_cast<const Bool *>(reinterpret_cast<const char *>(drawable) + 0x3B1) == false)
						noDrawable = true;
					if (*reinterpret_cast<const Bool *>(reinterpret_cast<const char *>(drawable) + 0x3B0) != false)
						isShrouded = true;
					parentXfrm = reinterpret_cast<Matrix3D *>(((Int (__fastcall *)(void *))j_00017512)(drawable));
				}
				else
					parentXfrm = reinterpret_cast<Matrix3D *>(reinterpret_cast<char *>(object) + 8);
				m_lastPos = m_pos;
				m_pos.x = parentXfrm->Row[0].w;
				m_pos.y = parentXfrm->Row[1].w;
				m_pos.z = parentXfrm->Row[2].w;
			}
		}

		if (drawable != 0 && ((Bool (__fastcall *)(void *))j_0002d5c4)(&m_attachBoneName))
			{
				const char *boneName = m_attachBoneName.m_data == 0
					? reinterpret_cast<const char *>(0x0107388B)
					: reinterpret_cast<const char *>(m_attachBoneName.m_data) + 8;
				if (((Int (__fastcall *)(void *, void *, const char *, Int, Coord3D *, Matrix3D *, Int))j_0002f766)(
					drawable, 0, boneName, 0, 0, &boneTransform, 1) != 0)
					((void (__fastcall *)(void *, void *, const Matrix3D *))j_0004484b)(this, 0, &boneTransform);
			}

		if (m_skipParentTransform)
		{
			m_transform = m_localTransform;
			m_isIdentity = false;
			transformSet = true;
		}
		else if (m_isLocalIdentity == false)
		{
			if (parentXfrm != 0)
				m_transform.mul(*parentXfrm, m_localTransform);
			else
				m_transform = m_localTransform;
			m_isIdentity = false;
			transformSet = true;
		}
		else if (parentXfrm != 0)
		{
			m_transform = *parentXfrm;
			m_isIdentity = false;
			transformSet = true;
		}
		if (transformSet == false)
			m_isIdentity = true;

	if (m_controlParticle != 0)
	{
		Coord3D *controlPosition = reinterpret_cast<Coord3D *>(reinterpret_cast<char *>(m_controlParticle) + 0x1C);
		m_transform.Row[0].w = controlPosition->x;
		m_transform.Row[1].w = controlPosition->y;
		m_transform.Row[2].w = controlPosition->z;
		m_lastPos = m_pos;
		m_pos = *controlPosition;
		m_isIdentity = false;
	}

	if (m_isDestroyed == false && (m_isForever || m_systemLifetimeLeft != 0) &&
		isShrouded == false && m_isStopped == false && noDrawable == false)
		((void (__fastcall *)(void *, void *, Coord3D *, Int, Bool, Matrix3D *))j_0003e59f)(
			this, 0, &m_pos, m_priority, m_isIdentity, &m_transform);
	}

	((void (__fastcall *)(void *))j_00044ebd)(reinterpret_cast<char *>(this) + 0x1B0);
	Bool result = ((Bool (__fastcall *)(void *))j_00002153)(this);
	if (*reinterpret_cast<const Bool *>(reinterpret_cast<const char *>(TheWritableGlobalData) + 0xA91))
	{
		__int64 elapsed;
		QueryPerformanceCounter(&elapsed);
		elapsed -= start;
		m_updateTime = (float)elapsed * *reinterpret_cast<const float *>(0x01075C68) / (float)frequency;
	}
	return result;
}
