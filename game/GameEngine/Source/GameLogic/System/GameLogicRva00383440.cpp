// cl: /DNDEBUG /MD /EHsc
//
// GameLogic::rva00383440, retail 0x00383440 (50 bytes, RET 4 then INT3).
//
// Its only caller, Object::~Object (0x001D4010), loads ECX from TheGameLogic
// (0x012F0898) and pushes the Object before calling through ILT 0x0003B1B0, so the
// body is a GameLogic thiscall member with one argument that does not use `this`.
// The body is Zero Hour's GameLogic::sendObjectDestroyed statement for statement:
// return if TheGameClient is null, ask the Object for its drawable through
// ?getDrawable@Object@@UBEPAVDrawable@@XZ (vftable slot 10), hand a non-null one to
// the client's destroyDrawable (GameClient slot 24), then call the matched
// ?friend_bindToDrawable@Object@@QAEXPAVDrawable@@@Z with NULL. That name is
// already claimed by the 83-byte body at 0x0038D090, whose find-then-push_back
// shape is Zero Hour's destroyObject instead, so this one keeps its address until
// the two rows are reconciled. It was previously matched as the __stdcall
// ?bfmeGo1010B@@YGXPAVBfmeThing1010@@@Z, an ABI its caller's ECX load refutes.

class Drawable;

class Object
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09();
	virtual Drawable *getDrawable() const;		// slot 10
	void friend_bindToDrawable(Drawable *draw);
};

class GameClient
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void destroyDrawable(Drawable *draw);	// slot 24 (+0x60), ZH position
};
extern GameClient *TheGameClient;

class GameLogic
{
public:
	void rva00383440(Object *obj);
};

// ?rva00383440@GameLogic@@QAEXPAVObject@@@Z
void GameLogic::rva00383440(Object *obj)
{
	if (TheGameClient == 0)
		return;

	Drawable *draw = obj->getDrawable();
	if (draw)
		TheGameClient->destroyDrawable(draw);

	obj->friend_bindToDrawable(0);
}
