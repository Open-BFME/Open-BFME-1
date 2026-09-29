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

#define BFME_UNIT_ANGLE_ONE (1.0f)
#define BFME_UNIT_ANGLE_MINUS_ONE (-1.0f)
#define BFME_UNIT_ANGLE_LIMIT (0.99f)
#define BFME_UNIT_ANGLE_ZERO (0.0f)

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
