// Six function-local statics, one per object.
//
// Each is a whole function whose only statement declares a static: the guard
// byte is tested, the guard dword is set, the constructor runs on the object
// and the compiler-generated teardown is handed to atexit. Testing a byte but
// setting a dword is what MSVC does with these guards; both addresses, and the
// teardown pushed to atexit, are relocations.
//
// The unwind frame with the state going -1 to 0 is the object becoming live
// across the atexit call. The six sit next to each other in retail and differ
// only in which constructor they call and which guard they own.


class BfmeStaticThingA
{
public:
	BfmeStaticThingA(void);				// retail 0x0002AEC8
	~BfmeStaticThingA(void);
};

class BfmeStaticThingB
{
public:
	BfmeStaticThingB(void);				// retail 0x0004912A
	~BfmeStaticThingB(void);
};

class BfmeStaticThingC
{
public:
	BfmeStaticThingC(void);				// retail 0x00039108
	~BfmeStaticThingC(void);
};

class BfmeStaticThingD
{
public:
	BfmeStaticThingD(void);				// retail 0x0003DB0E
	~BfmeStaticThingD(void);
};

class BfmeStaticThingE
{
public:
	BfmeStaticThingE(void);				// retail 0x000022D9
	~BfmeStaticThingE(void);
};

class BfmeStaticThingF
{
public:
	BfmeStaticThingF(void);				// retail 0x0000A533
	~BfmeStaticThingF(void);
};

// ?bfmeEnsure_005D9AE0@@YAXXZ
void bfmeEnsure_005D9AE0(void)
{
	static BfmeStaticThingA theBfmeThing;
}

// ?bfmeEnsure_005D9B50@@YAXXZ present-unmatched
void bfmeEnsure_005D9B50(void)
{
	static BfmeStaticThingB theBfmeThing;
}

// ?bfmeEnsure_005D9BC0@@YAXXZ present-unmatched
void bfmeEnsure_005D9BC0(void)
{
	static BfmeStaticThingC theBfmeThing;
}

// ?bfmeEnsure_005D9C30@@YAXXZ
void bfmeEnsure_005D9C30(void)
{
	static BfmeStaticThingD theBfmeThing;
}

// ?bfmeEnsure_005D9CA0@@YAXXZ
void bfmeEnsure_005D9CA0(void)
{
	static BfmeStaticThingE theBfmeThing;
}

// ?bfmeEnsure_005D9D10@@YAXXZ present-unmatched
void bfmeEnsure_005D9D10(void)
{
	static BfmeStaticThingF theBfmeThing;
}
