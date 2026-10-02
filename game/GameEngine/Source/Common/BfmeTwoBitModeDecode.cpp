// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

// The normalisation step this body calls is retail 0x009B4680, defined as
// Rva009B4680Normalize (game/GameEngine/Source/Common/Rva009B4680Normalize.cpp).
struct Rva009B4680State;

int Rva009B4680Normalize(Rva009B4680State *state);

int Rva009B5090DecodeMode(unsigned char *ctx)
{
	Rva009B4680State *state = (Rva009B4680State *)(ctx + 0x150);
	int value = Rva009B4680Normalize(state) * 2;
	value += Rva009B4680Normalize(state);

	switch (value) {
	case 0:
		return 0;
	case 1:
		return 2;
	case 2:
		return 3;
	case 3:
		return 4;
	}
	return 0;
}
