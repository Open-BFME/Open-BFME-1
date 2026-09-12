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

class Vector3
{
	public:
	float X;
	float Y;
	float Z;
};

extern void GameGetColorComponentsReal(int color, float *red, float *green,
	float *blue, float *alpha);
extern void RGB_To_HSV(Vector3 &hsv, const Vector3 &rgb);
extern void HSV_To_RGB(Vector3 &rgb, const Vector3 &hsv);
#define g_bfmeScaleB3 (*(float *)0x01084068)

struct Rva00107A50ColorLocals
{
	float red;
	float green;
	float blue;
	float alpha;
	Vector3 hsv;
	Vector3 rgb;
};

unsigned rva00107A50MakeColor(void *colorData)
{
	Rva00107A50ColorLocals local;

	GameGetColorComponentsReal((int)colorData, &local.red, &local.green,
		&local.blue, &local.alpha);
	local.rgb.X = local.red;
	local.rgb.Y = local.green;
	local.rgb.Z = local.blue;
	RGB_To_HSV(local.hsv, local.rgb);
	local.hsv.Y *= *(const float *)0x0108887C;
	if (local.hsv.Y > 1.0f)
		local.hsv.Y = 1.0f;
	HSV_To_RGB(local.rgb, local.hsv);

	unsigned char alpha = (unsigned char)(int)(local.alpha * g_bfmeScaleB3);
	unsigned char red = (unsigned char)(int)(local.rgb.X * g_bfmeScaleB3);
	unsigned char green = (unsigned char)(int)(local.rgb.Y * g_bfmeScaleB3);
	unsigned char blue = (unsigned char)(int)(local.rgb.Z * g_bfmeScaleB3);
	return (alpha << 24) | (red << 16) | (green << 8) | blue;
}

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
