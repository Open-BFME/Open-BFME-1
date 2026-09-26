// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <list>

class Overridable
{
public:
	const Overridable *getFinalOverride() const;
	unsigned char m_pad[0xd4];
	volatile unsigned int m_flags;
};
class Rva0024B3A0Bridge
{
public:
	unsigned char m_pad[4];
	Overridable *m_final;
};
class Rva0024B3A0Receiver;
class Object
{
public:
	void *m_vtable;
	Rva0024B3A0Bridge *m_bridge;
	unsigned char m_pad08[0x1f4];
	Rva0024B3A0Receiver *m_contain;
	unsigned char m_pad200[0x168];
	bool m_rva368Flag;
};
class Rva0024B3A0Receiver
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2c();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3c();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4c();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5c();
	virtual void slot60();
	virtual void slot64();
	virtual class Rva0024B3A0Receiver *getReceiver();
	virtual void slot6c();
	virtual void slot70();
	virtual void slot74();
	virtual void slot78();
	virtual void slot7c();
	virtual void slot80();
	virtual void slot84();
	virtual void slot88();
	virtual void slot8c();
	virtual void slot90();
	virtual void slot94();
	virtual void slot98();
	virtual void slot9c();
	virtual void onRider(Object *);
	virtual void slota4();
	virtual void slota8();
	virtual void slotac();
	virtual void slotb0();
	virtual void slotb4();
	virtual void slotb8();
	virtual void slotbc();
	virtual void slotc0();
	virtual void slotc4();
	virtual void slotc8();
	virtual void slotcc();
	virtual void slotd0();
	virtual void slotd4();
	virtual void slotd8();
	virtual void slotdc();
	virtual void slote0();
	virtual void slote4();
	virtual void slote8();
	virtual const _STL::list<Object *> &riders() const;
};
class SiegeExit0024AE60
{
public:
	void release(Object *, void *);
};
class Rva0024B3A0SiegeInterface
{
public:
	void update(Object *, void *);
private:
	unsigned char m_pad[0xc4];
	bool m_disabled;
};
void Rva0024B3A0SiegeInterface::update(Object *argument, void *context)
{
	if (m_disabled) return;
	Rva0024B3A0Bridge *bridge = argument->m_bridge;
	const Overridable *final = (const Overridable *)bridge;
	if (bridge && bridge->m_final)
		final = bridge->m_final->getFinalOverride();
	unsigned int flags = final->m_flags;
	if (((flags >> 8) & 0x10) != 0)
	{
		Rva0024B3A0Receiver *holder = argument->m_contain;
		if (!holder) return;
		Rva0024B3A0Receiver *receiver = holder->getReceiver();
		if (!receiver) return;
		_STL::list<Object *> occupants = receiver->riders();
		for (_STL::list<Object *>::iterator it = occupants.begin();
			it != occupants.end(); ++it)
		{
			Object *rider = *it;
			if (!rider->m_rva368Flag)
			{
				receiver->onRider(rider);
				((SiegeExit0024AE60 *)((char *)this - 0x30))->release(rider, context);
			}
		}
		for (_STL::list<Object *>::iterator it = occupants.begin();
			it != occupants.end(); ++it)
		{
			Object *rider = *it;
			receiver->onRider(rider);
			((SiegeExit0024AE60 *)((char *)this - 0x30))->release(rider, context);
		}
	}
	((SiegeExit0024AE60 *)((char *)this - 0x30))->release(
		argument, context);
}
