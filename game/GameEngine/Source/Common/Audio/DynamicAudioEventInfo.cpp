// stlport
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /Igame/GameEngine/Source/Common/System /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// DynamicAudioEventInfo::xferNoName and its native override forwarders.
// The vendor header supplies real method declarations only; BFME's AudioEventInfo
// base is 0x98 bytes, so its different ZH data layout must not be dereferenced.
// This address-qualified physical view records only independently witnessed
// fields. The five base-setter source spellings are unknown and stay RVA-named.
// See targets/game/reverse/identity_evidence/000b5710-dynamic-audio-xfer.md.
// Original dictionary literals and constructor/copy/destructor chains prove
// the audio owner; INI fields and Xfer type tags independently prove Real/enum
// argument types. The no-argument Gen forwarders were ABI-misidentified.

#include "Common/DynamicAudioEventInfo.h"
#include "xfer.h"
// Receiver/layout view; never constructed and never emits an audio vtable.
class Rva000B5710Owner
{
public:
    void Rva000AF9A0(float);
    void Rva000AF9B0(float);
    void Rva000AF9C0(float);
    void Rva000AF9D0(float);
    void Rva000AF9E0(AudioPriority);

    unsigned char pad00[0x10];
    float at10;                         // Volume
    unsigned char pad14[4];
    float at18;                         // MinVolume
    unsigned char pad1c[0x18];
    AudioPriority at34;
    unsigned char pad38[4];
    unsigned char at3c;                  // Low byte of Control
    unsigned char pad3d[0x37];
    float at74, at78;                    // MinRange / MaxRange
    unsigned char pad7c[0x1c];
    unsigned int flags;                 // Dynamic override bits at +0x98
};

// Same declaration as the existing Rva000AF960FlagWord.cpp provider.
struct Rva000AF960Object
{
    unsigned char m_prefix[0x3c];
    unsigned int m_flags;

    void addFlags(unsigned int flags);
    void removeFlags(unsigned int flags);
};

__declspec(noinline) void Rva000B5710Owner::Rva000AF9A0(float value)
{
    at10 = value;
}

__declspec(noinline) void Rva000B5710Owner::Rva000AF9B0(float value)
{
    at18 = value;
}

__declspec(noinline) void Rva000B5710Owner::Rva000AF9C0(float value)
{
    at74 = value;
}

__declspec(noinline) void Rva000B5710Owner::Rva000AF9D0(float value)
{
    at78 = value;
}

__declspec(noinline) void Rva000B5710Owner::Rva000AF9E0(AudioPriority value)
{
    at34 = value;
}

void DynamicAudioEventInfo::xferNoName(Xfer *x)
{
    Rva000B5710Owner &info = *reinterpret_cast<Rva000B5710Owner *>(this);
    {
        Xfer::Version version = {{1, 1}};
        *x == version;
    }
    {
        if (x->IsLoading()) {
            unsigned int value;
            *x == *reinterpret_cast<unsigned char *>(&value);
            // Only the byte written by the transfer is initialized.
            value = *reinterpret_cast<unsigned char *>(&value);
            if (value & 1u) info.flags |= 1u; else info.flags &= ~1u;
            if (value & 2u) info.flags |= 2u; else info.flags &= ~2u;
            if (value & 4u) info.flags |= 4u; else info.flags &= ~4u;
            if (value & 8u) info.flags |= 8u; else info.flags &= ~8u;
            if (value & 16u) info.flags |= 16u; else info.flags &= ~16u;
            if (value & 32u) info.flags |= 32u; else info.flags &= ~32u;
            if (value & 64u) info.flags |= 64u; else info.flags &= ~64u;
            if (value & 128u) info.flags |= 128u; else info.flags &= ~128u;
        } else {
            unsigned char value = 0;
            if (info.flags & 1) value = 1;
            if (info.flags & 2) value |= 2;
            if (info.flags & 4) value |= 4;
            if (info.flags & 8) value |= 8;
            if (info.flags & 16) value |= 16;
            if (info.flags & 32) value |= 32;
            if (info.flags & 64) value |= 64;
            if (info.flags & 128) value |= 128;
            *x == value;
        }
    }
    if (info.flags & 2) {
        bool b = (info.at3c & 1) != 0;
        *x == b;
        if (x->IsLoading()) {
            if (b)
                reinterpret_cast<Rva000AF960Object *>(this)->addFlags(1);
            else
                reinterpret_cast<Rva000AF960Object *>(this)->removeFlags(1);
        }
    }
    if (info.flags & 8) {
        float v = info.at10;
        *x == v;
        info.Rva000AF9A0(v);
    }
    if (info.flags & 16) {
        float v = info.at18;
        *x == v;
        info.Rva000AF9B0(v);
    }
    if (info.flags & 32) {
        float v = info.at74;
        *x == v;
        info.Rva000AF9C0(v);
    }
    if (info.flags & 64) {
        float v = info.at78;
        *x == v;
        info.Rva000AF9D0(v);
    }
    if (info.flags & 128) {
        unsigned char v = info.at34;
        *x == v;
        info.Rva000AF9E0((AudioPriority)v);
    }
}

void DynamicAudioEventInfo::overrideVolume(float value)
{
    Rva000B5710Owner &info = *reinterpret_cast<Rva000B5710Owner *>(this);
    info.flags |= 0x8;
    info.Rva000AF9A0(value);
}

void DynamicAudioEventInfo::overrideMinVolume(float value)
{
    Rva000B5710Owner &info = *reinterpret_cast<Rva000B5710Owner *>(this);
    info.flags |= 0x10;
    info.Rva000AF9B0(value);
}

void DynamicAudioEventInfo::overrideMinRange(float value)
{
    Rva000B5710Owner &info = *reinterpret_cast<Rva000B5710Owner *>(this);
    info.flags |= 0x20;
    info.Rva000AF9C0(value);
}

void DynamicAudioEventInfo::overrideMaxRange(float value)
{
    Rva000B5710Owner &info = *reinterpret_cast<Rva000B5710Owner *>(this);
    info.flags |= 0x40;
    info.Rva000AF9D0(value);
}

void DynamicAudioEventInfo::overridePriority(AudioPriority value)
{
    Rva000B5710Owner &info = *reinterpret_cast<Rva000B5710Owner *>(this);
    info.flags |= 0x80;
    info.Rva000AF9E0(value);
}
