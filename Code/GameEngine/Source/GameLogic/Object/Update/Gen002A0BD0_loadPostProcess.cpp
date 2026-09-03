// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x002A0BD0: UpdateModule::loadPostProcess, then the +0x20 functor
// with +0x2c, then the same Display/GlobalData scale publish as 0x002A0AD0
// using the Real at +0x28.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Display.h
class Display
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot0a();
	virtual void slot0b();
	virtual void slot0c();
	virtual void slot0d();
	virtual void slot0e();
	virtual void slot0f();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot1a();
	virtual void slot1b();
	virtual void slot1c();
	virtual void slot1d();
	virtual void slot1e();
	virtual void slot1f();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void setAmbient(float value);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
public:
	unsigned char m_pad[0x48];
	float m_value48;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ModuleData
{
public:
	unsigned char m_pad[0x14];
	float m_factor;
};

class Functor
{
public:
	virtual void apply(float value);
	void *m_pad;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule
{
protected:
	virtual void loadPostProcess();

public:
	ModuleData *m_moduleData;
	unsigned char m_gap[0x20 - 0x08];
};

extern Display *TheDisplay;
extern GlobalData *TheWritableGlobalData;

class Gen002A0BD0 : public UpdateModule
{
public:
	void loadPostProcess();

	Functor m_functor;
	float m_scale;
	float m_mul;
};

// ?loadPostProcess@Gen002A0BD0@@QAEXXZ
void Gen002A0BD0::loadPostProcess()
{
	UpdateModule::loadPostProcess();
	m_functor.apply(m_mul);
	float scale = m_scale;
	ModuleData *data = m_moduleData;
	if (data && TheDisplay)
		TheDisplay->setAmbient(1.0 - data->m_factor * m_mul * scale);
	if (TheWritableGlobalData)
		TheWritableGlobalData->m_value48 = scale * m_mul;
}
