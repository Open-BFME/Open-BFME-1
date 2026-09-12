// ?process@Rva0024CF00Owner@@QAEXPAX0@Z
// partial score=0.22 date=2026-09-12
// ?process@Rva0024CF00Owner@@QAEXPAX0@Z
// cl: /DNDEBUG /MD /EHsc

class Rva0024CF00Vector
{
public:
	Rva0024CF00Vector();
	float x, y, z, w;
};

class Rva0024CF00Triangle
{
public:
	__forceinline Rva0024CF00Triangle() {}
	Rva0024CF00Vector points[3];
};

class Rva0024CF00String;
class Rva0024CF00Owner
{
public:
	void process(void *subject, void *context);
	void makeKey(Rva0024CF00String *, void *);
	int query(void *, Rva0024CF00String *, Rva0024CF00Triangle *, int, int);
	int fallback(void *, int, Rva0024CF00Triangle *);
	char pad[8];
	void *system;
};

class Rva0024CF00String
{
public:
	Rva0024CF00String();
	~Rva0024CF00String();
	char bytes[0x0c];
};

void processRva0024CF00Candidates(Rva0024CF00Triangle *, void *, void *, void *, void *);

class Rva0024CF00Callback { public: virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35(); virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39(); virtual void apply(void *); };

class Rva0024CF00Physics { public: void randomForce(int); void apply(const Rva0024CF00Vector *); };
class Rva0024CF00Object {
public:
	void setMatrix(const Rva0024CF00Triangle *);
	void notify(void);
	void kill(int, int);
	char p0[8]; float scaleA; char pC[0x18-0x0c]; float scaleB;
	char p1c[0x74-0x1c]; int key;
	char p78[0x11c-0x78]; unsigned flags;
	char p120[0x208-0x120]; Rva0024CF00Physics *physics;
};

int GetGameLogicRandomValue(int, int, const char *, int);

extern "C" void b_000fbb40(void);
#pragma comment(linker, "/alternatename:??0Rva0024CF00Vector@@QAE@XZ=?b_000fbb40@@YAXXZ")

void Rva0024CF00Owner::process(void *subject, void *context)
{
	Rva0024CF00Triangle candidates[32];
	char scratch[0x88];
	Rva0024CF00String string;
	Rva0024CF00Object *object = (Rva0024CF00Object *)context;
	makeKey(&string, object);
	int accepted = query(system, &string, candidates, 0, 0x20);
	if (!accepted)
		accepted = fallback(system, 0, candidates);
	int chosen = accepted;
	if (chosen < 0)
		chosen = 0;
	if (subject)
		((Rva0024CF00Callback *)subject)->apply(object);
	processRva0024CF00Candidates(candidates, object, subject, &string, scratch);
	object->setMatrix(&candidates[chosen]);
	Rva0024CF00Physics *physics = object->physics;
	if (physics) {
		int random = GetGameLogicRandomValue(3, 8, (const char *)0x010B0710, 0x2fd);
		Rva0024CF00Vector force;
		force.x = object->scaleA * random;
		force.y = object->scaleB * random;
		force.z = object->scaleA;
		physics->randomForce(1);
		if (!(object->flags & 0x01000000)) {
			object->flags |= 0x01000000;
			object->notify();
		}
		physics->apply(&force);
	}
	object->kill(8, 0);
}
