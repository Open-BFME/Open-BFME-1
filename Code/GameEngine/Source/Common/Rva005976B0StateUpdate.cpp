// cl: /O2 /Ob0
// Open-BFME5: clean C++ conversion of the 0x005976B0 state updater.

class BfmeThingAOA
{
public:
	char m_flag;
	char m_pad[ 3 ];
	void *m_what;
};

bool __cdecl rva00592D60Ask();

class BfmeThingBRF : public BfmeThingAOA
{
public:
	void bfmeStepBRF();
};

class BfmeThingCDA
{
public:
	void j_0001bc70();
};

class Rva005976B0
{
public:
	void update( void *value );

private:
	char m_pad[ 0x68 ];
	BfmeThingBRF m_state;
};

// ?update@Rva005976B0@@QAEXPAX@Z
void Rva005976B0::update( void *value )
{
	BfmeThingBRF *state = &m_state;
	void *what = value ? *(void **)( (char *)value + 0x74 ) : 0;

	if ( what != state->m_what || !state->m_flag )
	{
		state->bfmeStepBRF();
		state->m_what = what;
		state->m_flag = 1;
	}

	if ( rva00592D60Ask() )
		( (BfmeThingCDA *)state )->j_0001bc70();
}
