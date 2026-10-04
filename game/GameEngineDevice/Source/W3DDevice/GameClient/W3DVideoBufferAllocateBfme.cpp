// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
// BFME W3DVideoBuffer allocation with its embedded 0x14-byte render state.

void __cdecl W3DRadarResetLock(void);
char __cdecl bfmeUnlock1179(void);

class TextureLoader
{
public:
	static void Validate_Texture_Size(unsigned int &, unsigned int &);
};

class Rva00739C70State
{
public:
	bool rva0073a050(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);

private:
	int m_value_00;
	int m_value_04;
	void *m_texture;
	char m_surface[4];
	unsigned int m_flags;
};

#pragma comment(linker, "/alternatename:?rva0073a050@Rva00739C70State@@QAE_NIIIIII@Z=?j_0002d5ab@@YAXXZ")

class W3DRadarResetGuard
{
public:
	W3DRadarResetGuard(void) { W3DRadarResetLock(); }
	~W3DRadarResetGuard(void) { bfmeUnlock1179(); }
};

class VideoBuffer
{
public:
	virtual ~VideoBuffer();
	virtual void slot01(void) = 0;
	virtual bool allocate(unsigned int, unsigned int, bool) = 0;
	virtual void free(void) = 0;
	virtual void *lock(void) = 0;
	virtual void unlock(void) = 0;
	virtual bool valid(void) = 0;

protected:
	unsigned int m_x_pos;
	unsigned int m_y_pos;
	unsigned int m_width;
	unsigned int m_height;
	unsigned int m_texture_width;
	unsigned int m_texture_height;
	unsigned int m_pitch;
	float m_value_20;
	int m_format;
	bool m_flag_28;
};

class W3DVideoBuffer : public VideoBuffer
{
public:
	virtual bool allocate(unsigned int width, unsigned int height, bool flag);

private:
	Rva00739C70State m_states[1];
	Rva00739C70State *m_state_40;
	Rva00739C70State *m_state_44;
	bool m_flag_48;
	bool m_flag_49;
	bool m_flag_4a;
};

bool W3DVideoBuffer::allocate(unsigned int width, unsigned int height, bool flag)
{
	W3DRadarResetGuard guard;
	free();
	m_width = width;
	m_height = height;
	m_texture_width = width;
	m_texture_height = height;
	TextureLoader::Validate_Texture_Size(m_texture_width, m_texture_height);
	int format = m_format;
	m_flag_49 = flag;

	unsigned int state_format;
	switch (format) {
	case 2:
		state_format = 0x16;
		break;
	case 5:
		state_format = flag ? 0x15 : 0x16;
		break;
	case 1:
		state_format = 0x14;
		break;
	case 3:
		state_format = 0x17;
		break;
	case 4:
		state_format = 0x18;
		break;
	default:
		return false;
	}

	int index = 0;
	Rva00739C70State *state = m_states;
	while (index < 1) {
		if (!state->rva0073a050(m_texture_width, m_texture_height,
			m_width, m_height, state_format, 0))
			return false;
		++index;
		++state;
	}
	return true;
}
