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
// base.  Neither callee (0x0024CAE0, 0x0024C940) has an identity yet.

int GetGameLogicRandomValue(int lo, int hi, char *file, int line);

class HordeTransportContainBase
{
public:
	void first(void);
	void second(void);
};

class TransportContain
{
public:
	void update(void);
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
			HordeTransportContainBase *self =
				(HordeTransportContainBase *)((char *)this - 0x10);
			m_framesUntilNextCall =
				GetGameLogicRandomValue(3, 5, (char *)0x010B0710, 0x350);
			self->first();
		}
		if (m_framesUntilNextCall <= 0)
		{
			((HordeTransportContainBase *)((char *)this - 0x10))->second();
			m_framesUntilNextCall =
				GetGameLogicRandomValue(0, 4, (char *)0x010B0710, 0x35d);
		}
		--m_framesUntilNextCall;
	}
	((TransportContain *)this)->update();
}
