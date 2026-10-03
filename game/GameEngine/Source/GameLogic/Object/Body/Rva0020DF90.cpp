// cl: /O2
// Opaque secondary-subobject wrapper, RVA0020DF90, 38B through RET4 at20DFB3.
// ILT00034D65 reaches this body. Slot14 of this-10 has no proven method name.
// The final232B callee returns ST0 on every exit, and this wrapper forwards it.
// Reuse its witnessed HealingArmor001B0200 ABI and existing pin.
// Evidence: targets/game/reverse/identity_evidence/0020df90-float-return.md

class Rva0020DF90Head
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
};

class Object;
struct HealingArmor001B0200
{
 float adjust(void *arg, Object *object, int flag);
};

class Rva0020DF90Part
{
public:
	float invoke(void *arg);

};

float Rva0020DF90Part::invoke(void *arg)
{
	Rva0020DF90Head *head = (Rva0020DF90Head *)((char *)this - 0x10);
	head->slot14();
	Object *member = *(Object **)((char *)this - 8);
	void *a = arg;
	return ((HealingArmor001B0200 *)((char *)this + 0xC8))->adjust(a, member, 1);
}
