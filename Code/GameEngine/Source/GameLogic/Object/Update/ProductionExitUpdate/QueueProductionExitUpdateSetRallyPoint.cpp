// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX- /O2 /Ob1
// QueueProductionExitUpdate::setRallyPoint at 0x002D0CA0.
struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object;
Object *bfmeQueryRallyOverride(Object *obj, const Coord3D *pos);

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
	Object *overrideHost = bfmeQueryRallyOverride(obj, pos);
	if (overrideHost)
		m_rallyPoint = *reinterpret_cast<const Coord3D *>(
			reinterpret_cast<const char *>(overrideHost) + 0x38);
	else
		m_rallyPoint = *pos;
	m_rallyPointExists = true;
}
