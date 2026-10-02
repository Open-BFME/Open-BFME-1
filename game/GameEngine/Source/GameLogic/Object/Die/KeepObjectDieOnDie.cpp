// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// stlport
// KeepObjectDie::onDie at retail 0x00255990 (90 B): slot 0 of the one-slot
// DieModuleInterface table 0x010B315C, which KeepObjectDie's registered
// constructor 0x00255870 stores at +0x10; the only route is ILT 0x00045F3E,
// whose VA appears once in the image. Zero Hour's DieModuleInterface declares
// one virtual, onDie(const DamageInfo *).
// Evidence: targets/game/reverse/identity_evidence/diemodule-slot0-ondie.md

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

extern GameLogic *TheGameLogic;

class DamageInfo;

class KeepObjectDie
{
public:
	virtual void onDie( const DamageInfo *damageInfo );
};

void KeepObjectDie::onDie( const DamageInfo *damageInfo )
{
	Object *object = *(Object **)( (char *)this - 8 );
	if( object != 0 )
	{
		Player *player = object->getControllingPlayer();
		if( player != 0 && ((PlayerShim *)player)->unidentified_00012eea() )
		{
			TheGameLogic->destroyObject( object );
			return;
		}
	}

	((BfmeItemRY *)*(Object **)( (char *)this - 8 ))->bfmeDoRY(
		(void *)0x12e, (void *)0x19 );
	BfmeGateAMB *gate = *(BfmeGateAMB **)( (char *)this - 0xc );
	((BfmeGateAMB *)( (char *)gate + 8 ))->bfmeAskAMB(
		*(Object **)( (char *)this - 8 ), (BfmeKeyAMB *)damageInfo );
}
