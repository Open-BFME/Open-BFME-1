// cl: /O2 /Ob0

extern "C" void * __cdecl memset(void *block, int value, unsigned int bytes);
#pragma intrinsic(memset)

union GameMessageArgumentType
{
	int integer;
	int pixel[2];
};

class GameMessage
{
public:
	const GameMessageArgumentType *getArgument(int index) const;

	char m_pad[0x10];
	int m_type;
};

struct LookAtEvent
{
	int m_type;
	int m_pixel[2];
	int m_value;
	int m_stamp;
	unsigned char m_flags;
	char m_align[3];
};

class LookAtTranslator
{
public:
	LookAtTranslator();
	virtual ~LookAtTranslator();
	virtual void translate();
	void fillFromMessage(const GameMessage *msg);
	void emit(LookAtEvent *event);
	void emitSelectedA();
	void emitSelectedB();

private:
	int m_link;
	LookAtEvent m_events[20];
	unsigned char m_flag;
	int m_mode;
	int m_a;
	int m_b;
};

extern LookAtTranslator *TheLookAtTranslator;

LookAtTranslator::LookAtTranslator()
{
	LookAtTranslator *self = this;
	LookAtEvent *event = self->m_events;
	int remaining = 20;
	do
	{
		event->m_flags &= 0xFE;
		event->m_type = 0;
		event->m_value = 0;
		event->m_stamp = 0;
		++event;
	} while (--remaining);

	self->m_flag = 0;
	self->m_mode = 2;
	self->m_a = 0;
	self->m_b = 0;

	if (TheLookAtTranslator == 0)
	{
		TheLookAtTranslator = self;
		self->m_link = 0;
		memset(self->m_events, 0, sizeof(self->m_events));
	}
}

void LookAtTranslator::fillFromMessage(const GameMessage *msg)
{
	int type = msg->m_type;
	switch (type)
	{
	case 4:
	case 6:
	case 14:
	case 16:
	{
		LookAtEvent *event = &m_events[type];
		event->m_type = type;
		const GameMessageArgumentType *arg = msg->getArgument(0);
		event->m_pixel[0] = arg->pixel[0];
		event->m_pixel[1] = arg->pixel[1];
		arg = msg->getArgument(1);
		event->m_value = arg->integer;
		arg = msg->getArgument(2);
		event->m_stamp = arg->integer;
		event->m_flags &= 0xFE;
		break;
	}
	}
}

void LookAtTranslator::emitSelectedA()
{
	LookAtEvent *first = &m_events[4];
	LookAtEvent *second = &m_events[14];
	LookAtEvent *selected;
	if (first && !(first->m_flags & 1))
	{
		if (second && !(second->m_flags & 1))
		{
			unsigned int secondStamp = second->m_stamp;
			unsigned int firstStamp = first->m_stamp;
			selected = firstStamp <= secondStamp ? second : first;
		}
		else
		{
			selected = first;
		}
	}
	else
	{
		selected = second && !(second->m_flags & 1) ? second : 0;
	}
	if (selected)
		emit(selected);
}

void LookAtTranslator::emitSelectedB()
{
	LookAtEvent *first = &m_events[6];
	LookAtEvent *second = &m_events[16];
	LookAtEvent *selected;
	if (first && !(first->m_flags & 1))
	{
		if (second && !(second->m_flags & 1))
		{
			unsigned int secondStamp = second->m_stamp;
			unsigned int firstStamp = first->m_stamp;
			selected = firstStamp <= secondStamp ? second : first;
		}
		else
		{
			selected = first;
		}
	}
	else
	{
		selected = second && !(second->m_flags & 1) ? second : 0;
	}
	if (selected)
		emit(selected);
}
