// Twenty-three 11-byte bodies, each a single global load and a tail jump:
//
//     mov ecx, [global]
//     jmp <member>
//
// Nothing else -- no arguments touched, no ret of their own. The global's
// address rides a DIR32 relocation from retail, so only the jump has to
// resolve.
//
// They fall into thirteen globals. Where two of them load the SAME global and
// jump to the SAME member, that is one member with two callers, not two
// members -- so the classes below carry one declaration per distinct target
// and 0x0046ECF0 and 0x0055BD20 share theirs.
//
// The tail jump means these forward whatever the member returns and whatever
// stack arguments they were handed; void and no arguments is the reading that
// costs nothing, since neither is visible in eleven bytes.

class BfmeGlobal_012ed5bc
{
public:
	void bfmeCall_008f73f0(void);					// retail 0x008F73F0
};

class RecorderClass;
extern RecorderClass *TheRecorder;
class ShroudManager;
extern ShroudManager *TheShroudManager;
				// 0x012ED5BC

class BfmeGlobal_012ed62c
{
public:
	void bfmeCall_0004a7a5(void);					// retail 0x0004A7A5
};

				// 0x012ED62C

class BfmeGlobal_012ed668
{
public:
	void bfmeCall_0000b99c(void);					// retail 0x0000B99C
	void bfmeCall_00020f36(void);					// retail 0x00020F36
	void bfmeCall_00041b5a(void);					// retail 0x00041B5A
};

// 0x012ED668 is retail's AudioManager *TheAudio
// (?TheAudio@@3PAVAudioManager@@A); the BfmeGlobal_012ed668 view above is
// TU-local.
class AudioManager;
extern AudioManager *TheAudio;

class BfmeGlobal_012f076c
{
public:
	void bfmeCall_00028ce0(void);					// retail 0x00028CE0
	void bfmeCall_0004aa98(void);					// retail 0x0004AA98
};

extern BfmeGlobal_012f076c *TheBfmeGlobal_012f076c;				// 0x012F076C

class BfmeGlobal_012f0898
{
public:
	void bfmeCall_000238a3(void);					// retail 0x000238A3
};

class GameLogic;
extern GameLogic *TheGameLogic;				// 0x012F0898

class BfmeGlobal_012f142c
{
public:
	void bfmeCall_00045ec1(void);					// retail 0x00045EC1
};

class Eva;
extern Eva *TheEva;				// 0x012F142C

// 0x012F19E8 is retail's `WindowManager *g_rva012F19E8WindowManager`
// (?g_rva012F19E8WindowManager@@3PAVWindowManager@@A, defined in
// game/GameEngine/Source/GameClient/GUI/WindowManager.cpp); the
// BfmeGlobal_012f19e8 view below is TU-local and reached through a cast.
class WindowManager;
extern WindowManager *g_rva012F19E8WindowManager;				// 0x012F19E8

class BfmeGlobal_012f19e8
{
public:
	void bfmeCall_000290d2(void);					// retail 0x000290D2
};

class BfmeGlobal_012f4b70
{
public:
	void bfmeCall_0003514d(void);					// retail 0x0003514D
};

class BannerUI;
extern BannerUI *TheBannerUI;				// 0x012F4B70

class BfmeGlobal_012f4b98
{
public:
	void bfmeCall_00045c91(void);					// retail 0x00045C91
};

extern BfmeGlobal_012f4b98 *TheBfmeGlobal_012f4b98;				// 0x012F4B98

class BfmeGlobal_012f4c64
{
public:
	void bfmeCall_0003cbd2(void);					// retail 0x0003CBD2
	void bfmeCall_00046d1c(void);					// retail 0x00046D1C
};

extern BfmeGlobal_012f4c64 *TheBfmeGlobal_012f4c64;				// 0x012F4C64

class BfmeGlobal_012f6928
{
public:
	void bfmeCall_00030832(void);					// retail 0x00030832
	void bfmeCall_000459d5(void);					// retail 0x000459D5
};

class RayEffectSystem;
extern RayEffectSystem *TheRayEffects;				// 0x012F6928

class BfmeGlobal_012f706c
{
public:
	void bfmeCall_0000386e(void);					// retail 0x0000386E
};

// 0x012F706C is retail's `LivingWorldManager *TheLivingWorldManager`
// (?TheLivingWorldManager@@3PAVLivingWorldManager@@A, defined in
// game/GameEngine/Source/GameLogic/LivingWorld/LivingWorldManager.cpp);
// the BfmeGlobal_012f706c view above is TU-local and reached through a cast.
class LivingWorldManager;
extern LivingWorldManager *TheLivingWorldManager;				// 0x012F706C

class BfmeGlobal_012f7fe0
{
public:
	void bfmeCall_00029532(void);					// retail 0x00029532
	void bfmeCall_0002ec85(void);					// retail 0x0002EC85
};

extern BfmeGlobal_012f7fe0 *TheBfmeGlobal_012f7fe0;				// 0x012F7FE0

// ?Gen_0006c170@@YAXXZ
void Gen_0006c170(void)
{
	(*reinterpret_cast<BfmeGlobal_012ed62c **>(&TheRecorder))->bfmeCall_0004a7a5();
}

// ?Gen_002ed8c0@@YAXXZ
void Gen_002ed8c0(void)
{
	reinterpret_cast<BfmeGlobal_012f4b70 *>(TheBannerUI)->bfmeCall_0003514d();
}

// ?Gen_002ed950@@YAXXZ
void Gen_002ed950(void)
{
	TheBfmeGlobal_012f076c->bfmeCall_00028ce0();
}

// ?Gen_002eec60@@YAXXZ
void Gen_002eec60(void)
{
	TheBfmeGlobal_012f4b98->bfmeCall_00045c91();
}

// ?Gen_002eff20@@YAXXZ
void Gen_002eff20(void)
{
	TheBfmeGlobal_012f076c->bfmeCall_0004aa98();
}

// ?Gen_002f05d0@@YAXXZ
void Gen_002f05d0(void)
{
	reinterpret_cast<BfmeGlobal_012f142c *>(TheEva)->bfmeCall_00045ec1();
}

// ?Gen_002f0dc0@@YAXXZ
void Gen_002f0dc0(void)
{
	(*reinterpret_cast<BfmeGlobal_012ed5bc **>(&TheShroudManager))->bfmeCall_008f73f0();
}

// ?Gen_002f0f50@@YAXXZ
void Gen_002f0f50(void)
{
	((BfmeGlobal_012f0898 *)TheGameLogic)->bfmeCall_000238a3();
}

// ?Gen_0042e720@@YAXXZ
void Gen_0042e720(void)
{
	reinterpret_cast<BfmeGlobal_012f6928 *>(TheRayEffects)->bfmeCall_000459d5();
}

// ?Gen_0042e730@@YAXXZ
void Gen_0042e730(void)
{
	reinterpret_cast<BfmeGlobal_012f6928 *>(TheRayEffects)->bfmeCall_00030832();
}

// ?Gen_0046ecf0@@YAXXZ
void Gen_0046ecf0(void)
{
	((BfmeGlobal_012f19e8 *)g_rva012F19E8WindowManager)->bfmeCall_000290d2();
}

// ?Gen_0046ed60@@YAXXZ
void Gen_0046ed60(void)
{
	TheBfmeGlobal_012f4c64->bfmeCall_00046d1c();
}

// ?Gen_0046ed70@@YAXXZ
void Gen_0046ed70(void)
{
	TheBfmeGlobal_012f4c64->bfmeCall_0003cbd2();
}

// ?Gen_0055bd20@@YAXXZ
void Gen_0055bd20(void)
{
	((BfmeGlobal_012f19e8 *)g_rva012F19E8WindowManager)->bfmeCall_000290d2();
}

// ?Gen_006a3790@@YAXXZ
void Gen_006a3790(void)
{
	((BfmeGlobal_012ed668 *)TheAudio)->bfmeCall_0000b99c();
}

// ?Gen_006a37a0@@YAXXZ
void Gen_006a37a0(void)
{
	((BfmeGlobal_012ed668 *)TheAudio)->bfmeCall_00041b5a();
}

// ?Gen_006a37b0@@YAXXZ
void Gen_006a37b0(void)
{
	((BfmeGlobal_012ed668 *)TheAudio)->bfmeCall_00020f36();
}

// ?Gen_006be3f0@@YAXXZ
void Gen_006be3f0(void)
{
	TheBfmeGlobal_012f7fe0->bfmeCall_00029532();
}

// ?Gen_006be400@@YAXXZ
void Gen_006be400(void)
{
	TheBfmeGlobal_012f7fe0->bfmeCall_0002ec85();
}

// ?Gen_006fd020@@YAXXZ
void Gen_006fd020(void)
{
	((BfmeGlobal_012f706c *)TheLivingWorldManager)->bfmeCall_0000386e();
}
