// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail's five-byte void-decorated Player::iterateObjects ILT thunk at
// 0x0002F1CB forwards to the int-return body at 0x000CDCF0 (see
// PlayerObjectWalk.cpp). It lives in its own unit so that Player.obj no longer
// carries the lowest retail RVA of any row among the Generals-header TUs, which
// otherwise sorts Player.obj ahead of retail's StringBase providers in link
// order. The callers (Player.cpp and 27 others) reach it by this decoration.

class Object;

typedef void (*ObjectIterateFunc)(Object *, void *);

class PlayerIterateObjectsShim
{
public:
	void iterateObjects( ObjectIterateFunc func, void *userData ) const;
};

class Player
{
public:
	void iterateObjects( ObjectIterateFunc func, void *userData ) const;
};

// ?iterateObjects@Player@@QBEXP6AXPAVObject@@PAX@Z1@Z
void Player::iterateObjects( ObjectIterateFunc func, void *userData ) const
{
	((const PlayerIterateObjectsShim *)this)->iterateObjects(func, userData);
}
