// cl: /DNDEBUG /MD /EHsc

struct BfmeRvaCoord3D
{
	float x;
	float y;
	float z;

	BfmeRvaCoord3D() {}
	~BfmeRvaCoord3D() {}
};

struct BfmeRva48D00Coord;

class Rva00248D00
{
public:
	void transform(const BfmeRva48D00Coord *, BfmeRva48D00Coord *);
};

class Rva00248DB0
{
public:
	BfmeRvaCoord3D *getPosition(void);
};

BfmeRvaCoord3D *Rva00248DB0::getPosition(void)
{
	static BfmeRvaCoord3D position;
	((Rva00248D00 *)((char *)this - 0x20))->transform(
		(BfmeRva48D00Coord *)(*(char **)((char *)this - 0x1c) + 0x190),
		(BfmeRva48D00Coord *)&position);
	return &position;
}

class Rva00248E10
{
public:
	BfmeRvaCoord3D *getPosition(void);
};

BfmeRvaCoord3D *Rva00248E10::getPosition(void)
{
	static BfmeRvaCoord3D position;
	((Rva00248D00 *)((char *)this - 0x20))->transform(
		(BfmeRva48D00Coord *)(*(char **)((char *)this - 0x1c) + 0x184),
		(BfmeRva48D00Coord *)&position);
	return &position;
}

class Rva00248E70
{
public:
	BfmeRvaCoord3D *getPosition(void);
};

BfmeRvaCoord3D *Rva00248E70::getPosition(void)
{
	static BfmeRvaCoord3D position;
	((Rva00248D00 *)((char *)this - 0x20))->transform(
		(BfmeRva48D00Coord *)(*(char **)((char *)this - 0x1c) + 0x19c),
		(BfmeRva48D00Coord *)&position);
	return &position;
}
