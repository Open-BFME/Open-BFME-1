// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O2 /GX

typedef float Real;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Handicap.h
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
