// ?getBestContactPoint@GeometryInfo@@QBE_NPAUCoord3D@@PBU2@PBDHH_N@Z
// partial score=0.55 date=2026-09-26
// cl: /O2 /Ob0 /G6

struct Coord3D
{
	float x, y, z;
};

class CRCParameterCheck;
extern bool g_bfmeDockingTraceActive;
extern CRCParameterCheck *TheCRCParameterCheck;
extern "C" void __cdecl bfmeRetailCritterDesyncLog(void *, const char *, ...);

class AsciiString
{
public:
	int bfmeCompare1294(const char *s) const;
	void *m_data;
};

struct Rva0087F590Contact
{
	Coord3D m_point;
	AsciiString m_label;
};

struct Rva0087F590Shape
{
	char pad00[0x10];
	float offsetX;
	float offsetY;
	float offsetZ;
	char pad1C[4];
	bool enabled;
	char pad21[3];
};

class BfmeSubYR
{
public:
	char bfmeDoYR(void *a, void *b, void *c, void *d, int e);
};

#define BFME_ONE (*(const float *)0x01075334)
#define BFME_TENTH (*(const float *)0x01075C70)
#define BFME_255TH (*(const float *)0x0107C64C)

class GeometryInfo
{
public:
	bool getBestContactPoint(Coord3D *out, const Coord3D *callerPos, const char *label,
		int pref, int seed, bool skipCollideTest) const;
	float getMaxHeightAbovePosition() const;

	char pad00[0x2C];
	Rva0087F590Shape *m_shapes;
	Rva0087F590Shape *m_shapesEnd;
	char pad34[4];
	Rva0087F590Contact *m_contacts38;
	Rva0087F590Contact *m_contactsEnd3C;
	char pad40[4];
	Coord3D m_coord44;
	Coord3D m_innermostContactPoint;
};

bool GeometryInfo::getBestContactPoint(Coord3D *out, const Coord3D *callerPos,
	const char *label, int pref, int seed, bool skipCollideTest) const
{
	if (g_bfmeDockingTraceActive && callerPos && TheCRCParameterCheck)
	{
		bfmeRetailCritterDesyncLog(TheCRCParameterCheck,
			"        GeometryInfo::getBestContactPoint, callerPos=%g,%g,%g, label=%s, pref=%d, seed=%d, skipCollideTest=%d, m_innermostContactPoint=%g,%g,%g",
			callerPos->x, callerPos->y, callerPos->z,
			label ? label : "NONE", pref, seed,
			skipCollideTest ? "TRUE" : "FALSE", m_innermostContactPoint.x, m_innermostContactPoint.y, m_innermostContactPoint.z);
	}
	*out = m_innermostContactPoint;
	switch (pref)
	{
	case 0:
	{
		if (!callerPos)
			return false;

		float bestDistance = 3.402823466e+38F;
		int bestIndex = m_contactsEnd3C - m_contacts38;
		int index = 0;
		for (const Rva0087F590Contact *p = m_contacts38; p != m_contactsEnd3C; ++p, ++index)
		{
			if (p->m_label.bfmeCompare1294(label ? label : "") != 0)
				continue;
			Coord3D candidate = p->m_point;
			if (getMaxHeightAbovePosition() < candidate.z)
				candidate.z = getMaxHeightAbovePosition();
			if (!skipCollideTest &&
				!((BfmeSubYR *)this)->bfmeDoYR((void *)0x0130E908, 0,
					(void *)0x0130E918, &candidate, 0))
				continue;
			float dx = candidate.x - callerPos->x;
			float dy = candidate.y - callerPos->y;
			float dz = candidate.z - callerPos->z;
			float dist = dx * dx + dy * dy + dz * dz;
			if (dist < bestDistance)
			{
				bestDistance = dist;
				bestIndex = index;
			}
		}
		if (bestIndex == m_contactsEnd3C - m_contacts38)
			return false;
		*out = m_contacts38[bestIndex].m_point;
		if (getMaxHeightAbovePosition() < out->z)
		{
			out->z = getMaxHeightAbovePosition();
			return true;
		}
		if (getMaxHeightAbovePosition() * BFME_TENTH > out->z)
			out->z = getMaxHeightAbovePosition() * BFME_TENTH;
		return true;	}
	case 1:
	{
		*out = m_coord44;
		if (getMaxHeightAbovePosition() < out->z)
			out->z = getMaxHeightAbovePosition();
		return true;
	}
	case 3:
	{
		int count = m_contactsEnd3C - m_contacts38;
		if (count >= 2)
		{
			int index = seed % (count - 1);
			const Rva0087F590Contact *first = &m_contacts38[index];
			const Rva0087F590Contact *second = first + 1;
			volatile float firstZ = first->m_point.z;
			Coord3D secondPoint = second->m_point;
			float fraction = ((seed >> 8) & 255) * BFME_255TH;
			Coord3D mixedPoint;
			mixedPoint.x = first->m_point.x * fraction + secondPoint.x * (BFME_ONE - fraction);
			mixedPoint.y = first->m_point.y * fraction + secondPoint.y * (BFME_ONE - fraction);
			mixedPoint.z = firstZ * fraction + secondPoint.z * (BFME_ONE - fraction);
			*out = mixedPoint;
		}
		if (getMaxHeightAbovePosition() < out->z)
			out->z = getMaxHeightAbovePosition();
		if (!skipCollideTest &&
			!((BfmeSubYR *)this)->bfmeDoYR((void *)0x0130E908, 0,
				(void *)0x0130E918, out, 0))
		{
			for (Rva0087F590Shape *shape = m_shapes; shape != m_shapesEnd; ++shape)
			{
				if (shape->enabled)
				{
					out->x = shape->offsetX;
					out->y = shape->offsetY;
					break;
				}
			}
		}
		if (getMaxHeightAbovePosition() < out->z)
		{
			out->z = getMaxHeightAbovePosition();
			return true;
		}
		if (getMaxHeightAbovePosition() * BFME_TENTH > out->z)
			out->z = getMaxHeightAbovePosition() * BFME_TENTH;
		return true;
	}
	default:
		return false;
	}
}
