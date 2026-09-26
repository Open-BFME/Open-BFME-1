struct Rva8BB1A0Bounds
{
	float left;
	float top;
	float right;
	float bottom;
};

struct Rva8BB1A0BoundsSource
{
	void getBounds(Rva8BB1A0Bounds *bounds);
};

struct Rva8BB1A0BoundsCheckThunk
{
	bool contains(Rva8BB1A0BoundsSource *source, void *unused);

	unsigned char padding[0x1274];
	int x;
	int y;
};

// ?d_008bb1a0@@YAXXZ
bool Rva8BB1A0BoundsCheckThunk::contains(Rva8BB1A0BoundsSource *source, void *)
{
	Rva8BB1A0Bounds bounds;
	source->getBounds(&bounds);
	if ((float)x >= bounds.left && (float)x <= bounds.right &&
		(float)y >= bounds.top && (float)y <= bounds.bottom) {
		return true;
	}
	return false;
}
