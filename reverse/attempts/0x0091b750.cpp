// ?method@Rva0091B750@@QAEXIABU_D3DCAPS8@@@Z
// partial score=0.9167 date=2026-09-24
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep
// Retail RVA 0x0091B750; address-derived identity pending independent naming evidence.

#include <d3d8.h>

class Rva0091B750
{
	unsigned char _unrecovered_000[0x20b];
	unsigned char _formatSupport[100];
	unsigned char _unrecovered_271[0x2a0 - 0x271];
	IDirect3D8 *direct3D;

public:
	void method(unsigned displayFormat, const D3DCAPS8 &caps);
};

void Rva0091B750::method(unsigned displayFormat, const D3DCAPS8 &caps)
{
	if (displayFormat == 0) {
		for (unsigned i = 0; i < 100; ++i) {
			_formatSupport[i] = 0;
		}
		return;
	}

	for (unsigned format = 70; format < 81; ++format) {
		switch (format) {
		case 70:
		case 72:
		case 74:
		case 76:
		case 78:
		case 79:
		case 81:
		case 82:
		case 83:
			_formatSupport[format] = SUCCEEDED(direct3D->CheckDeviceFormat(
				caps.AdapterOrdinal,
				caps.DeviceType,
				(D3DFORMAT)displayFormat,
				2,
				1,
				(D3DFORMAT)format));
			break;
		default:
			break;
		}
	}
}
