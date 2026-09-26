// cl: /DNDEBUG /MD /EHsc
// Open-BFME: BFME unit-vector angle helper, retail body 0x003FD650 (108B).
// The named ILT 0x00022C6E is called by Path::bfmeBuildTurnArc.

struct Coord3D
{
	float x;
	float y;
	float z;
};

extern float ACos(float);

#define BFME_UNIT_ANGLE_ONE (*(const float *)0x01075334)
#define BFME_UNIT_ANGLE_MINUS_ONE (*(const float *)0x0109BF3C)
#define BFME_UNIT_ANGLE_LIMIT (*(const float *)0x01083BFC)
#define BFME_UNIT_ANGLE_ZERO (*(const float *)0x01075350)

float bfmeUnitAngle(const Coord3D *a, const Coord3D *b)
{
	float dot = a->z * b->z + a->y * b->y + a->x * b->x;
	if (dot > BFME_UNIT_ANGLE_ONE)
		return BFME_UNIT_ANGLE_ZERO;
	if (dot < BFME_UNIT_ANGLE_MINUS_ONE)
		dot = -1.0f;
	else if (dot >= BFME_UNIT_ANGLE_LIMIT)
		return BFME_UNIT_ANGLE_ZERO;
	float result = ACos(dot);
	return result;
}
