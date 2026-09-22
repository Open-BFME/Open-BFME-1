// ?bfmeStencilClearHelper933AF0@@YAXXZ
// partial score=0.45 date=2026-09-22
// cl: /DNDEBUG /MD /EHsc
// Retail 0x00933AF0 (139 B). Sets the BFME stencil-clear flag at 0x012D7188,
// decrements the global retry counter at 0x012D7184, and calls
// DX8Wrapper::Clear() with one of two argument sets depending on
// Has_Stencil()/the counter value -- or returns without clearing when the
// counter is neither exhausted-this-call nor already at its 0xFF sentinel.
// Address-derived: no named caller/vtable/string identifies the owner
// beyond the proven W3DGadget caller cited in the brief.

class Vector3
{
public:
	Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
	float X, Y, Z;
};

class DX8Wrapper
{
public:
	static bool Has_Stencil(void);
	static void Clear(
		bool clear_color,
		bool clear_z_stencil,
		bool clear_stencil,
		const Vector3 &color,
		float dest_alpha,
		float z,
		unsigned int stencil);
};

unsigned char g_bfmeStencilClearFlag933AF0;
int g_bfmeStencilRetryCounter933AF0;

// ?bfmeStencilClearHelper933AF0@@YAXXZ
void bfmeStencilClearHelper933AF0(void)
{
	g_bfmeStencilClearFlag933AF0 = 1;

	bool clearZStencil = false;

	if (DX8Wrapper::Has_Stencil())
	{
		int counter = g_bfmeStencilRetryCounter933AF0 - 1;
		g_bfmeStencilRetryCounter933AF0 = counter;

		if (counter >= 1)
		{
			if (counter != 0xff)
				return;
			goto doClear;
		}

		g_bfmeStencilRetryCounter933AF0 = 0xff;
		goto doClear;
	}

	clearZStencil = true;

doClear:
	DX8Wrapper::Clear(false, clearZStencil, true, Vector3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 0);
}
