// ?setRallyPoint@QueueProductionExitUpdate@@UAEXPBUCoord3D@@@Z
// partial score=0.9 date=2026-09-03
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX- /O2 /Ob2
// Retail 0x002D0CA0, 81 bytes: QueueProductionExitUpdate::setRallyPoint.
// ExitInterface this: object at [this-0x18], rally at +8, exists at +0x14.
// cdecl helper ILT 0x000159A6 (body 0x002D0A80). Non-null return: copy
// Coord3D from result+0x38. Wall: retail lea ecx,[esi+8] before je; MSVC 7.1
// folds dest into [esi+disp] (same non-steerable fold as lessons-archive).

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object;

void *bfmeQueryRallyOverride(Object *obj, const Coord3D *pos);

class QueueProductionExitUpdate
{
public:
	virtual void setRallyPoint(const Coord3D *pos);

private:
	unsigned char m_pad[4];
	Coord3D m_rallyPoint;
	bool m_rallyPointExists;
};

void QueueProductionExitUpdate::setRallyPoint(const Coord3D *pos)
{
	Object *obj = *reinterpret_cast<Object **>(
		reinterpret_cast<char *>(this) - 0x18);
	void *overrideHost = bfmeQueryRallyOverride(obj, pos);
	Coord3D *dst = &m_rallyPoint;
	if (overrideHost)
	{
		overrideHost = reinterpret_cast<char *>(overrideHost) + 0x38;
		dst->x = reinterpret_cast<const Coord3D *>(overrideHost)->x;
		dst->y = reinterpret_cast<const Coord3D *>(overrideHost)->y;
		m_rallyPointExists = true;
		dst->z = reinterpret_cast<const Coord3D *>(overrideHost)->z;
	}
	else
	{
		dst->x = pos->x;
		dst->y = pos->y;
		m_rallyPointExists = true;
		dst->z = pos->z;
	}
}
