// cl: /DNDEBUG /MD /GX- /O2 /Ob2

namespace FXParticleSystem
{

// globals referenced by retail ctor
extern void *g_windGlobalA; // 0x012F7004
extern void *g_windGlobalB; // 0x012B8E00

class WindModuleInfo
{
public:
	WindModuleInfo();
	virtual void dummy();

private:
	int field04;
	float field08;
	float field0c;
	float field10;
	int field14;
	float field18;
	float field1c;
	float field20;
	void *field24;
	int field28;
	float field2c;
	void *field30;
	float field34;
	float field38;
	unsigned char field3c;
	unsigned char pad3d[3];
	int field40;
	int field44;
};

// ??0WindModuleInfo@FXParticleSystem@@QAE@XZ
WindModuleInfo::WindModuleInfo()
{
	field04 = 1;
	field08 = 2.0f;
	field0c = 75.0f;
	field10 = 200.0f;
	field14 = 0;
	field18 = 0.15f;
	field1c = 0.15f;
	field20 = 0.45f;
	field28 = 0;
	field2c = 0.7853981852531433f;
	field24 = g_windGlobalA;
	field34 = 5.4977874755859375f;
	field38 = 6.2831854820251465f;
	field30 = g_windGlobalB;
	field3c = 1;
	field40 = 0;
	field44 = 0;
}

}
