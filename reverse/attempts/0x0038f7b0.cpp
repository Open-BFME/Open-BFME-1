// ?d_0038f7b0@@YAXXZ
// partial score=0.3 date=2026-09-17
// cl: /O2 /DNDEBUG /MD /EHsc
//
// Retail 0x0038F7B0.  The anonymous body is reached from GameLogic::startNewGame
// through a four-argument ILT call, but no source declaration proves its private
// owner.  Keep the address in the class name until a vtable, symbol, or matched
// caller proves more.
//
// The raw offsets below are deliberately address-derived.  They are the fields
// witnessed by the retail body: the AI template-name block, the MapObject link
// and flags, the map-object location/angle area, and the ThingTemplate kind bits.

typedef bool Bool;
typedef int Int;

struct Rva0038F7B0Coord3D
{
	float x;
	float y;
	float z;
};

class Rva0038F7B0Registry
{
};

class Rva0038F7B0Recorder
{
};

class Rva0038F7B0FinalOverride
{
};

class Rva0038F7B0MapObject
{
};

class Rva0038F7B0Players
{
};

class Rva0038F7B0Thing
{
};

class Rva0038F7B0Terrain
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual float getGroundHeight(float x, float y) = 0;
	virtual Int getLayerForDestination(Rva0038F7B0Thing *object,
		const Rva0038F7B0Coord3D *position) = 0;
};

extern void j_000019f1();
extern void j_000032d8();
extern void j_000050c9();
extern void j_000076cb();
extern void j_00009304();
extern void j_0000991c();
extern void j_00012814();
extern void j_0001325a();
extern void j_00015d7a();
extern void j_00017a12();
extern void j_000184b2();
extern void j_0001be82();
extern void j_0001c549();
extern void j_0001c675();
extern void j_000267c9();
extern void j_00028560();
extern void j_0003251f();
extern void j_00035e0e();
extern void j_000361ce();
extern void j_000364ad();
extern void j_00037f83();
extern void j_000399a5();
extern void j_0003a1a7();
extern void j_0003a855();
extern void j_00043a1d();
extern void j_000441b1();
extern void j_0004494a();
extern void j_0004a7a5();
extern void Rva0090F050();
extern void Rva009EBAC0(Int);

static void *readGlobal(unsigned int address)
{
	return *(void **)address;
}

static unsigned char readByte(const void *object, unsigned int offset)
{
	return *((const unsigned char *)object + offset);
}

static unsigned int readDword(const void *object, unsigned int offset)
{
	return *((const unsigned int *)((const unsigned char *)object + offset));
}

static void writeDword(void *object, unsigned int offset, unsigned int value)
{
	*((unsigned int *)((unsigned char *)object + offset)) = value;
}

static void *findTemplate(Rva0038F7B0Registry *registry, void *name)
{
	union
	{
		void (*raw)(void);
		void *(Rva0038F7B0Registry::*member)(void *);
	} call;
	call.raw = j_00028560;
	return (registry->*call.member)(name);
}

static Bool recorderIsMultiplayer(Rva0038F7B0Recorder *recorder)
{
	union
	{
		void (*raw)(void);
		Bool (Rva0038F7B0Recorder::*member)();
	} call;
	call.raw = j_0004a7a5;
	return (recorder->*call.member)();
}

static void *resolveFinalOverride(Rva0038F7B0FinalOverride *object)
{
	union
	{
		void (*raw)(void);
		void *(Rva0038F7B0FinalOverride::*member)();
	} call;
	call.raw = j_000267c9;
	return (object->*call.member)();
}

static void mapObjectNameChange(Rva0038F7B0MapObject *object)
{
	union
	{
		void (*raw)(void);
		void (*member)(Rva0038F7B0MapObject *);
	} call;
	call.raw = j_0001c549;
	call.member(object);
}

static void *mapObjectThing(Rva0038F7B0MapObject *object)
{
	union
	{
		void (*raw)(void);
		void *(Rva0038F7B0MapObject::*member)();
	} call;
	call.raw = j_00012814;
	return (object->*call.member)();
}

static void *mapObjectLocation(Rva0038F7B0MapObject *object)
{
	union
	{
		void (*raw)(void);
		void *(Rva0038F7B0MapObject::*member)();
	} call;
	call.raw = j_0001325a;
	return (object->*call.member)();
}

static Bool thingIsKindOf(Rva0038F7B0Thing *thing, Int kind)
{
	union
	{
		void (*raw)(void);
		Bool (Rva0038F7B0Thing::*member)(Int);
	} call;
	call.raw = j_000032d8;
	return (thing->*call.member)(kind);
}

static void *newObject(Rva0038F7B0Registry *registry, void *thing,
	void *team)
{
	union
	{
		void (*raw)(void);
		void *(Rva0038F7B0Registry::*member)(void *, void *);
	} call;
	call.raw = j_0004494a;
	return (registry->*call.member)(thing, team);
}

static void setOrientation(Rva0038F7B0Thing *object, float angle)
{
	union
	{
		void (*raw)(void);
		void (Rva0038F7B0Thing::*member)(float);
	} call;
	call.raw = j_000399a5;
	(object->*call.member)(angle);
}

static void setPosition(Rva0038F7B0Thing *object,
	const Rva0038F7B0Coord3D *position)
{
	union
	{
		void (*raw)(void);
		void (Rva0038F7B0Thing::*member)(const Rva0038F7B0Coord3D *);
	} call;
	call.raw = j_000019f1;
	(object->*call.member)(position);
}

static void updateFromMapObject(Rva0038F7B0Thing *object,
	Rva0038F7B0MapObject *mapObject)
{
	union
	{
		void (*raw)(void);
		void (Rva0038F7B0Thing::*member)(Rva0038F7B0MapObject *);
	} call;
	call.raw = j_0003a1a7;
	(object->*call.member)(mapObject);
}

static void addToPathfindMap(Rva0038F7B0Thing *object, void *pathfinder)
{
	union
	{
		void (*raw)(void);
		void (Rva0038F7B0Thing::*member)(void *);
	} call;
	call.raw = j_000441b1;
	(object->*call.member)(pathfinder);
}

static void setLayer(Rva0038F7B0Thing *object, Int layer)
{
	union
	{
		void (*raw)(void);
		void (Rva0038F7B0Thing::*member)(Int);
	} call;
	call.raw = j_00035e0e;
	(object->*call.member)(layer);
}

class Rva0038F7B0
{
public:
	void process(void *arg0, void *arg1, void *arg2, void *arg3);
};

void Rva0038F7B0::process(void *arg0, void *arg1, void *arg2, void *arg3)
{
	(void)arg0;
	(void)arg1;
	(void)arg2;
	(void)arg3;

	void *ai = readGlobal(0x012EF214);
	Rva0038F7B0Registry *registry =
		(Rva0038F7B0Registry *)readGlobal(0x012EF1D8);
	void *aiConfig = ai ? *(void **)((unsigned char *)ai + 0x14) : 0;
	void *templateA = aiConfig ? findTemplate(registry,
		(unsigned char *)aiConfig + 0xD8) : 0;
	void *templateB = aiConfig ? findTemplate(registry,
		(unsigned char *)aiConfig + 0xDC) : 0;
	void *templateC = aiConfig ? findTemplate(registry,
		(unsigned char *)aiConfig + 0xE0) : 0;

	Bool useTrees = aiConfig && readByte(aiConfig, 0xD4) != 0;
	Rva0038F7B0Recorder *recorder =
		(Rva0038F7B0Recorder *)readGlobal(0x012ED62C);
	if (recorder && recorderIsMultiplayer(recorder))
		useTrees = true;

	// The three AI templates are only used as final-override anchors in the
	// retail body.  Preserve that ordering without assigning them guessed names.
	if (templateA)
		templateA = resolveFinalOverride((Rva0038F7B0FinalOverride *)templateA);
	if (templateB)
		templateB = resolveFinalOverride((Rva0038F7B0FinalOverride *)templateB);
	if (templateC)
		templateC = resolveFinalOverride((Rva0038F7B0FinalOverride *)templateC);

	Rva0038F7B0Terrain *terrain =
		(Rva0038F7B0Terrain *)readGlobal(0x012EF4CC);
	void *pathfinder = aiConfig ? *(void **)((unsigned char *)ai + 0x0C) : 0;
	void *team = 0;
	Rva0038F7B0Players *players =
		(Rva0038F7B0Players *)readGlobal(0x012ED748);
	if (players)
	{
		union
		{
			void (*raw)(void);
			void *(Rva0038F7B0Players::*member)();
		} call;
		call.raw = j_0001be82;
		team = (players->*call.member)();
	}

	Rva0038F7B0MapObject *mapObject =
		(Rva0038F7B0MapObject *)readGlobal(0x012ED5DC);
	while (mapObject)
	{
		if ((readDword(mapObject, 0x20) & 0x36) != 0)
		{
			mapObject = (Rva0038F7B0MapObject *)readDword(mapObject, 4);
			continue;
		}

		mapObjectNameChange(mapObject);
		Rva0038F7B0Thing *thing =
			(Rva0038F7B0Thing *)mapObjectThing(mapObject);
		if (thing && !thingIsKindOf(thing, 0x5E))
		{
			void *locationData = mapObjectLocation(mapObject);
			if (locationData && terrain)
			{
				Rva0038F7B0Coord3D position =
					*(Rva0038F7B0Coord3D *)locationData;
				position.z += terrain->getGroundHeight(position.x, position.y);

				void *object = newObject(registry, thing, team);
				if (object)
				{
					float angle = *(float *)((unsigned char *)mapObject + 0x1C);
					setOrientation((Rva0038F7B0Thing *)object, angle);
					setPosition((Rva0038F7B0Thing *)object, &position);
					updateFromMapObject((Rva0038F7B0Thing *)object, mapObject);
					setLayer((Rva0038F7B0Thing *)object,
						terrain->getLayerForDestination(
							(Rva0038F7B0Thing *)object, &position));
					if (useTrees || !thingIsKindOf(thing, 0x5D))
						addToPathfindMap((Rva0038F7B0Thing *)object, pathfinder);
				}
			}
		}

		mapObject = (Rva0038F7B0MapObject *)readDword(mapObject, 4);
	}

	Rva0090F050();
}
