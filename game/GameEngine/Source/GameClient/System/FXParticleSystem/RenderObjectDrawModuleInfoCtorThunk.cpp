// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: RenderObjectDrawModuleInfo ctor
// Vtbl + three (byte, zero, zero, 8) groups and lead-in zeros.

namespace FXParticleSystem
{

extern "C" char RenderObjectDrawModuleInfo_vtbl;

class __declspec(novtable) RenderObjectDrawModuleInfo
{
public:
	RenderObjectDrawModuleInfo();

private:
	char *m_vtbl;
	unsigned char m_04;
	unsigned char m_pad05[3];
	unsigned int m_08;
	unsigned char m_0c;
	unsigned char m_pad0d[3];
	unsigned int m_10;
	unsigned int m_14;
	unsigned int m_18;
	unsigned int m_1c;
	unsigned int m_20;
	unsigned int m_24;
	unsigned int m_28;
	unsigned int m_2c;
	unsigned int m_30;
	unsigned int m_34;
	unsigned int m_38;
	unsigned int m_3c;
};

// ??0RenderObjectDrawModuleInfo@FXParticleSystem@@QAE@XZ
RenderObjectDrawModuleInfo::RenderObjectDrawModuleInfo()
{
	*reinterpret_cast<char *volatile *>(this) = &RenderObjectDrawModuleInfo_vtbl;
	*reinterpret_cast<unsigned int volatile *>(&m_10) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_20) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_30) = 0;
	*reinterpret_cast<unsigned char volatile *>(&m_0c) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_14) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_18) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_1c) = 8;
	*reinterpret_cast<unsigned int volatile *>(&m_24) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_28) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_2c) = 8;
	*reinterpret_cast<unsigned int volatile *>(&m_34) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_38) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_3c) = 8;
	*reinterpret_cast<unsigned char volatile *>(&m_04) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_08) = 0;
}

}
