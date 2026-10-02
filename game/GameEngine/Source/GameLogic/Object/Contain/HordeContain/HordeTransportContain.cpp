// cl: /DNDEBUG /MD /EHsc
//
// HordeTransportContain::update, retail RVA 0x0024CD10, from
// GameLogic/Object/Contain/HordeContain/HordeTransportContain.cpp -- the retail
// __FILE__ literal at 0x010B0710 that this body passes to
// GetGameLogicRandomValue.
//
// Identity: the constructor ??0HordeTransportContain@@ at 0x0024B6F0 stores the
// UpdateModule sub-object vftable 0x00CB05B0, and this body is its slot 0
// (slot 1 is ?getDisabledTypesToProcess@UpdateModule@@, which fixes the table as
// the UpdateModule interface, whose slot 0 is update()).  The tail call goes to
// 0x0022D660, slot 0 of TransportContain's own UpdateModule vftable 0x00CAD410
// as stored by ??0TransportContain@@ -- the base-class update.
//
// `this` is the UpdateModule sub-object at +0x10, so the two calls the tick
// makes on the object start reach HordeTransportContain through its primary
// base. The direct calls route through ILTs 0x0000F510 and 0x0003CBD7
// to the matched address-derived owners at 0x0024CAE0 and 0x0024C940.

int GetGameLogicRandomValue(int lo, int hi, char *file, int line);

class Rva0024CAE0Owner
{
public:
	void maintainNestedRiders(void);
};

class Rva0024C940Owner
{
public:
	void processNestedRiders(void);
};

// UpdateModule.h defines UPDATE_SLEEP_NONE as one frame.
enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1 };

class TransportContain
{
public:
	virtual UpdateSleepTime update(void);
};

class HordeTransportContain
{
public:
	void update(void);

	char m_updateModuleHead[0xd4];
	int m_framesUntilNextCall;
	unsigned char m_enabled;
};

void HordeTransportContain::update(void)
{
	if (m_enabled == 1)
	{
		if (m_framesUntilNextCall == -1000)
		{
			Rva0024CAE0Owner *self =
				(Rva0024CAE0Owner *)((char *)this - 0x10);
			m_framesUntilNextCall =
				GetGameLogicRandomValue(3, 5, "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\HordeTransportContain.cpp", 0x350);
			self->maintainNestedRiders();
		}
		if (m_framesUntilNextCall <= 0)
		{
			((Rva0024C940Owner *)((char *)this - 0x10))->processNestedRiders();
			m_framesUntilNextCall =
				GetGameLogicRandomValue(0, 4, "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\HordeTransportContain.cpp", 0x35d);
		}
		--m_framesUntilNextCall;
	}
	((TransportContain *)this)->TransportContain::update();
}
