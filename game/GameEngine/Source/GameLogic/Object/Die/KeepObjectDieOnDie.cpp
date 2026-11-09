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

class PlayerShim {};

class GameLogic
{
public:
	void destroyObject( Object *object );
};

class BfmeItemRY {};
class BfmeGateAMB {};

// Retail reaches each of these through its ILT thunk, which the ledger defines
// as ?j_XXXXXXXX@@YAXXZ (tools/callees.py 0x00255990: 0x12eea, 0x2852e,
// 0x357d8); call them by those names.
extern void j_00012eea();
extern void j_0002852e();
extern void j_000357d8();
typedef bool (PlayerShim::*PlayerShimByteCall)() const;
typedef void (BfmeItemRY::*BfmeItemRYCall)( void *one, void *two );
typedef bool (BfmeGateAMB::*BfmeGateAMBCall)( void *object, BfmeKeyAMB *key );
template<class T> T iltMemberCall( void (*p)() ) { union { void (*plain)(); T member; } call; call.plain = p; return call.member; }

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
		if( player != 0 && (((PlayerShim *)player)->*iltMemberCall<PlayerShimByteCall>( j_00012eea ))() )
		{
			TheGameLogic->destroyObject( object );
			return;
		}
	}

	(((BfmeItemRY *)*(Object **)( (char *)this - 8 ))->*iltMemberCall<BfmeItemRYCall>( j_0002852e ))(
		(void *)0x12e, (void *)0x19 );
	BfmeGateAMB *gate = *(BfmeGateAMB **)( (char *)this - 0xc );
	(((BfmeGateAMB *)( (char *)gate + 8 ))->*iltMemberCall<BfmeGateAMBCall>( j_000357d8 ))(
		*(Object **)( (char *)this - 8 ), (BfmeKeyAMB *)damageInfo );
}
