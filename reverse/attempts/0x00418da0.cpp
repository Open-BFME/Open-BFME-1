// ??0Drawable@@QAE@PBVThingTemplate@@W4DrawableStatus@@H@Z
// partial score=0.4 date=2026-09-19
// ??0Drawable@@QAE@PBVThingTemplate@@W4DrawableStatus@@H@Z
// BFME Drawable constructor witness at retail 0x00418DA0.
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef bool Bool;

class ThingTemplate;

// The retail body calls the Thing constructor through ILT 0x0002C1A6.
class ThingConstructorCall
{
public:
	void construct(const ThingTemplate *);
};
#pragma comment(linker, "/alternatename:?construct@ThingConstructorCall@@QAEXPBVThingTemplate@@@Z=?j_0002c1a6@@YAXXZ")

// The second base starts at +0x60 and contributes an EH cleanup state.
class BfmeBaseAt60
{
	char m_pad[4];
public:
	__declspec(noinline) ~BfmeBaseAt60() {}
};

class ThingAt0
{
	char m_pad[0x60];
public:
	__declspec(noinline) ~ThingAt0() {}
};

// This is the exact direct callee spelling printed by tools/callees.py.
class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString() : m_data(0) {}
	BFMERetailAsciiString(const BFMERetailAsciiString &other)
		: m_data(other.m_data) {}
	void releaseBuffer();
	~BFMERetailAsciiString()
	{
		releaseBuffer();
	}
	void *m_data;
};

class DrawableSubobject
{
	char m_pad[0x90];
public:
	void construct();
	__declspec(noinline) ~DrawableSubobject() {}
};
#pragma comment(linker, "/alternatename:?construct@DrawableSubobject@@QAEXXZ=?j_0003b700@@YAXXZ")

enum DrawableStatus
{
	DRAWABLE_STATUS_NONE = 0
};

class Drawable : public ThingAt0, public BfmeBaseAt60
{
	char m_pad64[0xa8];
	char m_string10c[4];
	char m_pad110[0x1c4];
	char m_string2d4[4];
	char m_string2d8[4];
	char m_pad2dc[0x1c];
	char m_string2f8[4];
	char m_pad2fc[0x20];
	char m_subobject31c[0x90];

	static void initStaticImages();

public:
	Drawable(const ThingTemplate *thingTemplate, DrawableStatus status,
		Int drawableID);
};
#pragma comment(linker, "/alternatename:?initStaticImages@Drawable@@CAXXZ=?j_000087e2@@YAXXZ")

class GameClientCall
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
	virtual void registerDrawable(Drawable *);
};

class ModuleDataCall
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
	virtual Int getMinimumRequiredGameLOD() const;
	virtual void slot3c();
	virtual unsigned char isAllowed() const;
};

class ModuleInfoCall
{
public:
	void *m_begin;
	void *m_end;
	BFMERetailAsciiString getNthName(Int index) const;
};
#pragma comment(linker, "/alternatename:?getNthName@ModuleInfoCall@@QBE?AVBFMERetailAsciiString@@H@Z=?j_0000eb56@@YAXXZ")

class ModuleFactoryCall
{
public:
	void *newModule(Drawable *drawable, const BFMERetailAsciiString &name,
		const ModuleDataCall *data, Int type);
};
#pragma comment(linker, "/alternatename:?newModule@ModuleFactoryCall@@QAEPAXPAVDrawable@@ABVBFMERetailAsciiString@@PBVModuleDataCall@@H@Z=?j_00003c1f@@YAXXZ")

class DrawableModuleCall
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void onObjectCreated();
	virtual void slot18();
	virtual void slot1c();
	virtual void *getModuleData();
};

class AudioClientCall
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08();
	virtual void slot0c(); virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1c(); virtual void slot20();
	virtual void slot24(); virtual void slot28(); virtual void slot2c();
	virtual void slot30(); virtual void slot34(); virtual void slot38();
	virtual void slot3c(); virtual void slot40(); virtual void slot44();
	virtual void slot48();
	virtual void update(void *value);
};

class DrawableEmitterCall
{
public:
	void emit(void *value, Bool flag);
};
#pragma comment(linker, "/alternatename:?emit@DrawableEmitterCall@@QAEXPAX_N@Z=?j_0002cb79@@YAXXZ")

void *operator new[](unsigned int);

extern "C" int __declspec(dllimport) __cdecl _memicmp(
	const void *, const void *, unsigned int);

static ModuleInfoCall *moduleInfoAt(const ThingTemplate *thingTemplate,
	UnsignedInt offset)
{
	return reinterpret_cast<ModuleInfoCall *>(
		const_cast<UnsignedByte *>(reinterpret_cast<const UnsignedByte *>(
			thingTemplate) + offset));
}

static GameClientCall *TheGameClientAt12F1464()
{
	return *reinterpret_cast<GameClientCall **>(0x012F1464);
}

Drawable::Drawable(const ThingTemplate *thingTemplate,
	DrawableStatus status, Int drawableID)
{
	reinterpret_cast<ThingConstructorCall *>(this)->construct(thingTemplate);
	UnsignedInt *word = reinterpret_cast<UnsignedInt *>(this);
	UnsignedInt zero = 0;
	UnsignedInt one = 0x3f800000;
	BFMERetailAsciiString initialName;

	word[0x60 / 4] = 0x01073744;
	word[0] = 0x010f1560;
	word[0x60 / 4] = 0x010f154c;
	word[0x64 / 4] = zero;
	word[0x68 / 4] = zero;
	word[0x78 / 4] = zero;
	word[0x7c / 4] = zero;
	word[0x80 / 4] = zero;
	word[0x84 / 4] = zero;
	word[0x88 / 4] = zero;
	word[0x8c / 4] = zero;
	word[0xa8 / 4] = 7;
	word[0xac / 4] = one;
	word[0xb0 / 4] = one;
	word[0xb4 / 4] = one;
	word[0xb8 / 4] = one;
	word[0xbc / 4] = one;
	word[0xc0 / 4] = one;
	word[0xc4 / 4] = one;
	word[0xc8 / 4] = zero;
	word[0xcc / 4] = one;
	word[0xd0 / 4] = zero;
	word[0xd4 / 4] = 10;
	word[0xd8 / 4] = zero;
	word[0xdc / 4] = zero;
	word[0xe0 / 4] = zero;
	*reinterpret_cast<UnsignedByte *>(this) = 0;
	*(reinterpret_cast<UnsignedByte *>(this) + 0xe4) = 0;
	word[0xf0 / 4] = zero;
	word[0xf4 / 4] = one;
	word[0xf8 / 4] = 0x3cf5c28f;
	word[0xfc / 4] = zero;
	word[0x100 / 4] = zero;
	word[0x104 / 4] = zero;
	word[0x108 / 4] = zero;
	word[0x10c / 4] = zero;
	word[0x110 / 4] = status;
	word[0x114 / 4] = zero;
	word[0x118 / 4] = zero;
	word[0x11c / 4] = zero;
	word[0x120 / 4] = zero;
	word[0x124 / 4] = zero;
	word[0x128 / 4] = zero;
	word[0x12c / 4] = zero;
	word[0x130 / 4] = zero;
	word[0x134 / 4] = zero;
	word[0x138 / 4] = zero;
	word[0x13c / 4] = zero;
	*(reinterpret_cast<UnsignedByte *>(this) + 0x140) = 1;
	*(reinterpret_cast<UnsignedByte *>(this) + 0x141) = 1;
	*(reinterpret_cast<UnsignedByte *>(this) + 0x142) = 1;
	*(reinterpret_cast<UnsignedByte *>(this) + 0x143) = 1;
	word[0x144 / 4] = zero;
	word[0x148 / 4] = zero;
	word[0x14c / 4] = zero;
	word[0x15c / 4] = zero;
	word[0x160 / 4] = zero;
	word[0x164 / 4] = zero;
	word[0x1fc / 4] = ~zero;
	word[0x23c / 4] = ~zero;
	word[0x240 / 4] = zero;
	word[0x244 / 4] = zero;
	word[0x248 / 4] = zero;
	word[0x24c / 4] = zero;
	word[0x250 / 4] = zero;
	word[0x254 / 4] = zero;
	word[0x258 / 4] = zero;
	word[0x25c / 4] = zero;
	word[0x260 / 4] = zero;
	word[0x264 / 4] = zero;
	word[0x268 / 4] = zero;
	word[0x26c / 4] = zero;
	word[0x270 / 4] = zero;
	word[0x274 / 4] = zero;
	word[0x278 / 4] = zero;
	word[0x27c / 4] = zero;
	word[0x280 / 4] = zero;
	word[0x284 / 4] = zero;
	word[0x288 / 4] = zero;
	word[0x28c / 4] = zero;
	word[0x290 / 4] = zero;
	word[0x294 / 4] = zero;
	word[0x298 / 4] = zero;
	word[0x29c / 4] = zero;
	word[0x2a0 / 4] = zero;
	word[0x2a4 / 4] = zero;
	word[0x2a8 / 4] = zero;
	word[0x2ac / 4] = zero;
	word[0x2b0 / 4] = zero;
	word[0x2b4 / 4] = zero;
	word[0x2b8 / 4] = zero;
	word[0x2bc / 4] = zero;
	word[0x2c0 / 4] = zero;
	word[0x2c4 / 4] = zero;
	word[0x2c8 / 4] = 0xbf800000u;
	word[0x2cc / 4] = zero;
	word[0x2d0 / 4] = zero;
	word[0x2d4 / 4] = zero;
	word[0x2d8 / 4] = zero;
	word[0x2dc / 4] = zero;
	word[0x2e0 / 4] = zero;
	word[0x2e4 / 4] = zero;
	word[0x2e8 / 4] = zero;
	word[0x2ec / 4] = zero;
	word[0x2f4 / 4] = zero;
	word[0x2f8 / 4] = zero;
	word[0x2fc / 4] = zero;
	word[0x300 / 4] = zero;
	word[0x304 / 4] = ~zero;
	word[0x308 / 4] = zero;
	word[0x30c / 4] = zero;
	word[0x310 / 4] = zero;
	word[0x314 / 4] = zero;
	*(reinterpret_cast<UnsignedByte *>(this) + 0x318) = 0;
	*(reinterpret_cast<UnsignedByte *>(this) + 0x319) = 0;
	*(reinterpret_cast<UnsignedByte *>(this) + 0x31a) = 0;
	*(reinterpret_cast<UnsignedByte *>(this) + 0x31b) = 0;
	(reinterpret_cast<DrawableSubobject *>(
		reinterpret_cast<UnsignedByte *>(this) + 0x31c))->construct();
	*(reinterpret_cast<UnsignedByte *>(this) + 0x3ac) = 0;
	*(reinterpret_cast<UnsignedByte *>(this) + 0x3ad) = 0;
	*(reinterpret_cast<UnsignedByte *>(this) + 0x3ae) = 0;
	*(reinterpret_cast<UnsignedByte *>(this) + 0x3af) = 1;
	*(reinterpret_cast<UnsignedByte *>(this) + 0x3b0) = 0;
	*(reinterpret_cast<UnsignedByte *>(this) + 0x3b2) = 1;
	*(reinterpret_cast<UnsignedByte *>(this) + 0x3b3) = 1;
	*(reinterpret_cast<UnsignedByte *>(this) + 0x3b4) = 0;
	word[0x3b8 / 4] = zero;
	word[0x3bc / 4] = zero;

	word[0x150 / 4] = zero;
	word[0x154 / 4] = zero;
	word[0x158 / 4] = zero;
	word[0x198 / 4] = one;
	word[0x19c / 4] = zero;
	word[0x1a0 / 4] = zero;
	word[0x1a4 / 4] = zero;
	word[0x1a8 / 4] = zero;
	word[0x1ac / 4] = one;
	word[0x1b0 / 4] = zero;
	word[0x1b4 / 4] = zero;
	word[0x1b8 / 4] = zero;
	word[0x1bc / 4] = zero;
	word[0x1c0 / 4] = one;
	word[0x1c4 / 4] = zero;
	word[0x200 / 4] = one;
	word[0x204 / 4] = zero;
	word[0x208 / 4] = zero;
	word[0x20c / 4] = zero;
	word[0x210 / 4] = zero;
	word[0x214 / 4] = one;
	word[0x218 / 4] = zero;
	word[0x21c / 4] = zero;
	word[0x220 / 4] = zero;
	word[0x224 / 4] = zero;
	word[0x228 / 4] = one;
	word[0x22c / 4] = zero;
	word[0x230 / 4] = zero;
	word[0x234 / 4] = zero;
	word[0x238 / 4] = zero;
	word[0x168 / 4] = one;
	word[0x16c / 4] = zero;
	word[0x170 / 4] = zero;
	word[0x174 / 4] = zero;
	word[0x178 / 4] = zero;
	word[0x17c / 4] = one;
	word[0x180 / 4] = zero;
	word[0x184 / 4] = zero;
	word[0x188 / 4] = zero;
	word[0x18c / 4] = zero;
	word[0x190 / 4] = one;
	word[0x194 / 4] = zero;

	word[0x1f8 / 4] = *reinterpret_cast<const UnsignedInt *>(
		reinterpret_cast<const UnsignedByte *>(thingTemplate) + 0x3c0);
	word[0x2f0 / 4] = drawableID;

	GameClientCall *client = TheGameClientAt12F1464();
	client->registerDrawable(this);
	if (TheGameClientAt12F1464() != 0)
	{
		const UnsignedByte *templateBytes =
			reinterpret_cast<const UnsignedByte *>(thingTemplate);
		const Int lod = *reinterpret_cast<const Int *>(
			reinterpret_cast<const UnsignedByte *>(
				*reinterpret_cast<const UnsignedByte **>(0x012ED5AC)) + 0x16c4);
		ModuleFactoryCall *factory = *reinterpret_cast<ModuleFactoryCall **>(
			0x012EF198);

		ModuleInfoCall *drawInfo = moduleInfoAt(thingTemplate, 0x2a0);
		UnsignedByte *drawBegin = *reinterpret_cast<UnsignedByte **>(drawInfo);
		UnsignedByte *drawEnd = *reinterpret_cast<UnsignedByte **>(
			reinterpret_cast<UnsignedByte *>(drawInfo) + 4);
		Int drawCount = (drawEnd - drawBegin) / 0x14;
		void **drawOut = reinterpret_cast<void **>(
			new void *[drawCount + 1]);
		word[0x150 / 4] = reinterpret_cast<UnsignedInt>(drawOut);
		for (Int i = 0; i < drawCount; ++i)
		{
			ModuleDataCall *data = *reinterpret_cast<ModuleDataCall **>(
				drawBegin + i * 0x14 + 8);
			if ((*reinterpret_cast<const UnsignedByte **>(0x012ED5C8))[0x1c] != 0 &&
				data->getMinimumRequiredGameLOD() > lod)
				continue;
			{
				BFMERetailAsciiString name = drawInfo->getNthName(i);
				*drawOut++ = factory->newModule(this, name, data, 1);
			}
			if (data->isAllowed() == 0)
				*(reinterpret_cast<UnsignedByte *>(this) + 0x31b) = 1;
		}
		*drawOut = 0;

		ModuleInfoCall *clientInfo = moduleInfoAt(thingTemplate, 0x2ac);
		UnsignedByte *clientBegin = *reinterpret_cast<UnsignedByte **>(clientInfo);
		UnsignedByte *clientEnd = *reinterpret_cast<UnsignedByte **>(
			reinterpret_cast<UnsignedByte *>(clientInfo) + 4);
		Int clientCount = (clientEnd - clientBegin) / 0x14;
		if (clientCount != 0)
		{
			void **clientOut = reinterpret_cast<void **>(
				new void *[clientCount + 1]);
			word[0x154 / 4] = reinterpret_cast<UnsignedInt>(clientOut);
			for (Int i = 0; i < clientCount; ++i)
			{
				ModuleDataCall *data = *reinterpret_cast<ModuleDataCall **>(
					clientBegin + i * 0x14 + 8);
				Bool skip = false;
				{
					BFMERetailAsciiString probeName = clientInfo->getNthName(i);
					if ((*(reinterpret_cast<const UnsignedByte *>(thingTemplate) + 0xc8) & 0x40) != 0 &&
						(*reinterpret_cast<const UnsignedByte **>(0x012ED5C8))[0x1a] == 0)
					{
						const UnsignedByte *text = probeName.m_data == 0
							? reinterpret_cast<const UnsignedByte *>(0x0107388b)
							: reinterpret_cast<const UnsignedByte *>(probeName.m_data) + 8;
						unsigned int length = probeName.m_data == 0 ? 0
							: *reinterpret_cast<const unsigned short *>(
								reinterpret_cast<const UnsignedByte *>(probeName.m_data) + 4);
						if (length > 0x10)
							length = 0x10;
						skip = _memicmp(text,
							reinterpret_cast<const void *>(0x0108f7b8), length) == 0;
					}
				}
				if (!skip)
				{
					BFMERetailAsciiString name = clientInfo->getNthName(i);
					*clientOut++ = factory->newModule(this, name, data, 2);
				}
			}
			*clientOut = 0;
		}

		ModuleInfoCall *otherInfo = moduleInfoAt(thingTemplate, 0x2b8);
		UnsignedByte *otherBegin = *reinterpret_cast<UnsignedByte **>(otherInfo);
		UnsignedByte *otherEnd = *reinterpret_cast<UnsignedByte **>(
			reinterpret_cast<UnsignedByte *>(otherInfo) + 4);
		Int otherCount = (otherEnd - otherBegin) / 0x14;
		if (otherCount != 0)
		{
			void **otherOut = reinterpret_cast<void **>(
				new void *[otherCount + 1]);
			word[0x158 / 4] = reinterpret_cast<UnsignedInt>(otherOut);
			for (Int i = 0; i < otherCount; ++i)
			{
				ModuleDataCall *data = *reinterpret_cast<ModuleDataCall **>(
					otherBegin + i * 0x14 + 8);
				BFMERetailAsciiString name = otherInfo->getNthName(i);
				*otherOut++ = factory->newModule(this, name, data, 3);
			}
			*otherOut = 0;
		}
	}
	for (Int listIndex = 0; listIndex < 3; ++listIndex)
	{
		DrawableModuleCall ***list = reinterpret_cast<DrawableModuleCall ***>(
			reinterpret_cast<UnsignedByte *>(this) + 0x150 + listIndex * 4);
		DrawableModuleCall **module = *list;
		if (module != 0)
		{
			while (*module != 0)
			{
				(*module)->onObjectCreated();
				++module;
			}
		}
	}

	initStaticImages();

	UnsignedByte *logic = *reinterpret_cast<UnsignedByte **>(0x012F0898);
	UnsignedByte *state = *reinterpret_cast<UnsignedByte **>(0x012EF190);
	if (logic != 0 && logic[0x69] == 0 && state != 0 && state[0x54] == 0 &&
		*reinterpret_cast<UnsignedByte *>(reinterpret_cast<UnsignedByte *>(this) + 0x140) != 0 &&
		*reinterpret_cast<UnsignedByte *>(reinterpret_cast<UnsignedByte *>(this) + 0x141) != 0 &&
		*reinterpret_cast<UnsignedByte *>(reinterpret_cast<UnsignedByte *>(this) + 0x143) != 0)
	{
		DrawableModuleCall *module = *reinterpret_cast<DrawableModuleCall **>(
			reinterpret_cast<UnsignedByte *>(this) + 0x144);
		if (module != 0)
		{
			AudioClientCall *audio = *reinterpret_cast<AudioClientCall **>(
				0x012ED668);
			if (audio != 0)
				audio->update(*reinterpret_cast<void **>(
				reinterpret_cast<UnsignedByte *>(module) + 0x10));
		}
		module = *reinterpret_cast<DrawableModuleCall **>(
			reinterpret_cast<UnsignedByte *>(this) + 0x148);
		if (module != 0)
		{
			AudioClientCall *audio = *reinterpret_cast<AudioClientCall **>(
				0x012ED668);
			if (audio != 0)
				audio->update(*reinterpret_cast<void **>(
					reinterpret_cast<UnsignedByte *>(module) + 0x10));
		}
		DrawableModuleCall *owner = *reinterpret_cast<DrawableModuleCall **>(
			reinterpret_cast<UnsignedByte *>(this) + 0xfc);
		void *value = 0;
		if (owner != 0)
			value = owner->getModuleData();
		reinterpret_cast<DrawableEmitterCall *>(this)->emit(value, false);
	}

	word[0x3c0 / 4] = zero;
	reinterpret_cast<BFMERetailAsciiString *>(
		reinterpret_cast<UnsignedByte *>(this) + 0x2d4)->releaseBuffer();
	reinterpret_cast<BFMERetailAsciiString *>(
		reinterpret_cast<UnsignedByte *>(this) + 0x2d8)->releaseBuffer();
	(void)status;
}
