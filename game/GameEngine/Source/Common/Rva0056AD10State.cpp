struct BfmeState56AD10A
{
	char m_head[ 0x2c ];
	unsigned char m_firstFlag;
	unsigned char m_secondFlag;
};

struct BfmeState56AD10B
{
	char m_head[ 0x10c ];
	int m_mode;
};

extern "C" BfmeState56AD10A *g_bfmeState56AD10A;
extern "C" BfmeState56AD10B *g_bfmeState56AD10B;

class Rva0056AD10
{
public:
	int resolveMode() const;

private:
	char m_head[ 0x270 ];
	int m_state;
};

int Rva0056AD10::resolveMode() const
{
	if ( !( g_bfmeState56AD10A->m_firstFlag && g_bfmeState56AD10A->m_secondFlag ) && m_state == 3 )
	{
		if ( g_bfmeState56AD10B == 0 || g_bfmeState56AD10B->m_mode != 2 )
			return 0;

		return 2;
	}

	return 1;
}
