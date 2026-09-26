// ?notify@Rva00411CD0Owner@@QAEXXZ
// partial score=0.88 date=2026-09-26
// cl: /DNDEBUG /MD /EHsc
// Retail RVA 0x00411CD0: address-derived view of the owning Drawable.
class Rva00411CD0Player;
class Rva00411CD0Object
{
public:
	Rva00411CD0Player *getControllingPlayer();
private:
	char pad[0x74];
	unsigned int id;
};
class Rva00411CD0Message
{
public:
	void appendObjectIDArgument(unsigned int id);
};
class Rva00411CD0MessageStream
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08();
	virtual void slot0c(); virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1c(); virtual void slot20();
	virtual void slot24(); virtual void slot28(); virtual void slot2c();
	virtual void slot30();
	virtual Rva00411CD0Message *appendMessage(int id);
};
#define RVACLIENT_HEAD virtual void slot00(); virtual void slot04(); virtual void slot08(); \
	virtual void slot0c(); virtual void slot10(); virtual void slot14(); virtual void slot18(); \
	virtual void slot1c(); virtual void slot20(); virtual void slot24(); virtual void slot28(); \
	virtual void slot2c(); virtual void slot30(); virtual void slot34();
#define RVACLIENT_TAIL virtual void slot3c(); virtual void slot40(); virtual void slot44(); \
	virtual void slot48(); virtual void slot4c(); virtual void slot50(); virtual void slot54(); \
	virtual void slot58(); virtual void slot5c(); virtual void slot60(); virtual void slot64(); \
	virtual void slot68(); virtual void slot6c(); virtual void slot70(); virtual void slot74(); \
	virtual void slot78(); virtual void slot7c(); virtual void slot80(); virtual void slot84(); \
	virtual void slot88(); virtual void slot8c(); virtual void slot90(); virtual void slot94(); \
	virtual void slot98(); virtual void slot9c(); virtual void slota0(); virtual void slota4(); \
	virtual void slota8(); virtual void slotac(); virtual void slotb0(); virtual void slotb4(); \
	virtual void slotb8(); virtual void slotbc(); virtual void slotc0(); virtual void slotc4(); \
	virtual void slotc8(); virtual void slotcc(); virtual void slotd0(); virtual void slotd4(); \
	virtual void slotd8(); virtual void slotdc(); virtual void slote0();
class Rva00411CD0Owner;
class Rva00411CD0InGameUI
{
public:
	RVACLIENT_HEAD
	virtual void slot38();
	RVACLIENT_TAIL
	virtual void notify(Rva00411CD0Owner *owner);
};
class Rva00411CD0Receiver
{
public:
	RVACLIENT_HEAD
	virtual void setEnabled(bool enabled);
	RVACLIENT_TAIL
	virtual bool queryEnabled();
};
#undef RVACLIENT_HEAD
#undef RVACLIENT_TAIL
class Rva00411CD0Owner
{
public:
	void notify();
private:
	char pad000[0xfc];
	Rva00411CD0Object *object;
	char pad100[0x50];
	Rva00411CD0Receiver **receivers;
	char pad154[8];
	int mode;
	char pad160[0x1bb];
	unsigned char flag31b;
	char pad31c[0x90];
	unsigned char flag3ac;
	unsigned char flag3ad;
	unsigned char flag3ae;
};

// Temporary ABI views only: each call below follows the independently decoded
// 0x00411CD0 instruction stream; semantic names remain address-qualified.
extern Rva00411CD0Player **TheBfmePlayers;
extern Rva00411CD0MessageStream *TheMessageStream;
extern Rva00411CD0InGameUI *TheInGameUI;

void Rva00411CD0Owner::notify()
{
	bool enabled;
	if (flag3ad || flag3ae)
	{
		enabled = true;
		if (flag3ac && object)
		{
			Rva00411CD0Player *controllingPlayer = TheBfmePlayers[3];
			if (object->getControllingPlayer() == controllingPlayer)
			{
				Rva00411CD0Message *message = TheMessageStream->appendMessage(0x3ec);
				message->appendObjectIDArgument(*(unsigned int *)((char *)object + 0x74));
				TheInGameUI->notify(this);
			}
		}
	}
	else
	{
		enabled = false;
	}

	Rva00411CD0Receiver **p = receivers;
	while (*p)
	{
		if (flag31b && mode == 5 && !flag3ae)
			enabled = (*p)->queryEnabled();
		(*p)->setEnabled(enabled);
		++p;
	}
}
