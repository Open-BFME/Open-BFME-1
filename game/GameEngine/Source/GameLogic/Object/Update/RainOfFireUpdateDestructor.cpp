// cl: /DNDEBUG /MD /EHsc
// BFME RainOfFireUpdate destructor; the vtable family and base call are
// identified by the retail body at 0x002A0C90.

class Thing;
class Object;
class ModuleData
{
public:
	unsigned char m_pad[0x14];
	volatile float m_initialDelay;
};

class Gen_dtor_00113d40
{
public:
	virtual ~Gen_dtor_00113d40();

protected:
	const ModuleData *m_moduleData;
};

class ROFU_DeepBase : public Gen_dtor_00113d40
{
protected:
	Object *m_object;
};

class ROFU_Iface1
{
public:
	virtual void slot();
};

class ROFU_Iface2
{
public:
	virtual void slot();
};

class ROFU_BehaviorModule : public ROFU_DeepBase, public ROFU_Iface1
{
public:
	virtual ~ROFU_BehaviorModule() {}
};

class UpdateModule : public ROFU_BehaviorModule, public ROFU_Iface2
{
public:
	virtual ~UpdateModule() {}

protected:
	unsigned int m_f14;
	int m_f18;
	int m_f1c;
};

class ROFU_Interface
{
public:
	virtual void slot();
};

#define DISPLAY_SLOT(N) virtual void slot##N();
class Display
{
public:
	DISPLAY_SLOT(0)  DISPLAY_SLOT(1)  DISPLAY_SLOT(2)  DISPLAY_SLOT(3)
	DISPLAY_SLOT(4)  DISPLAY_SLOT(5)  DISPLAY_SLOT(6)  DISPLAY_SLOT(7)
	DISPLAY_SLOT(8)  DISPLAY_SLOT(9)  DISPLAY_SLOT(10) DISPLAY_SLOT(11)
	DISPLAY_SLOT(12) DISPLAY_SLOT(13) DISPLAY_SLOT(14) DISPLAY_SLOT(15)
	DISPLAY_SLOT(16) DISPLAY_SLOT(17) DISPLAY_SLOT(18) DISPLAY_SLOT(19)
	DISPLAY_SLOT(20) DISPLAY_SLOT(21) DISPLAY_SLOT(22) DISPLAY_SLOT(23)
	DISPLAY_SLOT(24) DISPLAY_SLOT(25) DISPLAY_SLOT(26) DISPLAY_SLOT(27)
	DISPLAY_SLOT(28) DISPLAY_SLOT(29) DISPLAY_SLOT(30) DISPLAY_SLOT(31)
	DISPLAY_SLOT(32) DISPLAY_SLOT(33) DISPLAY_SLOT(34) DISPLAY_SLOT(35)
	DISPLAY_SLOT(36) DISPLAY_SLOT(37) DISPLAY_SLOT(38)
	virtual void slot39(float);
};
#undef DISPLAY_SLOT

extern Display *TheDisplay;
extern float BfmeZeroRange;
extern double g_bfmeSubB3;

class GlobalData
{
private:
	unsigned char m_pad[0x48];

public:
	float m_field48;
};

extern GlobalData *TheWritableGlobalData;

class RainOfFireUpdate : public UpdateModule, public ROFU_Interface
{
public:
	virtual ~RainOfFireUpdate();

private:
	unsigned int m_frame;
	unsigned int m_f28;
	volatile float m_f2c;
	unsigned int m_f30;
	float m_f34;
};

// ??1RainOfFireUpdate@@UAE@XZ
RainOfFireUpdate::~RainOfFireUpdate()
{
	const ModuleData *data = m_moduleData;
	m_f2c = 0.0f;
	m_f28 = 0;

	if (data != 0 && TheDisplay != 0)
	{
		TheDisplay->slot39(g_bfmeSubB3 - data->m_initialDelay * BfmeZeroRange);
	}

	if (TheWritableGlobalData != 0)
	{
		TheWritableGlobalData->m_field48 = m_f2c * BfmeZeroRange;
	}
}
