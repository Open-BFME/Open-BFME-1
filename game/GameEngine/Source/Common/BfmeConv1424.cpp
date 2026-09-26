// cl: /Od /Gy

class BfmeRegVLY
{
public:
	void bfmeInitVLY();
};

extern BfmeRegVLY g_bfmeRegVLY;

class BfmeThingVLY
{
public:
	BfmeThingVLY *bfmeCtorVLY();
};

BfmeThingVLY *BfmeThingVLY::bfmeCtorVLY()
{
	if (0)
		g_bfmeRegVLY.bfmeInitVLY();
	return this;
}


class BfmeRegVLZ
{
public:
	void bfmeInitVLZ();
};

extern BfmeRegVLZ g_bfmeRegVLZ;

class BfmeThingVLZ
{
public:
	BfmeThingVLZ *bfmeCtorVLZ();
};

BfmeThingVLZ *BfmeThingVLZ::bfmeCtorVLZ()
{
	if (1)
		g_bfmeRegVLZ.bfmeInitVLZ();
	return this;
}
