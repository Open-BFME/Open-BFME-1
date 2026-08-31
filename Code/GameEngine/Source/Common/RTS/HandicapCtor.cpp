// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O2 /GX

typedef float Real;

class Handicap
{
public:
	Handicap();

private:
	Real m_handicaps[2][2];
};

Handicap::Handicap()
{
	for (int handicap = 0; handicap < 2; ++handicap)
	{
		for (int thing = 0; thing < 2; ++thing)
		{
			m_handicaps[handicap][thing] = 1.0f;
		}
	}
}
