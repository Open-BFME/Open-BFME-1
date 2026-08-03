// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift the retail AudioEventInfo hashtable resize MASM body into a C++ thunk.

class AsciiString
{
};

struct AudioEventInfo
{
};

namespace rts
{
template <class T>
struct hash
{
};

template <class T>
struct equal_to
{
};
}

namespace _STL
{
template <class First, class Second>
struct pair
{
};

template <class T>
struct _Select1st
{
};

template <class T>
class allocator
{
};

template <class Value, class Key, class Hash, class Extract, class Equal, class Alloc>
class hashtable
{
public:
    void resize(unsigned int);
};

template <class Value, class Key, class Hash, class Extract, class Equal, class Alloc>
__declspec(naked) void hashtable<Value, Key, Hash, Extract, Equal, Alloc>::resize(unsigned int)
{
    __asm {
        __emit 0x6a;
        __emit 0xff;
        __emit 0x68;
        __emit 0x58;
        __emit 0x8a;
        __emit 0xff;
        __emit 0x00;
        __emit 0x64;
        __emit 0xa1;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x50;
        __emit 0x64;
        __emit 0x89;
        __emit 0x25;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x83;
        __emit 0xec;
        __emit 0x18;
        __emit 0x8b;
        __emit 0x44;
        __emit 0x24;
        __emit 0x28;
        __emit 0x55;
        __emit 0x56;
        __emit 0x8b;
        __emit 0x71;
        __emit 0x04;
        __emit 0x57;
        __emit 0x8b;
        __emit 0x79;
        __emit 0x08;
        __emit 0x8d;
        __emit 0x69;
        __emit 0x04;
        __emit 0x2b;
        __emit 0xfe;
        __emit 0xc1;
        __emit 0xff;
        __emit 0x02;
        __emit 0x3b;
        __emit 0xc7;
        __emit 0x89;
        __emit 0x7c;
        __emit 0x24;
        __emit 0x14;
        __emit 0x0f;
        __emit 0x86;
        __emit 0x55;
        __emit 0x01;
        __emit 0x00;
        __emit 0x00;
        __emit 0x53;
        __emit 0x89;
        __emit 0x44;
        __emit 0x24;
        __emit 0x38;
        __emit 0x8b;
        __emit 0x44;
        __emit 0x24;
        __emit 0x38;
        __emit 0x33;
        __emit 0xdb;
        __emit 0x53;
        __emit 0x50;
        __emit 0x8d;
        __emit 0x4c;
        __emit 0x24;
        __emit 0x40;
        __emit 0x51;
        __emit 0x68;
        __emit 0xe0;
        __emit 0x58;
        __emit 0x07;
        __emit 0x01;
        __emit 0x68;
        __emit 0x70;
        __emit 0x58;
        __emit 0x07;
        __emit 0x01;
        __emit 0xe8;
        __emit 0x3f;
        __emit 0xce;
        __emit 0xf5;
        __emit 0xff;
        __emit 0x83;
        __emit 0xc4;
        __emit 0x14;
        __emit 0x3d;
        __emit 0xe0;
        __emit 0x58;
        __emit 0x07;
        __emit 0x01;
        __emit 0x75;
        __emit 0x0b;
        __emit 0xbe;
        __emit 0xfb;
        __emit 0xff;
        __emit 0xff;
        __emit 0xff;
        __emit 0x89;
        __emit 0x74;
        __emit 0x24;
        __emit 0x10;
        __emit 0xeb;
        __emit 0x08;
        __emit 0x8b;
        __emit 0x10;
        __emit 0x89;
        __emit 0x54;
        __emit 0x24;
        __emit 0x10;
        __emit 0x8b;
        __emit 0xf2;
        __emit 0x3b;
        __emit 0xf7;
        __emit 0x0f;
        __emit 0x86;
        __emit 0x0e;
        __emit 0x01;
        __emit 0x00;
        __emit 0x00;
        __emit 0x8d;
        __emit 0x44;
        __emit 0x24;
        __emit 0x38;
        __emit 0x50;
        __emit 0x8b;
        __emit 0xcd;
        __emit 0x89;
        __emit 0x5c;
        __emit 0x24;
        __emit 0x18;
        __emit 0xe8;
        __emit 0xd9;
        __emit 0x13;
        __emit 0xf5;
        __emit 0xff;
        __emit 0x50;
        __emit 0x8d;
        __emit 0x4c;
        __emit 0x24;
        __emit 0x18;
        __emit 0x51;
        __emit 0x56;
        __emit 0x8d;
        __emit 0x4c;
        __emit 0x24;
        __emit 0x28;
        __emit 0xe8;
        __emit 0x3d;
        __emit 0x7b;
        __emit 0xf6;
        __emit 0xff;
        __emit 0x3b;
        __emit 0xfb;
        __emit 0x89;
        __emit 0x5c;
        __emit 0x24;
        __emit 0x30;
        __emit 0x0f;
        __emit 0x86;
        __emit 0x84;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0xeb;
        __emit 0x03;
        __emit 0x8d;
        __emit 0x49;
        __emit 0x00;
        __emit 0x8b;
        __emit 0x45;
        __emit 0x00;
        __emit 0x8b;
        __emit 0x34;
        __emit 0x98;
        __emit 0x85;
        __emit 0xf6;
        __emit 0x74;
        __emit 0x70;
        __emit 0x8d;
        __emit 0x9b;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x8d;
        __emit 0x56;
        __emit 0x04;
        __emit 0x52;
        __emit 0x8d;
        __emit 0x4c;
        __emit 0x24;
        __emit 0x18;
        __emit 0xe8;
        __emit 0xd3;
        __emit 0xf2;
        __emit 0x7c;
        __emit 0x00;
        __emit 0x8b;
        __emit 0x4c;
        __emit 0x24;
        __emit 0x14;
        __emit 0x85;
        __emit 0xc9;
        __emit 0x74;
        __emit 0x05;
        __emit 0x83;
        __emit 0xc1;
        __emit 0x08;
        __emit 0xeb;
        __emit 0x05;
        __emit 0xb9;
        __emit 0x8b;
        __emit 0x38;
        __emit 0x07;
        __emit 0x01;
        __emit 0x8a;
        __emit 0x01;
        __emit 0x33;
        __emit 0xff;
        __emit 0x84;
        __emit 0xc0;
        __emit 0x74;
        __emit 0x10;
        __emit 0x0f;
        __emit 0xbe;
        __emit 0xc0;
        __emit 0x8d;
        __emit 0x3c;
        __emit 0xbf;
        __emit 0x03;
        __emit 0xf8;
        __emit 0x8a;
        __emit 0x41;
        __emit 0x01;
        __emit 0x41;
        __emit 0x84;
        __emit 0xc0;
        __emit 0x75;
        __emit 0xf0;
        __emit 0x8d;
        __emit 0x4c;
        __emit 0x24;
        __emit 0x14;
        __emit 0xe8;
        __emit 0x80;
        __emit 0xf0;
        __emit 0x7c;
        __emit 0x00;
        __emit 0x33;
        __emit 0xd2;
        __emit 0x8b;
        __emit 0xc7;
        __emit 0xf7;
        __emit 0x74;
        __emit 0x24;
        __emit 0x10;
        __emit 0x8b;
        __emit 0x0e;
        __emit 0x8b;
        __emit 0x45;
        __emit 0x00;
        __emit 0x89;
        __emit 0x0c;
        __emit 0x98;
        __emit 0x8b;
        __emit 0x44;
        __emit 0x24;
        __emit 0x1c;
        __emit 0x8b;
        __emit 0x0c;
        __emit 0x90;
        __emit 0x89;
        __emit 0x0e;
        __emit 0x89;
        __emit 0x34;
        __emit 0x90;
        __emit 0x8b;
        __emit 0x45;
        __emit 0x00;
        __emit 0x8b;
        __emit 0x34;
        __emit 0x98;
        __emit 0x85;
        __emit 0xf6;
        __emit 0x75;
        __emit 0x9a;
        __emit 0x8b;
        __emit 0x7c;
        __emit 0x24;
        __emit 0x18;
        __emit 0x43;
        __emit 0x3b;
        __emit 0xdf;
        __emit 0x72;
        __emit 0x81;
        __emit 0x8b;
        __emit 0x4d;
        __emit 0x00;
        __emit 0x85;
        __emit 0xc9;
        __emit 0x8b;
        __emit 0x54;
        __emit 0x24;
        __emit 0x1c;
        __emit 0x8b;
        __emit 0x44;
        __emit 0x24;
        __emit 0x20;
        __emit 0x89;
        __emit 0x55;
        __emit 0x00;
        __emit 0x8b;
        __emit 0x54;
        __emit 0x24;
        __emit 0x24;
        __emit 0x89;
        __emit 0x45;
        __emit 0x04;
        __emit 0x8b;
        __emit 0x45;
        __emit 0x08;
        __emit 0x89;
        __emit 0x55;
        __emit 0x08;
        __emit 0xc7;
        __emit 0x44;
        __emit 0x24;
        __emit 0x30;
        __emit 0xff;
        __emit 0xff;
        __emit 0xff;
        __emit 0xff;
        __emit 0x74;
        __emit 0x37;
        __emit 0x2b;
        __emit 0xc1;
        __emit 0xc1;
        __emit 0xf8;
        __emit 0x02;
        __emit 0xc1;
        __emit 0xe0;
        __emit 0x02;
        __emit 0x3d;
        __emit 0x80;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x76;
        __emit 0x1e;
        __emit 0x51;
        __emit 0xe8;
        __emit 0x85;
        __emit 0x95;
        __emit 0x7c;
        __emit 0x00;
        __emit 0x83;
        __emit 0xc4;
        __emit 0x04;
        __emit 0x5b;
        __emit 0x5f;
        __emit 0x5e;
        __emit 0x5d;
        __emit 0x8b;
        __emit 0x4c;
        __emit 0x24;
        __emit 0x18;
        __emit 0x64;
        __emit 0x89;
        __emit 0x0d;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x83;
        __emit 0xc4;
        __emit 0x24;
        __emit 0xc2;
        __emit 0x04;
        __emit 0x00;
        __emit 0x50;
        __emit 0x51;
        __emit 0xe8;
        __emit 0xa6;
        __emit 0x5c;
        __emit 0x77;
        __emit 0x00;
        __emit 0x83;
        __emit 0xc4;
        __emit 0x08;
        __emit 0x5b;
        __emit 0x8b;
        __emit 0x4c;
        __emit 0x24;
        __emit 0x24;
        __emit 0x5f;
        __emit 0x5e;
        __emit 0x5d;
        __emit 0x64;
        __emit 0x89;
        __emit 0x0d;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x83;
        __emit 0xc4;
        __emit 0x24;
        __emit 0xc2;
        __emit 0x04;
        __emit 0x00;
    }
}
}

typedef _STL::pair<const AsciiString, AudioEventInfo *> AudioEventInfoPair;
typedef _STL::hashtable<AudioEventInfoPair, AsciiString, rts::hash<AsciiString>, _STL::_Select1st<AudioEventInfoPair>, rts::equal_to<AsciiString>, _STL::allocator<AudioEventInfoPair> > AudioEventInfoHashtable;
template void AudioEventInfoHashtable::resize(unsigned int);
