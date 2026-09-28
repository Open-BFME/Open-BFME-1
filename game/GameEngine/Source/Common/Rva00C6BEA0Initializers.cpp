// cl: /O2 /MD
// Address-derived initialization routine: INT3 / MOV [absolute], address / RET / INT3.
extern void *Rva00EF6C90;
extern void **Rva00EF6C98;
void Rva00C6BED0() { Rva00EF6C98 = &Rva00EF6C90; }

namespace FXParticleSystem {
template<int N> struct DefaultModuleKey {
private: static const char *GetValue();
public: static const char *Read() { return GetValue(); }
};
template<int N> struct DefaultModuleName {
private: static const char *GetValue();
public: static const char *Read() { return GetValue(); }
};
}
extern "C" int __cdecl atexit(void (__cdecl *)());
void Rva00C70430SetGlobal();


// 0x00C6BEA0: independent INT3-bounded initializer.
void Rva00C6BEA0() { atexit(Rva00C70430SetGlobal); }


// 0x00C6BEB0: independent INT3-bounded initializer.
void Rva00C6BEB0() { Rva00EF6C90 = (void *)FXParticleSystem::DefaultModuleKey<6>::Read(); }

extern void *Rva00EF6C94;
// 0x00C6BEC0: independent INT3-bounded initializer.
void Rva00C6BEC0() { Rva00EF6C94 = (void *)FXParticleSystem::DefaultModuleName<6>::Read(); }

extern void *Rva00EF6C9C;
// 0x00C6BEE0: independent INT3-bounded initializer.
void Rva00C6BEE0() { Rva00EF6C9C = (void *)&Rva00EF6C94; }

extern void *Rva00EF6CA0;
extern char Rva00D139F4;
// 0x00C6BEF0: independent INT3-bounded initializer.
void Rva00C6BEF0() { Rva00EF6CA0 = (void *)&Rva00D139F4; }

extern void *Rva00EF6CA4;
extern char Rva00D139F8;
// 0x00C6BF00: independent INT3-bounded initializer.
void Rva00C6BF00() { Rva00EF6CA4 = (void *)&Rva00D139F8; }

extern void *Rva00EF6CA8;
extern char Rva00D1375C;
// 0x00C6BF10: independent INT3-bounded initializer.
void Rva00C6BF10() { Rva00EF6CA8 = (void *)&Rva00D1375C; }

extern void *Rva00EF6CAC;
extern char Rva00D13760;
// 0x00C6BF20: independent INT3-bounded initializer.
void Rva00C6BF20() { Rva00EF6CAC = (void *)&Rva00D13760; }

extern void *Rva00EF6CB0;
extern char Rva00D13540;
// 0x00C6BF30: independent INT3-bounded initializer.
void Rva00C6BF30() { Rva00EF6CB0 = (void *)&Rva00D13540; }

extern void *Rva00EF6CB4;
extern char Rva00D13544;
// 0x00C6BF40: independent INT3-bounded initializer.
void Rva00C6BF40() { Rva00EF6CB4 = (void *)&Rva00D13544; }

extern void *Rva00EF6CB8;
extern char Rva00D13798;
// 0x00C6BF50: independent INT3-bounded initializer.
void Rva00C6BF50() { Rva00EF6CB8 = (void *)&Rva00D13798; }

extern void *Rva00EF6CBC;
extern char Rva00D1379C;
// 0x00C6BF60: independent INT3-bounded initializer.
void Rva00C6BF60() { Rva00EF6CBC = (void *)&Rva00D1379C; }

extern void *Rva00EF6CC0;
extern char Rva00D13670;
// 0x00C6BF70: independent INT3-bounded initializer.
void Rva00C6BF70() { Rva00EF6CC0 = (void *)&Rva00D13670; }

extern void *Rva00EF6CC4;
extern char Rva00D13674;
// 0x00C6BF80: independent INT3-bounded initializer.
void Rva00C6BF80() { Rva00EF6CC4 = (void *)&Rva00D13674; }

extern void *Rva00EF6CC8;
// 0x00C6BF90: independent INT3-bounded initializer.
void Rva00C6BF90() { Rva00EF6CC8 = (void *)FXParticleSystem::DefaultModuleKey<1>::Read(); }

extern void *Rva00EF6CCC;
// 0x00C6BFA0: independent INT3-bounded initializer.
void Rva00C6BFA0() { Rva00EF6CCC = (void *)FXParticleSystem::DefaultModuleName<1>::Read(); }

extern void *Rva00EF6CD0;
// 0x00C6BFB0: independent INT3-bounded initializer.
void Rva00C6BFB0() { Rva00EF6CD0 = (void *)&Rva00EF6CC8; }

extern void *Rva00EF6CD4;
// 0x00C6BFC0: independent INT3-bounded initializer.
void Rva00C6BFC0() { Rva00EF6CD4 = (void *)&Rva00EF6CCC; }

extern void *Rva00EF6CD8;
// 0x00C6BFD0: independent INT3-bounded initializer.
void Rva00C6BFD0() { Rva00EF6CD8 = (void *)FXParticleSystem::DefaultModuleKey<0>::Read(); }

extern void *Rva00EF6CDC;
// 0x00C6BFE0: independent INT3-bounded initializer.
void Rva00C6BFE0() { Rva00EF6CDC = (void *)FXParticleSystem::DefaultModuleName<0>::Read(); }

extern void *Rva00EF6CE0;
// 0x00C6BFF0: independent INT3-bounded initializer.
void Rva00C6BFF0() { Rva00EF6CE0 = (void *)&Rva00EF6CD8; }

extern void *Rva00EF6CE4;
// 0x00C6C000: independent INT3-bounded initializer.
void Rva00C6C000() { Rva00EF6CE4 = (void *)&Rva00EF6CDC; }

extern void *Rva00EF6CE8;
// 0x00C6C010: independent INT3-bounded initializer.
void Rva00C6C010() { Rva00EF6CE8 = (void *)FXParticleSystem::DefaultModuleKey<3>::Read(); }

extern void *Rva00EF6CEC;
// 0x00C6C020: independent INT3-bounded initializer.
void Rva00C6C020() { Rva00EF6CEC = (void *)FXParticleSystem::DefaultModuleName<3>::Read(); }

extern void *Rva00EF6CF0;
// 0x00C6C030: independent INT3-bounded initializer.
void Rva00C6C030() { Rva00EF6CF0 = (void *)&Rva00EF6CE8; }

extern void *Rva00EF6CF4;
// 0x00C6C040: independent INT3-bounded initializer.
void Rva00C6C040() { Rva00EF6CF4 = (void *)&Rva00EF6CEC; }

extern void *Rva00EF6CF8;
// 0x00C6C050: independent INT3-bounded initializer.
void Rva00C6C050() { Rva00EF6CF8 = (void *)FXParticleSystem::DefaultModuleKey<2>::Read(); }

extern void *Rva00EF6CFC;
// 0x00C6C060: independent INT3-bounded initializer.
void Rva00C6C060() { Rva00EF6CFC = (void *)FXParticleSystem::DefaultModuleName<2>::Read(); }

extern void *Rva00EF6D00;
// 0x00C6C070: independent INT3-bounded initializer.
void Rva00C6C070() { Rva00EF6D00 = (void *)&Rva00EF6CF8; }

extern void *Rva00EF6D04;
// 0x00C6C080: independent INT3-bounded initializer.
void Rva00C6C080() { Rva00EF6D04 = (void *)&Rva00EF6CFC; }

extern void *Rva00EF6D08;
// 0x00C6C090: independent INT3-bounded initializer.
void Rva00C6C090() { Rva00EF6D08 = (void *)FXParticleSystem::DefaultModuleKey<7>::Read(); }

extern void *Rva00EF6D0C;
// 0x00C6C0A0: independent INT3-bounded initializer.
void Rva00C6C0A0() { Rva00EF6D0C = (void *)FXParticleSystem::DefaultModuleName<7>::Read(); }

extern void *Rva00EF6D10;
// 0x00C6C0B0: independent INT3-bounded initializer.
void Rva00C6C0B0() { Rva00EF6D10 = (void *)&Rva00EF6D08; }

extern void *Rva00EF6D14;
// 0x00C6C0C0: independent INT3-bounded initializer.
void Rva00C6C0C0() { Rva00EF6D14 = (void *)&Rva00EF6D0C; }

extern void *Rva00EF6D18;
extern char Rva00D143E8;
// 0x00C6C0D0: independent INT3-bounded initializer.
void Rva00C6C0D0() { Rva00EF6D18 = (void *)&Rva00D143E8; }

extern void *Rva00EF6D1C;
extern char Rva00D143EC;
// 0x00C6C0E0: independent INT3-bounded initializer.
void Rva00C6C0E0() { Rva00EF6D1C = (void *)&Rva00D143EC; }

extern void *Rva00EF6D20;
extern char Rva00D149E0;
// 0x00C6C0F0: independent INT3-bounded initializer.
void Rva00C6C0F0() { Rva00EF6D20 = (void *)&Rva00D149E0; }

extern void *Rva00EF6D24;
extern char Rva00D149E4;
// 0x00C6C100: independent INT3-bounded initializer.
void Rva00C6C100() { Rva00EF6D24 = (void *)&Rva00D149E4; }

extern void *Rva00EF6D28;
extern char Rva00D144B4;
// 0x00C6C110: independent INT3-bounded initializer.
void Rva00C6C110() { Rva00EF6D28 = (void *)&Rva00D144B4; }

extern void *Rva00EF6D2C;
extern char Rva00D144B8;
// 0x00C6C120: independent INT3-bounded initializer.
void Rva00C6C120() { Rva00EF6D2C = (void *)&Rva00D144B8; }

extern void *Rva00EF6D30;
extern char Rva00D13EF8;
// 0x00C6C130: independent INT3-bounded initializer.
void Rva00C6C130() { Rva00EF6D30 = (void *)&Rva00D13EF8; }

extern void *Rva00EF6D34;
extern char Rva00D13EFC;
// 0x00C6C140: independent INT3-bounded initializer.
void Rva00C6C140() { Rva00EF6D34 = (void *)&Rva00D13EFC; }

extern void *Rva00EF6D38;
extern char Rva00D14088;
// 0x00C6C150: independent INT3-bounded initializer.
void Rva00C6C150() { Rva00EF6D38 = (void *)&Rva00D14088; }

extern void *Rva00EF6D3C;
extern char Rva00D1408C;
// 0x00C6C160: independent INT3-bounded initializer.
void Rva00C6C160() { Rva00EF6D3C = (void *)&Rva00D1408C; }

extern void *Rva00EF6D40;
extern char Rva00D13D7C;
// 0x00C6C170: independent INT3-bounded initializer.
void Rva00C6C170() { Rva00EF6D40 = (void *)&Rva00D13D7C; }

extern void *Rva00EF6D44;
extern char Rva00D13D80;
// 0x00C6C180: independent INT3-bounded initializer.
void Rva00C6C180() { Rva00EF6D44 = (void *)&Rva00D13D80; }

extern void *Rva00EF6D48;
extern char Rva00D13B3C;
// 0x00C6C190: independent INT3-bounded initializer.
void Rva00C6C190() { Rva00EF6D48 = (void *)&Rva00D13B3C; }

extern void *Rva00EF6D4C;
extern char Rva00D13B40;
// 0x00C6C1A0: independent INT3-bounded initializer.
void Rva00C6C1A0() { Rva00EF6D4C = (void *)&Rva00D13B40; }

extern void *Rva00EF6D50;
extern char Rva00D13F8C;
// 0x00C6C1B0: independent INT3-bounded initializer.
void Rva00C6C1B0() { Rva00EF6D50 = (void *)&Rva00D13F8C; }

extern void *Rva00EF6D54;
extern char Rva00D13F90;
// 0x00C6C1C0: independent INT3-bounded initializer.
void Rva00C6C1C0() { Rva00EF6D54 = (void *)&Rva00D13F90; }

extern void *Rva00EF6D58;
extern char Rva00D14020;
// 0x00C6C1D0: independent INT3-bounded initializer.
void Rva00C6C1D0() { Rva00EF6D58 = (void *)&Rva00D14020; }

extern void *Rva00EF6D5C;
extern char Rva00D14024;
// 0x00C6C1E0: independent INT3-bounded initializer.
void Rva00C6C1E0() { Rva00EF6D5C = (void *)&Rva00D14024; }

extern void *Rva00EF6D60;
extern char Rva00D13DD4;
// 0x00C6C1F0: independent INT3-bounded initializer.
void Rva00C6C1F0() { Rva00EF6D60 = (void *)&Rva00D13DD4; }

extern void *Rva00EF6D64;
extern char Rva00D13DD8;
// 0x00C6C200: independent INT3-bounded initializer.
void Rva00C6C200() { Rva00EF6D64 = (void *)&Rva00D13DD8; }

extern void *Rva00EF6D68;
extern char Rva00D13A34;
// 0x00C6C210: independent INT3-bounded initializer.
void Rva00C6C210() { Rva00EF6D68 = (void *)&Rva00D13A34; }

extern void *Rva00EF6D6C;
extern char Rva00D13A38;
// 0x00C6C220: independent INT3-bounded initializer.
void Rva00C6C220() { Rva00EF6D6C = (void *)&Rva00D13A38; }

extern void *Rva00EF6D70;
extern char Rva00D14100;
// 0x00C6C230: independent INT3-bounded initializer.
void Rva00C6C230() { Rva00EF6D70 = (void *)&Rva00D14100; }

extern void *Rva00EF6D74;
extern char Rva00D14104;
// 0x00C6C240: independent INT3-bounded initializer.
void Rva00C6C240() { Rva00EF6D74 = (void *)&Rva00D14104; }

extern void *Rva00EF6D78;
extern char Rva00D13C4C;
// 0x00C6C250: independent INT3-bounded initializer.
void Rva00C6C250() { Rva00EF6D78 = (void *)&Rva00D13C4C; }

extern void *Rva00EF6D7C;
extern char Rva00D13C50;
// 0x00C6C260: independent INT3-bounded initializer.
void Rva00C6C260() { Rva00EF6D7C = (void *)&Rva00D13C50; }

extern void *Rva00EF6D80;
extern char Rva00D14268;
// 0x00C6C270: independent INT3-bounded initializer.
void Rva00C6C270() { Rva00EF6D80 = (void *)&Rva00D14268; }

extern void *Rva00EF6D84;
extern char Rva00D1426C;
// 0x00C6C280: independent INT3-bounded initializer.
void Rva00C6C280() { Rva00EF6D84 = (void *)&Rva00D1426C; }


// 0x00C6C290: independent INT3-bounded initializer.
void Rva00C6C290() { Rva00EF6C90 = (void *)FXParticleSystem::DefaultModuleKey<6>::Read(); }


// 0x00C6C2A0: independent INT3-bounded initializer.
void Rva00C6C2A0() { Rva00EF6C94 = (void *)FXParticleSystem::DefaultModuleName<6>::Read(); }


// 0x00C6C2B0: independent INT3-bounded initializer.
void Rva00C6C2B0() { Rva00EF6C98 = (void **)&Rva00EF6C90; }


// 0x00C6C2C0: independent INT3-bounded initializer.
void Rva00C6C2C0() { Rva00EF6C9C = (void *)&Rva00EF6C94; }
