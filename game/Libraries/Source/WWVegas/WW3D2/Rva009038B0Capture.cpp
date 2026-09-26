// cl: /DNDEBUG /MD /EHsc

struct Rva009038B0Device;

struct Rva009038B0Device
{
#define RVA009038B0_SLOT(n) virtual void __stdcall slot##n(void) = 0;
	RVA009038B0_SLOT(00) RVA009038B0_SLOT(01) RVA009038B0_SLOT(02)
	RVA009038B0_SLOT(03) RVA009038B0_SLOT(04) RVA009038B0_SLOT(05)
	RVA009038B0_SLOT(06) RVA009038B0_SLOT(07) RVA009038B0_SLOT(08)
	RVA009038B0_SLOT(09) RVA009038B0_SLOT(10) RVA009038B0_SLOT(11)
	RVA009038B0_SLOT(12) RVA009038B0_SLOT(13) RVA009038B0_SLOT(14)
	RVA009038B0_SLOT(15) RVA009038B0_SLOT(16) RVA009038B0_SLOT(17)
	RVA009038B0_SLOT(18) RVA009038B0_SLOT(19) RVA009038B0_SLOT(20)
	RVA009038B0_SLOT(21) RVA009038B0_SLOT(22) RVA009038B0_SLOT(23)
	RVA009038B0_SLOT(24) RVA009038B0_SLOT(25) RVA009038B0_SLOT(26)
	RVA009038B0_SLOT(27) RVA009038B0_SLOT(28) RVA009038B0_SLOT(29)
	RVA009038B0_SLOT(30) RVA009038B0_SLOT(31) RVA009038B0_SLOT(32)
	RVA009038B0_SLOT(33) RVA009038B0_SLOT(34) RVA009038B0_SLOT(35)
	RVA009038B0_SLOT(36) RVA009038B0_SLOT(37) RVA009038B0_SLOT(38)
	RVA009038B0_SLOT(39) RVA009038B0_SLOT(40) RVA009038B0_SLOT(41)
	RVA009038B0_SLOT(42) RVA009038B0_SLOT(43) RVA009038B0_SLOT(44)
	virtual long __stdcall GetTransform(unsigned long, void *) = 0;
	RVA009038B0_SLOT(46) RVA009038B0_SLOT(47) RVA009038B0_SLOT(48)
	RVA009038B0_SLOT(49) RVA009038B0_SLOT(50) RVA009038B0_SLOT(51)
	RVA009038B0_SLOT(52) RVA009038B0_SLOT(53) RVA009038B0_SLOT(54)
	RVA009038B0_SLOT(55) RVA009038B0_SLOT(56) RVA009038B0_SLOT(57)
	virtual long __stdcall GetRenderState(unsigned long, unsigned long *) = 0;
	RVA009038B0_SLOT(59) RVA009038B0_SLOT(60) RVA009038B0_SLOT(61)
	RVA009038B0_SLOT(62) RVA009038B0_SLOT(63) RVA009038B0_SLOT(64)
	RVA009038B0_SLOT(65)
	virtual long __stdcall GetTextureStageState(unsigned long, unsigned long, unsigned long *) = 0;
	RVA009038B0_SLOT(67) RVA009038B0_SLOT(68) RVA009038B0_SLOT(69)
	RVA009038B0_SLOT(70) RVA009038B0_SLOT(71) RVA009038B0_SLOT(72)
	RVA009038B0_SLOT(73) RVA009038B0_SLOT(74) RVA009038B0_SLOT(75)
	RVA009038B0_SLOT(76) RVA009038B0_SLOT(77) RVA009038B0_SLOT(78)
	RVA009038B0_SLOT(79) RVA009038B0_SLOT(80) RVA009038B0_SLOT(81)
	RVA009038B0_SLOT(82) RVA009038B0_SLOT(83) RVA009038B0_SLOT(84)
	RVA009038B0_SLOT(85) RVA009038B0_SLOT(86) RVA009038B0_SLOT(87)
	RVA009038B0_SLOT(88) RVA009038B0_SLOT(89) RVA009038B0_SLOT(90)
	RVA009038B0_SLOT(91) RVA009038B0_SLOT(92)
	virtual long __stdcall GetVertexShader(unsigned long *) = 0;
	RVA009038B0_SLOT(94) RVA009038B0_SLOT(95) RVA009038B0_SLOT(96)
	RVA009038B0_SLOT(97) RVA009038B0_SLOT(98) RVA009038B0_SLOT(99)
	RVA009038B0_SLOT(100) RVA009038B0_SLOT(101) RVA009038B0_SLOT(102)
	RVA009038B0_SLOT(103) RVA009038B0_SLOT(104) RVA009038B0_SLOT(105)
	RVA009038B0_SLOT(106) RVA009038B0_SLOT(107)
	virtual long __stdcall GetPixelShader(unsigned long *) = 0;
#undef RVA009038B0_SLOT
};

struct Rva009038B0State
{
	unsigned char bytes[0x2EC];
};

struct Rva009038B0Stage
{
	unsigned long state1;
	unsigned long state2Low;
	unsigned long state2;
	unsigned long state3Low;
	unsigned long state3;
	unsigned long state4;
	unsigned long state4Low;
	unsigned long state5;
	unsigned long state6Low;
	unsigned long state6;
	unsigned long state11;
	unsigned long state24;
	unsigned long transform[16];
};

class DX8Wrapper
{
public:
	static Rva009038B0Device *D3DDevice;
};

void Rva009038B0Capture(Rva009038B0State *state)
{
	unsigned char *bytes = state->bytes;

	DX8Wrapper::D3DDevice->GetRenderState(0x16, reinterpret_cast<unsigned long *>(bytes + 0x00));
	DX8Wrapper::D3DDevice->GetRenderState(0x07, reinterpret_cast<unsigned long *>(bytes + 0x04));
	DX8Wrapper::D3DDevice->GetRenderState(0x0E, reinterpret_cast<unsigned long *>(bytes + 0x08));
	DX8Wrapper::D3DDevice->GetRenderState(0x0F, reinterpret_cast<unsigned long *>(bytes + 0x0C));
	DX8Wrapper::D3DDevice->GetRenderState(0x13, reinterpret_cast<unsigned long *>(bytes + 0x10));
	DX8Wrapper::D3DDevice->GetRenderState(0x14, reinterpret_cast<unsigned long *>(bytes + 0x14));
	DX8Wrapper::D3DDevice->GetRenderState(0x17, reinterpret_cast<unsigned long *>(bytes + 0x18));
	DX8Wrapper::D3DDevice->GetRenderState(0x18, reinterpret_cast<unsigned long *>(bytes + 0x1C));
	DX8Wrapper::D3DDevice->GetRenderState(0x19, reinterpret_cast<unsigned long *>(bytes + 0x20));
	DX8Wrapper::D3DDevice->GetRenderState(0x1A, reinterpret_cast<unsigned long *>(bytes + 0x24));
	DX8Wrapper::D3DDevice->GetRenderState(0x1B, reinterpret_cast<unsigned long *>(bytes + 0x28));
	DX8Wrapper::D3DDevice->GetRenderState(0x1D, reinterpret_cast<unsigned long *>(bytes + 0x2C));
	DX8Wrapper::D3DDevice->GetRenderState(0x34, reinterpret_cast<unsigned long *>(bytes + 0x30));
	DX8Wrapper::D3DDevice->GetRenderState(0x3C, reinterpret_cast<unsigned long *>(bytes + 0x34));
	DX8Wrapper::D3DDevice->GetRenderState(0x80, reinterpret_cast<unsigned long *>(bytes + 0x38));
	DX8Wrapper::D3DDevice->GetRenderState(0x81, reinterpret_cast<unsigned long *>(bytes + 0x3C));
	DX8Wrapper::D3DDevice->GetRenderState(0x88, reinterpret_cast<unsigned long *>(bytes + 0x40));
	DX8Wrapper::D3DDevice->GetRenderState(0x89, reinterpret_cast<unsigned long *>(bytes + 0x44));
	DX8Wrapper::D3DDevice->GetRenderState(0x8F, reinterpret_cast<unsigned long *>(bytes + 0x48));
	DX8Wrapper::D3DDevice->GetRenderState(0xA8, reinterpret_cast<unsigned long *>(bytes + 0x4C));
	DX8Wrapper::D3DDevice->GetRenderState(0xAB, reinterpret_cast<unsigned long *>(bytes + 0x50));
	DX8Wrapper::D3DDevice->GetRenderState(0xC1, reinterpret_cast<unsigned long *>(bytes + 0x54));
	DX8Wrapper::D3DDevice->GetRenderState(0xC3, reinterpret_cast<unsigned long *>(bytes + 0x58));
	DX8Wrapper::D3DDevice->GetTransform(0x100, bytes + 0x5C);
	DX8Wrapper::D3DDevice->GetTransform(2, bytes + 0x9C);
	DX8Wrapper::D3DDevice->GetTransform(3, bytes + 0xDC);
	DX8Wrapper::D3DDevice->GetVertexShader(reinterpret_cast<unsigned long *>(bytes + 0x11C));
	DX8Wrapper::D3DDevice->GetPixelShader(reinterpret_cast<unsigned long *>(bytes + 0x120));

	unsigned long stage = 0;
	Rva009038B0Stage *stages = reinterpret_cast<Rva009038B0Stage *>(bytes + 0x124);
	for (; stage < 4; ++stage)
	{
		Rva009038B0Stage *current = &stages[stage];
		DX8Wrapper::D3DDevice->GetTextureStageState(stage, 1, &current->state1);
		DX8Wrapper::D3DDevice->GetTextureStageState(stage, 2, &current->state2);
		unsigned long value = current->state2;
		value &= 0xFFFFFFF0;
		current->state2Low = current->state2 & 0x0F;
		current->state2 = value;
		DX8Wrapper::D3DDevice->GetTextureStageState(stage, 3, &current->state3);
		value = current->state3;
		current->state3Low = value & 0x0F;
		current->state3 = value & 0xFFFFFFF0;
		DX8Wrapper::D3DDevice->GetTextureStageState(stage, 4, &current->state4);
		DX8Wrapper::D3DDevice->GetTextureStageState(stage, 5, &current->state5);
		value = current->state5;
		value &= 0xFFFFFFF0;
		current->state4Low = current->state5 & 0x0F;
		current->state5 = value;
		DX8Wrapper::D3DDevice->GetTextureStageState(stage, 6, &current->state6);
		value = current->state6;
		current->state6Low = value & 0x0F;
		current->state6 = value & 0xFFFFFFF0;
		DX8Wrapper::D3DDevice->GetTextureStageState(stage, 0x0B, &current->state11);
		DX8Wrapper::D3DDevice->GetTextureStageState(stage, 0x18, &current->state24);
		DX8Wrapper::D3DDevice->GetTransform(stage + 0x10, &current->transform[0]);
	}
}


