// cl: /O2 /MD /DNDEBUG
// Retail 00249F50. Opaque secondary receiver and layout views.
// Evidence: identity_evidence/00249f50-list-force.md.
// The separate nontrivial coordinate copy is required by the retail x87 stores.
extern int GetGameLogicRandomValue(int,int,char *,int);
extern void j_0002a284();
struct Rva00249F50Coord {
	float x,y,z;
	Rva00249F50Coord(){
	}
	Rva00249F50Coord(const Rva00249F50Coord &o):x(o.x),y(o.y),z(o.z){
	}
}
;
struct Rva00249F50Physics {
	void apply(const Rva00249F50Coord *p) {
		typedef void (Rva00249F50Physics::*Fn)(const Rva00249F50Coord *);
		union{
			void(*p)();
			Fn f;
		}
		u;
		u.p=j_0002a284;
		(this->*u.f)(p);
	}
}
;
struct Rva00249F50Object {
	char pad[8];
	float x;
	char padC[12];
	float y;
	char pad1c[0x1ec];
	Rva00249F50Physics *physics;
}
;
struct Rva00249F50Node {
	Rva00249F50Node *next,*prev;
	void *value;
}
;
class Rva00249F50 {
	public:
#define S(n) virtual void slot##n();
	S(0) S(1) S(2) S(3) S(4) S(5) S(6) S(7) S(8) S(9) S(10) S(11) S(12) S(13) S(14) S(15) S(16) S(17) S(18) S(19) S(20) S(21) S(22) S(23) S(24) S(25) S(26) S(27) S(28) S(29) S(30) S(31) S(32) S(33) S(34) S(35)
#undef S
	virtual void consume(void *,void *);
	char pad[0xc8];
	Rva00249F50Node *sentinel;
	void body(void *);
}
;
void Rva00249F50::body(void *) {
	while(sentinel->next!=sentinel) {
		void *entry=sentinel->next->value;
		if(entry) {
			consume(entry,0);
			Rva00249F50Object *object=*(Rva00249F50Object **)((char*)this-0x18);
			Rva00249F50Physics *physics=object->physics;
			if(physics) {
				Rva00249F50Coord force;
				force.x=object->x;
				force.y=object->y;
				force.z=1.0f;
				float scale=(float)GetGameLogicRandomValue(3,8,"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\HordeSiegeEngineContain.cpp",782);
				force.x*=scale;
				force.y*=scale;
				force.z*=scale;
				Rva00249F50Coord copy(force);
				physics->apply(&copy);
			}
		}
	}
}
