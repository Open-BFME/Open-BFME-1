// ?validate@MapObject@@QAEXXZ
// partial score=0.2 date=2026-09-17
// Retail RVA 0x00088480, 1019 bytes.
//
// The duplicate caller reaches this body through ILT 0x00031FCF, and the
// existing MapObject declaration names that operation validate().  The body
// is the BFME audio-aware validation path; its stack-local layout is kept
// address-qualified below where the retail witness is not represented by the
// Zero Hour header.
//
// cl: /DNDEBUG /MD /EHsc

// Keep this TU independent of the Zero Hour aggregate headers.  The retail
// symbol and the two callee signatures below are all that is needed for the
// ABI; pulling in the donor MapObject header also pulls in incompatible STL
// configuration and masks the body-level codegen being measured here.
class MapObject
{
public:
	void validate();
};

typedef unsigned int UInt;
typedef unsigned char Byte;
typedef long Long;

extern "C" __declspec(dllimport) Long __stdcall InterlockedDecrement(Long volatile *addend);

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString() : m_data(0) {}
	BFMERetailAsciiString(const char *text);
	~BFMERetailAsciiString() { releaseBuffer(); }
	void __cdecl format(BFMERetailAsciiString format, ...);
	void releaseBuffer();
	void *m_data;
};

#define AUDIO_SLOT(n) virtual void slot##n() = 0;
class Rva005A00B0AudioClient
{
public:
	AUDIO_SLOT(0)  AUDIO_SLOT(1)  AUDIO_SLOT(2)  AUDIO_SLOT(3)
	AUDIO_SLOT(4)  AUDIO_SLOT(5)  AUDIO_SLOT(6)  AUDIO_SLOT(7)
	AUDIO_SLOT(8)  AUDIO_SLOT(9)  AUDIO_SLOT(10) AUDIO_SLOT(11)
	AUDIO_SLOT(12) AUDIO_SLOT(13) AUDIO_SLOT(14) AUDIO_SLOT(15)
	AUDIO_SLOT(16)
	virtual UInt addAudioEvent(void *event) = 0;
	AUDIO_SLOT(18) AUDIO_SLOT(19) AUDIO_SLOT(20) AUDIO_SLOT(21)
	AUDIO_SLOT(22) AUDIO_SLOT(23) AUDIO_SLOT(24) AUDIO_SLOT(25)
	AUDIO_SLOT(26) AUDIO_SLOT(27) AUDIO_SLOT(28) AUDIO_SLOT(29)
	AUDIO_SLOT(30) AUDIO_SLOT(31) AUDIO_SLOT(32) AUDIO_SLOT(33)
	AUDIO_SLOT(34) AUDIO_SLOT(35) AUDIO_SLOT(36) AUDIO_SLOT(37)
	AUDIO_SLOT(38) AUDIO_SLOT(39) AUDIO_SLOT(40) AUDIO_SLOT(41)
	AUDIO_SLOT(42)
	virtual void refreshAudioEvent(void *event) = 0;
	AUDIO_SLOT(44) AUDIO_SLOT(45) AUDIO_SLOT(46) AUDIO_SLOT(47)
	AUDIO_SLOT(48) AUDIO_SLOT(49) AUDIO_SLOT(50) AUDIO_SLOT(51)
	AUDIO_SLOT(52) AUDIO_SLOT(53) AUDIO_SLOT(54) AUDIO_SLOT(55)
	AUDIO_SLOT(56) AUDIO_SLOT(57) AUDIO_SLOT(58) AUDIO_SLOT(59)
	AUDIO_SLOT(60) AUDIO_SLOT(61) AUDIO_SLOT(62) AUDIO_SLOT(63)
	AUDIO_SLOT(64) AUDIO_SLOT(65) AUDIO_SLOT(66) AUDIO_SLOT(67)
	AUDIO_SLOT(68)
	virtual void updateAudioEvent(void *event) = 0;
};
#undef AUDIO_SLOT

extern Rva005A00B0AudioClient *TheAudioClientUpdate;
extern void *g_bfmeCurEYE;

extern void j_00001005();
extern void j_00004075();
extern void j_000113c4();
extern void j_000121ac();
extern void j_0001325a();
extern void j_0001d002();
extern void j_00026f35();
extern void j_0002940b();
extern void j_0002c6d8();
extern void j_000362ff();
extern void j_0003e4d7();
extern void j_00043c07();
extern void j_00048522();

class Rva00088480OneArgCall
{
public:
	void call(void *argument);
};

class Rva00088480NoArgCall
{
public:
	void call();
};

class Rva00088480ReadyCall
{
public:
	Byte call();
};

class Rva00088480GetCall
{
public:
	void *call(int index);
};

class Rva00088480EventCall
{
public:
	void *call();
};

class Rva00088480PositionalCtor
{
public:
	void call(const void *name, const void *position, int extra);
};

static __forceinline void rvaAssign(void *self, void *source)
{
	union
	{
		void (*raw)();
		void (Rva00088480OneArgCall::*member)(void *);
	} call;
	call.raw = j_0002c6d8;
	(reinterpret_cast<Rva00088480OneArgCall *>(self)->*call.member)(source);
}

static __forceinline void rvaHold(void *self, void *source)
{
	union
	{
		void (*raw)();
		void (Rva00088480OneArgCall::*member)(void *);
	} call;
	call.raw = j_00043c07;
	(reinterpret_cast<Rva00088480OneArgCall *>(self)->*call.member)(source);
}

static __forceinline void rvaReleaseTemporary(void *self)
{
	union
	{
		void (*raw)();
		void (Rva00088480NoArgCall::*member)();
	} call;
	call.raw = j_000362ff;
	(reinterpret_cast<Rva00088480NoArgCall *>(self)->*call.member)();
}

static __forceinline void rvaDestroyMissing(void *self)
{
	union
	{
		void (*raw)();
		void (Rva00088480NoArgCall::*member)();
	} call;
	call.raw = j_00048522;
	(reinterpret_cast<Rva00088480NoArgCall *>(self)->*call.member)();
}

static __forceinline Byte rvaReady(void *self)
{
	union
	{
		void (*raw)();
		Byte (Rva00088480ReadyCall::*member)();
	} call;
	call.raw = j_00001005;
	return (reinterpret_cast<Rva00088480ReadyCall *>(self)->*call.member)();
}

static __forceinline void *rvaGet(void *self, int index)
{
	union
	{
		void (*raw)();
		void *(Rva00088480GetCall::*member)(int);
	} call;
	call.raw = j_0003e4d7;
	return (reinterpret_cast<Rva00088480GetCall *>(self)->*call.member)(index);
}

static __forceinline void *rvaEvent(void *self)
{
	union
	{
		void (*raw)();
		void *(Rva00088480EventCall::*member)();
	} call;
	call.raw = j_0001325a;
	return (reinterpret_cast<Rva00088480EventCall *>(self)->*call.member)();
}

static __forceinline void rvaMakeEvent(void *self, const void *name,
	const void *position, int extra)
{
	union
	{
		void (*raw)();
		void (Rva00088480PositionalCtor::*member)(
			const void *, const void *, int);
	} call;
	call.raw = j_000113c4;
	(reinterpret_cast<Rva00088480PositionalCtor *>(self)->*call.member)(
		name, position, extra);
}

static __forceinline void rvaMakeRef(void *self, void *source)
{
	union
	{
		void (*raw)();
		void (Rva00088480OneArgCall::*member)(void *);
	} call;
	call.raw = j_000121ac;
	(reinterpret_cast<Rva00088480OneArgCall *>(self)->*call.member)(source);
}

static __forceinline void rvaDestroyEvent(void *self)
{
	union
	{
		void (*raw)();
		void (Rva00088480NoArgCall::*member)();
	} call;
	call.raw = j_00026f35;
	(reinterpret_cast<Rva00088480NoArgCall *>(self)->*call.member)();
}

static __forceinline void rvaUpdateThing(void *self, void *argument)
{
	union
	{
		void (*raw)();
		void (Rva00088480OneArgCall::*member)(void *);
	} call;
	call.raw = j_0001d002;
	(reinterpret_cast<Rva00088480OneArgCall *>(self)->*call.member)(argument);
}

static __forceinline void rvaReleaseMapObject(void *self)
{
	union
	{
		void (*raw)();
		void (Rva00088480NoArgCall::*member)();
	} call;
	call.raw = j_00004075;
	(reinterpret_cast<Rva00088480NoArgCall *>(self)->*call.member)();
}

struct Rva00088480State
{
	Byte m_reserved;
	Byte m_ready;
	Byte m_queryState;
	Byte m_queryFlag;
};

struct Rva00088480Locals
{
	Rva00088480State m_state;
	void *m_current;
	void *m_alternate;
	void *m_audioInfo;
	Byte m_name[4];
	Byte m_event[0x70];
};

struct Rva00088480MapObjectView
{
	Byte m_prefix[0x18];
	void *m_thingTemplate;
	Byte m_betweenTemplateAndProperties[8];
	void *m_properties;
	Byte m_betweenPropertiesAndFlags[0x1c];
	UInt m_runtimeFlags;
	Byte m_betweenFlagsAndHandles[0x0c];
	UInt m_handleA;
	UInt m_handleB;
	void *m_audioInfo;
};

static __forceinline void rvaReleaseCounted(void *object)
{
	class Rva00088480DeleteTarget
	{
	public:
		virtual void destroy(int flags) = 0;
	};

	if (object != 0)
	{
		Long *count = reinterpret_cast<Long *>(
			reinterpret_cast<Byte *>(object) + 4);
		if (InterlockedDecrement(count) <= 0)
			reinterpret_cast<Rva00088480DeleteTarget *>(object)->destroy(1);
	}
}

// ?validate@MapObject@@QAEXXZ
void MapObject::validate()
{
	Rva00088480MapObjectView *self =
		reinterpret_cast<Rva00088480MapObjectView *>(this);
	Rva00088480Locals local;

	if (TheAudioClientUpdate == 0 || self->m_thingTemplate == 0)
		return;

	local.m_state.m_queryState = 0;
	local.m_state.m_queryFlag = 0;
	local.m_audioInfo = 0;
	((void (__cdecl *)(void *, void *, void *, void *, void *, void *))j_0002940b)(
		self->m_properties, 0, self->m_thingTemplate,
		&local.m_state.m_queryState, &local.m_audioInfo,
		&local.m_state.m_queryFlag);

	if (local.m_audioInfo != 0)
	{
		BFMERetailAsciiString *name =
			reinterpret_cast<BFMERetailAsciiString *>(local.m_name);
		name->m_data = 0;
		const char *soundName = *reinterpret_cast<const char **>(
			reinterpret_cast<Byte *>(local.m_audioInfo) + 8);
		name->format(BFMERetailAsciiString(" MapObjectAmb %d %s"),
			*(int *)0x012ED5E8, soundName != 0 ? soundName :
			reinterpret_cast<const char *>(0x0107388B));
		rvaUpdateThing(local.m_audioInfo, name);
		++*(int *)0x012ED5E8;
		TheAudioClientUpdate->updateAudioEvent(local.m_audioInfo);
		name->releaseBuffer();
	}

	local.m_current = 0;
	local.m_alternate = 0;
	if (local.m_state.m_queryState != 0 || g_bfmeCurEYE == 0 ||
		(self->m_runtimeFlags & 0x10) == 0)
		return;

	if (local.m_audioInfo == 0)
	{
		void *sound = rvaGet(self->m_thingTemplate, 0x57);
		if (sound != 0)
		{
			sound = reinterpret_cast<Byte *>(sound) + 8;
			rvaAssign(&local.m_current, sound);
		}
		else
		{
			rvaDestroyMissing(&local.m_current);
			local.m_state.m_ready = 0;
		}
		if (local.m_current == 0)
		{
			sound = rvaGet(self->m_thingTemplate, 0x57);
			TheAudioClientUpdate->refreshAudioEvent(sound);
			rvaAssign(&local.m_current, reinterpret_cast<Byte *>(sound) + 8);
		}
	}
	else
	{
		rvaMakeRef(&local.m_alternate, local.m_audioInfo);
		rvaAssign(&local.m_current, &local.m_alternate);
		rvaReleaseTemporary(&local.m_alternate);
		void *sound = rvaGet(self->m_thingTemplate, 0x5b);
		if (sound != 0)
		{
			rvaAssign(&local.m_alternate, reinterpret_cast<Byte *>(sound) + 8);
			if (local.m_alternate == 0)
			{
				TheAudioClientUpdate->refreshAudioEvent(sound);
				rvaAssign(&local.m_alternate, reinterpret_cast<Byte *>(sound) + 8);
			}
		}
	}

	if (local.m_current == 0 && local.m_alternate == 0)
		return;

	switch (*(int *)0x012ED5D8)
	{
	case 1:
		local.m_state.m_ready = local.m_current != 0 && rvaReady(local.m_current);
		break;
	case 2:
		local.m_state.m_ready = local.m_state.m_queryFlag;
		break;
	case 3:
		local.m_state.m_ready = 0;
		if (local.m_current != 0 && rvaReady(local.m_current))
			local.m_state.m_ready = 1;
		if (local.m_alternate != 0 && rvaReady(local.m_alternate))
			local.m_state.m_ready = 1;
		break;
	default:
		local.m_state.m_ready = 0;
		break;
	}

	Byte playing = (self->m_handleA >= 5 || self->m_handleB >= 5) ? 1 : 0;
	if (local.m_state.m_ready == playing)
		return;
	if (local.m_state.m_ready == 0)
	{
		rvaReleaseMapObject(this);
		return;
	}

	rvaHold(&self->m_audioInfo, &local.m_audioInfo);
	if (local.m_current != 0)
	{
		void *position = rvaEvent(this);
		rvaMakeEvent(local.m_event, &local.m_current, position, 0);
		self->m_handleA = TheAudioClientUpdate->addAudioEvent(local.m_event);
		rvaDestroyEvent(local.m_event);
		if (local.m_alternate != 0)
		{
			position = rvaEvent(this);
			rvaMakeEvent(local.m_event, &local.m_alternate, position, 0);
			self->m_handleB = TheAudioClientUpdate->addAudioEvent(local.m_event);
			rvaDestroyEvent(local.m_event);
		}
	}

	rvaReleaseMapObject(this);
	rvaReleaseCounted(local.m_alternate);
	rvaReleaseCounted(local.m_current);
	rvaReleaseCounted(local.m_audioInfo);
}
