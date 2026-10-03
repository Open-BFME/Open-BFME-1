// cl: /DNDEBUG /MD /EHsc
// Open-BFME6: 0x0022F260. Forwarder with two pass-through arguments: the
// Object lives at this-0x18, take its controlling player, take the player
// list at player+0x22C through the inline getter (which leaves it in eax),
// and tail-jump to the list method at 0x000688A5 through the thunk at
// 0x0002818C. The arguments are never read here; the jmp inherits this
// frame unchanged. Object/Player reuse the real names so the
// getControllingPlayer call resolves to its matched body.

struct BfmeList2F260
{
	char m_pad[1];
};

// Retail's call enters the 5-byte ILT at 0x0002818C
// (game/gen_small/thunks_019.cpp, ?j_0002818c@@YAXXZ), which tail-jumps to
// 0x000688A5. That ILT is the only definition of the address, so call it under
// its defined name with the callee's thiscall shape. VC7.1 reserves
// __thiscall in a free-function-pointer typedef, so use the established
// pointer-to-member cast idiom.
extern void j_0002818c();
struct BfmeList2F260CallView { void call(int a, int b); };
typedef void (BfmeList2F260CallView::*BfmeList2F260Call)(int a, int b);

class Player
{
public:
	char m_pad[0x22C];
	BfmeList2F260 *volatile m_list;
};

class Object
{
public:
	Player *getControllingPlayer() const;
};

class Gen_0022F260
{
public:
	void bfmeForward(int a, int b);
};

// ?bfmeForward@Gen_0022F260@@QAEXHH@Z
void Gen_0022F260::bfmeForward(int a, int b)
{
	Gen_0022F260 *self = this;
	Object *obj = *(Object **)((char *)self - 0x18);
	Player *player = obj->getControllingPlayer();
	BfmeList2F260 *list = player->m_list;
	union { void (*asFunction)(); BfmeList2F260Call asMember; } gCast;
	gCast.asFunction = j_0002818c;
	(reinterpret_cast<BfmeList2F260CallView *>(list)->*gCast.asMember)(a, b);
}