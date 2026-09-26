// cl: /DNDEBUG /MD /EHsc

struct BfmeRvaCoord3D
{
	float x;
	float y;
	float z;

	BfmeRvaCoord3D() {}
	~BfmeRvaCoord3D() {}
};

class BfmeRvaTransform
{
public:
	void transform(const BfmeRvaCoord3D *, BfmeRvaCoord3D *);
};

class Rva00248DB0
{
public:
	BfmeRvaCoord3D *getPosition(void);
};

BfmeRvaCoord3D *Rva00248DB0::getPosition(void)
{
	static BfmeRvaCoord3D position;
	((BfmeRvaTransform *)((char *)this - 0x20))->transform(
		(BfmeRvaCoord3D *)(*(char **)((char *)this - 0x1c) + 0x190),
		&position);
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
	((BfmeRvaTransform *)((char *)this - 0x20))->transform(
		(BfmeRvaCoord3D *)(*(char **)((char *)this - 0x1c) + 0x184),
		&position);
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
	((BfmeRvaTransform *)((char *)this - 0x20))->transform(
		(BfmeRvaCoord3D *)(*(char **)((char *)this - 0x1c) + 0x19c),
		&position);
	return &position;
}
