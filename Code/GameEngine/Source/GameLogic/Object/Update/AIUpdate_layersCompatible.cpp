// cl: /DNDEBUG /MD /EHsc
// AIUpdate helper at 0x0026E8A0: object's layer vs the pathfinder cell
// layer at the given position. Fail only when one is a high layer (>=17)
// and the other is ground/invalid (<2).

class Object
{
public:
	int getLayer(void) const;
};

struct Coord3D;

class Pathfinder
{
public:
	int getLayer(const Coord3D *pos);
};

class AI
{
public:
	unsigned char m_pad[0x0C];
	Pathfinder *m_pathfinder;
};

extern "C" AI *_TheAIParseDefinitionAI;

class AIUpdateInterface
{
public:
	bool layersCompatible(const Coord3D *pos) const;

private:
	unsigned char m_pad[8];
	Object *m_object;
};

// ?layersCompatible@AIUpdateInterface@@QBE_NPBUCoord3D@@@Z
bool AIUpdateInterface::layersCompatible(const Coord3D *pos) const
{
	int objectLayer = m_object->getLayer();
	const Coord3D *p = pos;
	Pathfinder *pf = _TheAIParseDefinitionAI->m_pathfinder;
	int cellLayer = pf->getLayer(p);
	if (objectLayer >= 0x11)
	{
		if (cellLayer < 2)
			return false;
	}
	if (cellLayer >= 0x11)
	{
		if (objectLayer < 2)
			return false;
	}
	return true;
}
