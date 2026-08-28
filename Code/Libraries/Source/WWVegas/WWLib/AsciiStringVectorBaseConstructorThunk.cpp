// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
};

namespace _STL
{
template <class Type>
class allocator
{
};

template <class Type, class Allocator>
class _Vector_base
{
public:
    _Vector_base(unsigned int, const Allocator &);
};

__declspec(naked) _Vector_base<AsciiString, allocator<AsciiString> >::_Vector_base(
    unsigned int, const allocator<AsciiString> &)
{
    __asm {
        __emit 0x8b;
        __emit 0x44;
        __emit 0x24;
        __emit 0x08;
        __emit 0x53;
        __emit 0x56;
        __emit 0x8b;
        __emit 0xf1;
        __emit 0x57;
        __emit 0x6a;
        __emit 0x00;
        __emit 0x8d;
        __emit 0x7e;
        __emit 0x08;
        __emit 0x50;
        __emit 0x8b;
        __emit 0xcf;
        __emit 0xc7;
        __emit 0x06;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0xc7;
        __emit 0x46;
        __emit 0x04;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0xe8;
        __emit 0xab;
        __emit 0x72;
        __emit 0xe4;
        __emit 0xff;
        __emit 0x8b;
        __emit 0x5c;
        __emit 0x24;
        __emit 0x10;
        __emit 0x85;
        __emit 0xdb;
        __emit 0x74;
        __emit 0x22;
        __emit 0x8d;
        __emit 0x0c;
        __emit 0x9d;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x51;
        __emit 0xe8;
        __emit 0x9e;
        __emit 0xef;
        __emit 0xe6;
        __emit 0xff;
        __emit 0x8d;
        __emit 0x14;
        __emit 0x98;
        __emit 0x83;
        __emit 0xc4;
        __emit 0x04;
        __emit 0x89;
        __emit 0x06;
        __emit 0x89;
        __emit 0x46;
        __emit 0x04;
        __emit 0x89;
        __emit 0x17;
        __emit 0x5f;
        __emit 0x8b;
        __emit 0xc6;
        __emit 0x5e;
        __emit 0x5b;
        __emit 0xc2;
        __emit 0x08;
        __emit 0x00;
        __emit 0x33;
        __emit 0xc0;
        __emit 0x8d;
        __emit 0x14;
        __emit 0x98;
        __emit 0x89;
        __emit 0x06;
        __emit 0x89;
        __emit 0x46;
        __emit 0x04;
        __emit 0x89;
        __emit 0x17;
        __emit 0x5f;
        __emit 0x8b;
        __emit 0xc6;
        __emit 0x5e;
        __emit 0x5b;
        __emit 0xc2;
        __emit 0x08;
        __emit 0x00;
    }
}
}
