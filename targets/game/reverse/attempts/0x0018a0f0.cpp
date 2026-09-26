// ?canTargetOwner@@YA_NPAURva0018A0F0Holder@@@Z
// partial score=0.85 date=2026-09-06
class Object;
enum Relationship { RVA0018A0F0_ENEMIES = 0, RVA0018A0F0_NEUTRAL = 1, RVA0018A0F0_ALLIES = 2 };
class GameLogic { public: Object* bfmeFind1011(int id); };
extern GameLogic* TheBfmeGameLogic;
struct Rva0018A0F0Source {
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5();
	virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17();
	virtual int getTargetID();
};
class Object {
public:
	char m_pad[0x200];
	Rva0018A0F0Source* m_source;
	char m_pad2[0x344 - 0x204];
	unsigned char m_flags344;
	Relationship getRelationship(const Object* other) const;
	int queryAction(int a, Object* target, int b);
};
struct Rva0018A0F0Inner { char m_pad[0x10]; Object* m_object; };
struct Rva0018A0F0Holder { char m_pad[0x1c]; Rva0018A0F0Inner* m_inner; };
bool canTargetOwner(Rva0018A0F0Holder* holder)
{
	Object* self = holder->m_inner->m_object;
	Rva0018A0F0Source* source = self ? self->m_source : 0;
	if (self && source) {
		int id = source->getTargetID();
		if (id) {
			Object* target = TheBfmeGameLogic->bfmeFind1011(id);
			if (!target)
				return false;
			if (self->getRelationship(target) == RVA0018A0F0_ENEMIES && !(target->m_flags344 & 1)) {
				int r = self->queryAction(0, target, 2);
				if (r == 3)
					return true;
				if (r == 2)
					return true;
			}
		}
	}
	return false;
}
