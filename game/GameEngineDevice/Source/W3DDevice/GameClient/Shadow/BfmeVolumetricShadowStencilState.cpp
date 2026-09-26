// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
//
// Clean reconstruction of the BFME stencil-state helper at 0x007C12C0.
// The dump has no recovered source name: it is a cdecl helper taking one
// Boolean on the stack.  The device is the BFME global, and the COM calls are
// deliberately expressed through the D3D vtable so the retail ABI remains
// visible in the source.

typedef int Bool;

struct IDirect3DDevice9;
typedef long (__stdcall *BfmeSetRenderState)(IDirect3DDevice9 *, unsigned, unsigned);

class W3DRadarFormatCaps
{
public:
	unsigned char m_unreconstructed_00[0x90];
	unsigned m_caps;
};

extern IDirect3DDevice9 *TheD3DDevice;
extern W3DRadarFormatCaps *TheW3DRadarFormatCaps;

// ?setVolumetricShadowStencil@BfmeShadowState@@SAX_N@Z
void __stdcall setVolumetricShadowStencil(Bool frontFace)
{
	IDirect3DDevice9 *device = TheD3DDevice;

	if (!frontFace) {
		(*(BfmeSetRenderState **)device)[57](device, 0x36, 1);
		(*(BfmeSetRenderState **)device)[57](device, 0x35, 1);
	} else {
		(*(BfmeSetRenderState **)device)[57](device, 0x35, 1);
		(*(BfmeSetRenderState **)device)[57](device, 0x37, 1);
	}

	if (TheW3DRadarFormatCaps->m_caps & 0x100) {
		(*(BfmeSetRenderState **)device)[57](device, 0xB9, 1);
		(*(BfmeSetRenderState **)device)[57](device, 0x16, 1);

		if (!frontFace) {
			(*(BfmeSetRenderState **)device)[57](device, 0x37, 8);
			(*(BfmeSetRenderState **)device)[57](device, 0xBB, 1);
			(*(BfmeSetRenderState **)device)[57](device, 0xBA, 1);
			(*(BfmeSetRenderState **)device)[57](device, 0xBC, 7);
			(*(BfmeSetRenderState **)device)[57](device, 0xBD, 8);
		} else {
			(*(BfmeSetRenderState **)device)[57](device, 0x36, 7);
			(*(BfmeSetRenderState **)device)[57](device, 0xBA, 1);
			(*(BfmeSetRenderState **)device)[57](device, 0xBC, 1);
			(*(BfmeSetRenderState **)device)[57](device, 0xBB, 8);
			(*(BfmeSetRenderState **)device)[57](device, 0xBD, 8);
		}
	}
}
