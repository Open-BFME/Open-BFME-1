// ?run@Rva000B5710Owner@@QAEXPAVRva000B5710Xfer@@@Z
// partial score=1.0 date=2026-10-01
// cl: /DNDEBUG /MD
class Rva000B5710Xfer { public:
virtual void slot00();
virtual bool slot01();
virtual void slot02();
virtual void slot03();
virtual void slot04();
virtual void slot05();
virtual void slot06();
virtual void slot07();
virtual void slot08();
virtual void slot09();
virtual void slot0A(unsigned char *);
virtual void slot0B();
virtual void slot0C();
virtual void slot0D();
virtual void slot0E();
virtual void slot0F();
virtual void slot10();
virtual void slot11();
virtual void slot12();
virtual void slot13();
virtual void slot14();
virtual void slot15();
virtual void slot16();
virtual void slot17();
virtual void slot18();
virtual void slot19();
virtual void slot1A();
virtual void slot1B(unsigned int *);
virtual void slot1C();
virtual void slot1D();
virtual void slot1E();
virtual void slot1F();
virtual void slot20();
virtual void slot21(unsigned char *);
virtual void slot22();
virtual void slot23(bool *);
};
class Rva000B5710Owner {
public:
 void run(Rva000B5710Xfer *x);
 void Rva000AF960(unsigned int); void Rva000AF980(unsigned int);
 void Rva000AF9A0(unsigned int); void Rva000AF9B0(unsigned int); void Rva000AF9C0(unsigned int); void Rva000AF9D0(unsigned int); void Rva000AF9E0(unsigned int);
 unsigned char pad00[0x10]; unsigned int at10; unsigned char pad14[4]; unsigned int at18;
 unsigned char pad1c[0x18]; unsigned int at34; unsigned char pad38[4]; unsigned char at3c;
 unsigned char pad3d[0x37]; unsigned int at74,at78; unsigned char pad7c[0x1c]; unsigned int flags;
};
void Rva000B5710Owner::run(Rva000B5710Xfer *x) {
 { unsigned char version[2]={1,1}; x->slot0A(version); }
 {
 if(x->slot01()) {
 unsigned int value;
 x->slot21((unsigned char *)&value);
 value=(unsigned char)value;
 if(value & 1u) flags |= 1u; else flags &= ~1u;
 if(value & 2u) flags |= 2u; else flags &= ~2u;
 if(value & 4u) flags |= 4u; else flags &= ~4u;
 if(value & 8u) flags |= 8u; else flags &= ~8u;
 if(value & 16u) flags |= 16u; else flags &= ~16u;
 if(value & 32u) flags |= 32u; else flags &= ~32u;
 if(value & 64u) flags |= 64u; else flags &= ~64u;
 if(value & 128u) flags |= 128u; else flags &= ~128u;

 } else {
 unsigned char value=0;
 if(flags & 1) value=1;
 if(flags & 2) value|=2;
 if(flags & 4) value|=4;
 if(flags & 8) value|=8;
 if(flags & 16) value|=16;
 if(flags & 32) value|=32;
 if(flags & 64) value|=64;
 if(flags & 128) value|=128;
 x->slot21(&value);
 }
 }
 if(flags & 2) { bool b=(at3c & 1)!=0; x->slot23(&b); if(x->slot01()) {if(b) Rva000AF960(1);else Rva000AF980(1);} }
 if(flags & 8) {unsigned int v=at10;x->slot1B(&v);Rva000AF9A0(v);}
 if(flags & 16) {unsigned int v=at18;x->slot1B(&v);Rva000AF9B0(v);}
 if(flags & 32) {unsigned int v=at74;x->slot1B(&v);Rva000AF9C0(v);}
 if(flags & 64) {unsigned int v=at78;x->slot1B(&v);Rva000AF9D0(v);}

 if(flags & 128) {unsigned char v=at34;x->slot21(&v);Rva000AF9E0(v);}
}
