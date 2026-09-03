// ?bfmeGet@Gen_0021AAD0@@QAEPAVPlayer@@XZ
// partial score=0.75 date=2026-09-03
// cl: /DNDEBUG /MD /EHsc
// Open-BFME6: 0x0021AAD0. Guarded player getter, 29 bytes: read the
// pointer at this+0x99C, answer null when it points to itself, otherwise
// take the Object at its pointee+8 and tail-jump to its controlling
// player. Object/Player reuse the real names so the getControllingPlayer
// call resolves to its matched body.

class Player
{
};

class Object
{
public:
	Player *getControllingPlayer() const;
};

class Gen_0021AAD0
{
public:
	Player *bfmeGet();
};

// ?bfmeGet@Gen_0021AAD0@@QAEPAVPlayer@@XZ
Player *Gen_0021AAD0::bfmeGet()
{
	void *p = *(void **)((char *)this + 0x99C);

	if (*(void **)p == p)
		return 0;

	Object *obj = *(Object **)((char *)*(void **)p + 8);
	return obj->getControllingPlayer();
}
