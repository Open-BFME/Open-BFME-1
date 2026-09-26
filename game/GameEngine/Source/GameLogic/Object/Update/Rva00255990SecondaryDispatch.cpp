// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// stlport
// Neutral ABI recovery for the 90-byte secondary-interface body at
// 0x00255990.  No named caller or vtable slot proves a public owner here.

class Player;
struct BfmeKeyAMB;

class Object
{
public:
	Player *getControllingPlayer() const;
};

class PlayerShim
{
public:
	bool unidentified_00012eea() const;
};

class GameLogic
{
public:
	void destroyObject( Object *object );
};

class BfmeItemRY
{
public:
	void bfmeDoRY( void *one, void *two );
};

class BfmeGateAMB
{
public:
	bool bfmeAskAMB( void *object, BfmeKeyAMB *key );
};

extern GameLogic *TheBfmeGameLogic;

class Rva00255990Owner
{
public:
	void run( void *argument );
};

void Rva00255990Owner::run( void *argument )
{
	Object *object = *(Object **)( (char *)this - 8 );
	if( object != 0 )
	{
		Player *player = object->getControllingPlayer();
		if( player != 0 && ((PlayerShim *)player)->unidentified_00012eea() )
		{
			TheBfmeGameLogic->destroyObject( object );
			return;
		}
	}

	((BfmeItemRY *)*(Object **)( (char *)this - 8 ))->bfmeDoRY(
		(void *)0x12e, (void *)0x19 );
	BfmeGateAMB *gate = *(BfmeGateAMB **)( (char *)this - 0xc );
	((BfmeGateAMB *)( (char *)gate + 8 ))->bfmeAskAMB(
		*(Object **)( (char *)this - 8 ), (BfmeKeyAMB *)argument );
}
