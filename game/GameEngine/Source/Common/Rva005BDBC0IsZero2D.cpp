// cl: /O2 /Ob2 /G6
// Open-BFME5: clean C++ conversion of the two-component zero test.

typedef float Real;

extern const Real g_rva01075350;

struct Rva005BDBC0Point
{
	unsigned int m_unused;
	Real x;
	Real y;
};

int Rva005BDBC0IsZero2D(const Rva005BDBC0Point *point)
{
	if (point->x == g_rva01075350 && point->y == g_rva01075350)
		return 1;
	return 0;
}
