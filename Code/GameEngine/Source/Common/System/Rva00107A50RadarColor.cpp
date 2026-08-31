// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class Rva00107A50Player
{
public:
	char padding00[0x1c4];
	void *colorData;
};

class Rva00107A50Object
{
public:
	Rva00107A50Player *getControllingPlayer();
};

struct Rva00107A50RadarObject
{
	void *vtable;
	Rva00107A50Object *object;
	Rva00107A50RadarObject *next;
	unsigned color;
};

class Rva00107A50Radar
{
public:
	void refreshObjectColor(Rva00107A50Object *object);

private:
	char padding00[0x10];
	Rva00107A50RadarObject *objects;
};

unsigned rva00107A50MakeColor(void *colorData);

void Rva00107A50Radar::refreshObjectColor(Rva00107A50Object *object)
{
	if (!object)
		return;

	Rva00107A50Player *player = object->getControllingPlayer();
	if (!player)
		return;

	for (Rva00107A50RadarObject *entry = objects; entry; entry = entry->next)
	{
		if (entry->object == object)
		{
			entry->color = rva00107A50MakeColor(player->colorData);
			return;
		}
	}
}
