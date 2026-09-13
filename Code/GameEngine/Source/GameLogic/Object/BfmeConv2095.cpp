struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object
{
public:
	unsigned char m_bfmeHeadYB[0x74];
	int m_bfme74YB;
};

class Weapon
{
public:
	bool privateFireWeapon(const Object *src, const Coord3D *pos, const Object *tgt, int n, const Coord3D *alt, int a, int b, int c, int *out);

	bool bfmeFireYB(const Object *src, const Coord3D *pos, const Coord3D *alt, int n);
	bool bfmeFireYC(const Object *src, const Coord3D *pos, const Object *tgt, int n);
};

bool Weapon::bfmeFireYB(const Object *src, const Coord3D *pos, const Coord3D *alt, int n)
{
	return privateFireWeapon(src, pos, 0, 0, alt, 1, 0, n, 0);
}

bool Weapon::bfmeFireYC(const Object *src, const Coord3D *pos, const Object *tgt, int n)
{
	return privateFireWeapon(src, pos, tgt, tgt->m_bfme74YB, 0, 1, 0, n, 0);
}
