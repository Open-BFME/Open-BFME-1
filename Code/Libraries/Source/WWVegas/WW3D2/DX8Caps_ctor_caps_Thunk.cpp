// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// Open-BFME5: lift the capability-record DX8 constructor to clean C++.

#include "wwstring.h"

struct IDirect3D8;
struct _D3DADAPTER_IDENTIFIER8;
enum WW3DFormat { WW3DFormat_dummy = 0 };

struct _D3DCAPS8
{
	unsigned char m_unreconstructed_00[0x1C];
	unsigned DevCaps;
	unsigned char m_unreconstructed_20[0x110];
};
typedef _D3DCAPS8 D3DCAPS8;

class DX8Caps
{
public:
	DX8Caps(IDirect3D8 *, const D3DCAPS8 &, WW3DFormat,
		const _D3DADAPTER_IDENTIFIER8 &);

private:
	void Compute_Caps(WW3DFormat, const _D3DADAPTER_IDENTIFIER8 &);

	int m_maxDisplayWidth;
	int m_maxDisplayHeight;
	D3DCAPS8 m_caps;
	bool m_supportTnL;
	unsigned char m_unreconstructed_139[0x153];
	int m_vendorId;
	unsigned char m_unreconstructed_290[0x0C];
	StringClass m_driverDLL;
	IDirect3D8 *m_direct3D;
	StringClass m_capsLog;
	StringClass m_compactLog;
};

// ??0DX8Caps@@QAE@PAUIDirect3D8@@ABU_D3DCAPS8@@W4WW3DFormat@@ABU_D3DADAPTER_IDENTIFIER8@@@Z
DX8Caps::DX8Caps(IDirect3D8 *direct3D, const D3DCAPS8 &caps,
	WW3DFormat displayFormat, const _D3DADAPTER_IDENTIFIER8 &adapterIdentifier)
	: m_maxDisplayWidth(0),
	  m_maxDisplayHeight(0),
	  m_caps(caps),
	  m_vendorId(0),
	  m_direct3D(direct3D)
{
	if ((m_caps.DevCaps & 0x10000) == 0x10000) {
		m_supportTnL = true;
	} else {
		m_supportTnL = false;
	}

	Compute_Caps(displayFormat, adapterIdentifier);
}
