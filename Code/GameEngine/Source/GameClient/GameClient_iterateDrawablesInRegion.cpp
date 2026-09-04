// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: GameClient::iterateDrawablesInRegion at 0x0042E570 (186B).
// ZH twin in GameClient.cpp. m_drawableList at +0x10 (registerDrawable).
// Drawable::getNextDrawable is the inline m_nextDrawable load at +0x104.
// getPosition is the already-pinned Drawable ILT at 0x0004B12D.

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct Region3D
{
	Coord3D lo;
	Coord3D hi;
};

class Drawable
{
public:
	const Coord3D *getPosition() const;
	Drawable *getNextDrawable() const { return m_nextDrawable; }

private:
	unsigned char m_pad[0x104];
	Drawable *m_nextDrawable;
};

typedef void (*GameClientFuncPtr)(Drawable *draw, void *userData);

class GameClient
{
public:
	virtual void iterateDrawablesInRegion(Region3D *region, GameClientFuncPtr userFunc, void *userData);

private:
	unsigned char m_pad[0x0C];
	Drawable *m_drawableList;
};

// ?iterateDrawablesInRegion@GameClient@@UAEXPAURegion3D@@P6AXPAVDrawable@@PAX@Z2@Z
void GameClient::iterateDrawablesInRegion(Region3D *region, GameClientFuncPtr userFunc, void *userData)
{
	Drawable *draw;
	Drawable *nextDrawable;

	for (draw = m_drawableList; draw; draw = nextDrawable)
	{
		nextDrawable = draw->getNextDrawable();

		const Coord3D *p = draw->getPosition();
		float x = p->x;
		Coord3D pos;
		pos.y = p->y;
		pos.z = p->z;
		if (region == 0 ||
			(x >= region->lo.x && x <= region->hi.x &&
			 pos.y >= region->lo.y && pos.y <= region->hi.y &&
			 pos.z >= region->lo.z && pos.z <= region->hi.z))
		{
			(*userFunc)(draw, userData);
		}
	}
}
