// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/LadderPreferences.h
class LadderPref
{
public:
    LadderPref(const LadderPref &);
};

__declspec(naked) LadderPref::LadderPref(const LadderPref &)
{
    __asm _emit(0x6A);
    __asm _emit(0xFF);
    __asm _emit(0x68);
    __asm _emit(0x08);
    __asm _emit(0x75);
    __asm _emit(0xFF);
    __asm _emit(0x00);
    __asm _emit(0x64);
    __asm _emit(0xA1);
    __asm _emit(0x00);
    __asm _emit(0x00);
    __asm _emit(0x00);
    __asm _emit(0x00);
    __asm _emit(0x50);
    __asm _emit(0x64);
    __asm _emit(0x89);
    __asm _emit(0x25);
    __asm _emit(0x00);
    __asm _emit(0x00);
    __asm _emit(0x00);
    __asm _emit(0x00);
    __asm _emit(0x51);
    __asm _emit(0x56);
    __asm _emit(0x57);
    __asm _emit(0x8B);
    __asm _emit(0x7C);
    __asm _emit(0x24);
    __asm _emit(0x1C);
    __asm _emit(0x8B);
    __asm _emit(0xF1);
    __asm _emit(0x57);
    __asm _emit(0x89);
    __asm _emit(0x74);
    __asm _emit(0x24);
    __asm _emit(0x0C);
    __asm _emit(0xE8);
    __asm _emit(0xF8);
    __asm _emit(0xE7);
    __asm _emit(0x7D);
    __asm _emit(0x00);
    __asm _emit(0x8D);
    __asm _emit(0x47);
    __asm _emit(0x04);
    __asm _emit(0x50);
    __asm _emit(0x8D);
    __asm _emit(0x4E);
    __asm _emit(0x04);
    __asm _emit(0xC7);
    __asm _emit(0x44);
    __asm _emit(0x24);
    __asm _emit(0x18);
    __asm _emit(0x00);
    __asm _emit(0x00);
    __asm _emit(0x00);
    __asm _emit(0x00);
    __asm _emit(0xE8);
    __asm _emit(0x44);
    __asm _emit(0xDF);
    __asm _emit(0x7D);
    __asm _emit(0x00);
    __asm _emit(0x66);
    __asm _emit(0x8B);
    __asm _emit(0x4F);
    __asm _emit(0x08);
    __asm _emit(0x66);
    __asm _emit(0x89);
    __asm _emit(0x4E);
    __asm _emit(0x08);
    __asm _emit(0x8B);
    __asm _emit(0x57);
    __asm _emit(0x0C);
    __asm _emit(0x8B);
    __asm _emit(0x4C);
    __asm _emit(0x24);
    __asm _emit(0x0C);
    __asm _emit(0x89);
    __asm _emit(0x56);
    __asm _emit(0x0C);
    __asm _emit(0x5F);
    __asm _emit(0x8B);
    __asm _emit(0xC6);
    __asm _emit(0x5E);
    __asm _emit(0x64);
    __asm _emit(0x89);
    __asm _emit(0x0D);
    __asm _emit(0x00);
    __asm _emit(0x00);
    __asm _emit(0x00);
    __asm _emit(0x00);
    __asm _emit(0x83);
    __asm _emit(0xC4);
    __asm _emit(0x10);
    __asm _emit(0xC2);
    __asm _emit(0x04);
    __asm _emit(0x00);
}
