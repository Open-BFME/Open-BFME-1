// Ninety-four 8-byte __thiscall bodies of the single shape
//
//     push <IMM8> / call <REL32> / ret
//
// WHAT THE BYTES SHOW.  One small constant is pushed, one call is made, and the
// body returns without adjusting esp -- so the callee pops the argument, and
// ecx is neither set up nor saved, so it is passed through untouched.  That is
// `void C::go() { handle(K); }` where handle is a __thiscall member reached on
// the SAME `this`: a one-argument forwarder that hard-codes its argument.
// A __cdecl callee is excluded by the missing `add esp,4`.
//
// ONE DOMINANT AXIS: the constant. Eighty-seven of the ninety-four call the
// same target, 0x0001BFD1, with a different constant each time, and the
// constants run 0x00..0x52 nearly contiguously over a block of bodies laid out
// 16 bytes apart at 0x005A6CE0..0x005A7330 -- a generated table of per-index
// accessors, one entry per index. The remaining seven call six other targets.
// The gaps in the run (0x03, 0x04, 0x09, 0x0A, ...) are indices whose body is
// not of this shape, not missing rows.
//
// The opaque roots/bases remain ABI storage views, not recovered inheritance.
// Existing public native methods below receive the same unadjusted this; the
// one protected shadow site has a separately checked one-word member view.
//
// Root identities remain address-derived; binding a known callee does not name them.

// The Zero Hour header has getAudio, not BFME's existing getSound interface.
class AudioEventRTS;
class ThingTemplate
{
public:
    const AudioEventRTS *getSound(int index) const;
};

class LargeGroupBonusUpdate
{
public:
    void notify(int index);
};

class Object;
class SimpleObjectIterator
{
public:
    Object *firstWithNumeric(float *numeric);
};

class IndexedAudioEvent006B0210
{
public:
    void select(int index);
};

class W3DVolumetricShadow
{
protected:
    void Update(bool forceUpdate);
};

extern "C" void __identifier("?Update@W3DVolumetricShadow@@IAEX_N@Z")();

#define BFME_INDEX_FORWARD_CALLEE( ADDR )                                 \
	class Gen##ADDR                                                        \
	{                                                                      \
	public:                                                                \
		void handle( int index );                                           \
	};

#define BFME_INDEX_FORWARDER( NAME, CALLEE, CALL )                       \
	class NAME : public CALLEE                                             \
	{                                                                      \
	public:                                                                \
		void go();                                                          \
	};                                                                     \
	void NAME::go()                                                        \
	{                                                                      \
		CALL;                                                               \
	}

BFME_INDEX_FORWARD_CALLEE( 0001BFD1 )
BFME_INDEX_FORWARD_CALLEE( 0003415D )
BFME_INDEX_FORWARD_CALLEE( 00038951 )
BFME_INDEX_FORWARD_CALLEE( 000398C9 )
BFME_INDEX_FORWARD_CALLEE( 00039BD5 )
BFME_INDEX_FORWARD_CALLEE( 0003D172 )
BFME_INDEX_FORWARD_CALLEE( 00044A62 )

BFME_INDEX_FORWARDER( Rva00297890, Gen0003415D, reinterpret_cast<LargeGroupBonusUpdate *>(this)->notify(0x0) )
BFME_INDEX_FORWARDER( Rva005265F0, Gen00038951, handle(0x0) )
BFME_INDEX_FORWARDER( Rva006B0400, Gen00044A62, reinterpret_cast<IndexedAudioEvent006B0210 *>(this)->select(0x1) )
BFME_INDEX_FORWARDER( Rva000B5FC0, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x57) )
BFME_INDEX_FORWARDER( Rva0016A040, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x56) )
BFME_INDEX_FORWARDER( Rva001840D0, Gen00039BD5, handle(0x0) )
BFME_INDEX_FORWARDER( Rva001BD700, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x6B) )
BFME_INDEX_FORWARDER( Rva001BD710, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x6C) )
BFME_INDEX_FORWARDER( Rva001DE030, Gen000398C9, reinterpret_cast<SimpleObjectIterator *>(this)->firstWithNumeric(0) )
BFME_INDEX_FORWARDER( Rva0020DCD0, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x63) )
BFME_INDEX_FORWARDER( Rva0020DCE0, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x64) )
BFME_INDEX_FORWARDER( Rva0020DCF0, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x67) )
BFME_INDEX_FORWARDER( Rva0020DD00, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x68) )
BFME_INDEX_FORWARDER( Rva0020DD10, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x69) )
BFME_INDEX_FORWARDER( Rva002205A0, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x65) )
BFME_INDEX_FORWARDER( Rva002205B0, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x66) )
BFME_INDEX_FORWARDER( Rva002205C0, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x6A) )
BFME_INDEX_FORWARDER( Rva002AC040, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x60) )
BFME_INDEX_FORWARDER( Rva002AC050, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x61) )
BFME_INDEX_FORWARDER( Rva0036B970, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0xD) )
BFME_INDEX_FORWARDER( Rva005A6CE0, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x0) )
BFME_INDEX_FORWARDER( Rva005A6CF0, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x1) )
BFME_INDEX_FORWARDER( Rva005A6D00, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x2) )
BFME_INDEX_FORWARDER( Rva005A6D70, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x5) )
BFME_INDEX_FORWARDER( Rva005A6D80, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x6) )
BFME_INDEX_FORWARDER( Rva005A6D90, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x7) )
BFME_INDEX_FORWARDER( Rva005A6DA0, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x8) )
BFME_INDEX_FORWARDER( Rva005A6E10, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0xB) )
BFME_INDEX_FORWARDER( Rva005A6E20, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0xC) )
BFME_INDEX_FORWARDER( Rva005A6E30, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0xE) )
BFME_INDEX_FORWARDER( Rva005A6E40, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0xF) )
BFME_INDEX_FORWARDER( Rva005A6E50, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x10) )
BFME_INDEX_FORWARDER( Rva005A6E60, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x11) )
BFME_INDEX_FORWARDER( Rva005A6E70, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x12) )
BFME_INDEX_FORWARDER( Rva005A6E80, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x13) )
BFME_INDEX_FORWARDER( Rva005A6E90, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x14) )
BFME_INDEX_FORWARDER( Rva005A6EA0, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x15) )
BFME_INDEX_FORWARDER( Rva005A6EB0, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x16) )
BFME_INDEX_FORWARDER( Rva005A6EC0, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x17) )
BFME_INDEX_FORWARDER( Rva005A6ED0, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x18) )
BFME_INDEX_FORWARDER( Rva005A6EE0, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x19) )
BFME_INDEX_FORWARDER( Rva005A6EF0, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x1A) )
BFME_INDEX_FORWARDER( Rva005A6F00, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x1B) )
BFME_INDEX_FORWARDER( Rva005A6F10, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x1C) )
BFME_INDEX_FORWARDER( Rva005A6F20, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x1D) )
BFME_INDEX_FORWARDER( Rva005A6F30, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x1E) )
BFME_INDEX_FORWARDER( Rva005A6F40, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x1F) )
BFME_INDEX_FORWARDER( Rva005A6F50, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x20) )
BFME_INDEX_FORWARDER( Rva005A6F60, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x21) )
BFME_INDEX_FORWARDER( Rva005A6FA0, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x23) )
BFME_INDEX_FORWARDER( Rva005A6FB0, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x24) )
BFME_INDEX_FORWARDER( Rva005A6FC0, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x25) )
BFME_INDEX_FORWARDER( Rva005A6FD0, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x26) )
BFME_INDEX_FORWARDER( Rva005A6FE0, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x27) )
BFME_INDEX_FORWARDER( Rva005A6FF0, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x28) )
BFME_INDEX_FORWARDER( Rva005A7000, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x29) )
BFME_INDEX_FORWARDER( Rva005A7010, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x2A) )
BFME_INDEX_FORWARDER( Rva005A7020, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x2B) )
BFME_INDEX_FORWARDER( Rva005A7090, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x2E) )
BFME_INDEX_FORWARDER( Rva005A70A0, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x2F) )
BFME_INDEX_FORWARDER( Rva005A70B0, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x30) )
BFME_INDEX_FORWARDER( Rva005A70C0, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x31) )
BFME_INDEX_FORWARDER( Rva005A7130, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x34) )
BFME_INDEX_FORWARDER( Rva005A7140, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x35) )
BFME_INDEX_FORWARDER( Rva005A7150, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x36) )
BFME_INDEX_FORWARDER( Rva005A7160, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x37) )
BFME_INDEX_FORWARDER( Rva005A7170, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x38) )
BFME_INDEX_FORWARDER( Rva005A7180, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x39) )
BFME_INDEX_FORWARDER( Rva005A7190, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x3A) )
BFME_INDEX_FORWARDER( Rva005A71A0, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x3B) )
BFME_INDEX_FORWARDER( Rva005A71B0, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x3C) )
BFME_INDEX_FORWARDER( Rva005A71C0, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x3D) )
BFME_INDEX_FORWARDER( Rva005A71D0, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x3E) )
BFME_INDEX_FORWARDER( Rva005A71E0, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x3F) )
BFME_INDEX_FORWARDER( Rva005A71F0, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x40) )
BFME_INDEX_FORWARDER( Rva005A7200, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x41) )
BFME_INDEX_FORWARDER( Rva005A7210, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x42) )
BFME_INDEX_FORWARDER( Rva005A7220, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x43) )
BFME_INDEX_FORWARDER( Rva005A7230, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x44) )
BFME_INDEX_FORWARDER( Rva005A7240, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x45) )
BFME_INDEX_FORWARDER( Rva005A7250, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x46) )
BFME_INDEX_FORWARDER( Rva005A7260, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x47) )
BFME_INDEX_FORWARDER( Rva005A7270, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x48) )
BFME_INDEX_FORWARDER( Rva005A7280, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x49) )
BFME_INDEX_FORWARDER( Rva005A7290, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x4A) )
BFME_INDEX_FORWARDER( Rva005A72D0, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x4C) )
BFME_INDEX_FORWARDER( Rva005A72E0, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x4D) )
BFME_INDEX_FORWARDER( Rva005A72F0, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x4E) )
BFME_INDEX_FORWARDER( Rva005A7300, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x4F) )
BFME_INDEX_FORWARDER( Rva005A7310, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x50) )
BFME_INDEX_FORWARDER( Rva005A7320, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x51) )
BFME_INDEX_FORWARDER( Rva005A7330, Gen0001BFD1, reinterpret_cast<const ThingTemplate *>(this)->getSound(0x52) )
BFME_INDEX_FORWARDER( Rva006B03F0, Gen00044A62, reinterpret_cast<IndexedAudioEvent006B0210 *>(this)->select(0x0) )
class Rva007C0510 : public Gen0003D172
{
public:
    void go();
};

void Rva007C0510::go()
{
    union { void (*code)(); void (W3DVolumetricShadow::*member)(bool); } update = {
        &__identifier("?Update@W3DVolumetricShadow@@IAEX_N@Z") };
    typedef char ShadowForwarderPointersAreOneWord[(sizeof(update) == 4 && sizeof(update.code) == 4 && sizeof(update.member) == 4) ? 1 : -1];
    (reinterpret_cast<W3DVolumetricShadow *>(this)->*update.member)(true);
}

// A word store in the same retail run as Rva0016A040. BFME 2 donor:
// Code/GameEngine/Source/Common/Audio/AudioEventInfoPriority.cpp, 0x0041FDEE.
// No caller proves this receiver or field identity, so retain its address.
class Rva00169FF0
{
public:
    void storeWord(unsigned int value);
private:
    char m_at00[0x40];
    unsigned int m_at40;
};

void Rva00169FF0::storeWord(unsigned int value)
{
    m_at40 = value;
}

// BFME 2 donor CallForwarders8B.cpp: one constant-argument member call.
// Retail preserves this and returns getSound's pointer with slot 0x53.
class Rva0016A010 : public ThingTemplate
{
public:
    const AudioEventRTS *get() const;
};

const AudioEventRTS *Rva0016A010::get() const
{
    return getSound(0x53);
}

// BFME 2 CallForwarders8B.cpp pattern; separately carved sound slot 0x54.
class Rva0016A020 : public ThingTemplate
{
public:
    const AudioEventRTS *get() const;
};

const AudioEventRTS *Rva0016A020::get() const
{
    return getSound(0x54);
}

// BFME 2 CallForwarders8B.cpp pattern; independently carved sound slot 0x55.
class Rva0016A030 : public ThingTemplate
{
public:
    const AudioEventRTS *get() const;
};

const AudioEventRTS *Rva0016A030::get() const
{
    return getSound(0x55);
}

// BFME 2 DispByteFieldGetters.cpp shape. Only AL is defined by retail;
// retain the opaque receiver and independently witnessed displacement.
class Rva0016A000
{
public:
    unsigned char get() const;
private:
    char m_at00[0x29D];
    unsigned char m_at29D;
};

unsigned char Rva0016A000::get() const
{
    return m_at29D;
}

// BFME 2 DispDwordFieldGetters.cpp shape; retail supplies offset 0x208.
class Rva00169F70
{
public:
    int get() const;
private:
    char m_at00[0x208];
    int m_at208;
};

int Rva00169F70::get() const
{
    return m_at208;
}

// BFME 2 AudioEventInfoPriority.cpp assignment shape; no enum identity
// is inferred for this independently witnessed four-byte field.
class Rva00169FB0
{
public:
    void storeWord(unsigned int value);
private:
    char m_at00[0x3A4];
    unsigned int m_at3A4;
};

void Rva00169FB0::storeWord(unsigned int value)
{
    m_at3A4 = value;
}

// BFME 2 VtableSlotBodiesR3.cpp signed-word predicate shape. BFME 1
// clears the upper return bytes, so this view returns an int 0 or 1.
class Rva00169F50
{
public:
    int isPositive() const;
private:
    char m_at00[0x1A0];
    int m_at1A0;
};

int Rva00169F50::isPositive() const
{
    return m_at1A0 > 0;
}

// Unreferenced leaf getters between 0x00169F80 and 0x00169FE0: each is a
// REL32-carved complete body (ret then int3) reached only from its own ILT
// entry, so no owner is witnessed and every name keeps its address.
class Rva00169F80
{
public:
    int get() const;
private:
    char m_at00[0x208];
    int m_at208;
};

int Rva00169F80::get() const
{
    return m_at208;
}

class Rva00169F90
{
public:
    unsigned char get() const;
private:
    char m_at00[0x1F5];
    unsigned char m_at1F5;
};

unsigned char Rva00169F90::get() const
{
    return m_at1F5;
}

class Rva00169FA0
{
public:
    int get() const;
private:
    char m_at00[0x1EC];
    int m_at1EC;
};

int Rva00169FA0::get() const
{
    return m_at1EC;
}

class Rva00169FC0
{
public:
    int get() const;
private:
    char m_at00[0x3A4];
    int m_at3A4;
};

int Rva00169FC0::get() const
{
    return m_at3A4;
}

class Rva00169FD0
{
public:
    int get() const;
private:
    char m_at00[0x1F8];
    int m_at1F8;
};

int Rva00169FD0::get() const
{
    return m_at1F8;
}

class Rva00169FE0
{
public:
    int get() const;
private:
    char m_at00[0x40];
    int m_at40;
};

int Rva00169FE0::get() const
{
    return m_at40;
}
