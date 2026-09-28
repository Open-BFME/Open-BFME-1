// RVA0020F330; established Gen0020F330::handle identity retained.
// Primary-body snapshot: six float fields, damage snapshot, particle node IDs,
// four extension float/flag pairs, packed flags, and final enum field.
// XferException identity and ABI are already RTTI-proven at ThrowInfo011DFE5C.
// Node vtable010A74E8 is the existing Rva0020DE10Poly deleting-destructor owner.
// The transferred ID must outlive the loading block, keeping its stack slot
// distinct from the native throw temporary. The version pair occupies 4 bytes.
// cl: /DNDEBUG /MD /EHsc
class XferException { public: XferException(int,const char*,...); XferException(const XferException&); ~XferException(); char *text;int tag; };
struct FlagPair { unsigned char first,second;unsigned char pad[2]; };
#define V(N) virtual void slot##N()
class FlagPairTarget { public:
 V(00);V(01);virtual bool isSaving();virtual bool isCRC();virtual bool isLightCRC();V(05);V(06);V(07);V(08);V(09);virtual void applyFlags(FlagPair*);
 V(11);V(12);V(13);V(14);V(15);V(16);V(17);V(18);V(19);V(20);V(21);V(22);V(23);V(24);V(25);V(26);
 virtual void real(float*);V(28);virtual void uint32(unsigned*);V(30);virtual void uint16(unsigned short*);V(32);V(33);V(34);virtual void boolean(bool*);
};
class MidVirtualSlot90Receiver;
void Rva0010C0A0(MidVirtualSlot90Receiver*,void*);void Rva0010C0C0(MidVirtualSlot90Receiver*,void*);void Rva0010C160(MidVirtualSlot90Receiver*,void*);void Rva0010C2E0(MidVirtualSlot90Receiver*,void*);void Rva0010C3C0(MidVirtualSlot90Receiver*,void*);
class BfmeSeedTarget;
class Gen_00212790 { public: void bfmeSeed(BfmeSeedTarget*); };
class FlagXfer0020F000;
class BitFlagSnapshot0020F000 { public: void xfer(FlagXfer0020F000*);unsigned bits; };
class Rva0020DE10Poly { public: virtual ~Rva0020DE10Poly();unsigned id;Rva0020DE10Poly *next; };
struct Snapshot0020F330 { virtual void xfer(FlagPairTarget*);char pad[0x58]; };
class Gen0020F330 { public:
 char pad[0x18]; float f18,f1c,f20,f24,f28,f2c;unsigned f30,f34,f38,f3c;Snapshot0020F330 snapshot;unsigned f9c,fa0;bool fa4,fa5,fa6,fa7;Rva0020DE10Poly *head;float fac[4];bool fbc[4];char gapc0[12];unsigned fcc;BitFlagSnapshot0020F000 fd0;
 void handle(FlagPairTarget*);
};
void Gen0020F330::handle(FlagPairTarget *target) {
 ((Gen_00212790*)this)->bfmeSeed((BfmeSeedTarget*)target);
 if(target->isLightCRC())return;
 FlagPair flags;flags.first=1;flags.second=1;target->applyFlags(&flags);
 target->real(&f18);target->real(&f1c);target->real(&f20);target->real(&f24);target->real(&f28);target->real(&f2c);
 Rva0010C0A0((MidVirtualSlot90Receiver*)target,&f30);Rva0010C0C0((MidVirtualSlot90Receiver*)target,&f34);target->uint32(&f38);Rva0010C160((MidVirtualSlot90Receiver*)target,&f3c);
 snapshot.xfer(target);target->uint32(&f9c);target->uint32(&fa0);target->boolean(&fa4);target->boolean(&fa5);target->boolean(&fa6);target->boolean(&fa7);
 unsigned id;
 if(!target->isCRC()) {
  unsigned short count=0;
  for(Rva0020DE10Poly *n=head;n;n=n->next)++count;
  target->uint16(&count);
  if(target->isSaving()) {
   for(Rva0020DE10Poly *n=head;n;n=n->next) Rva0010C2E0((MidVirtualSlot90Receiver*)target,&n->id);
  } else {
   if(head) throw XferException(5,0);
   for(unsigned short i=0;i<count;++i) {
    Rva0010C2E0((MidVirtualSlot90Receiver*)target,&id);
    Rva0020DE10Poly *n=new Rva0020DE10Poly;
    n->id=id;n->next=head;head=n;
   }
  }
 }
 for(int i=0;i<4;++i) {target->real(&fac[i]);target->boolean(&fbc[i]);}
 fd0.xfer((FlagXfer0020F000*)target);Rva0010C3C0((MidVirtualSlot90Receiver*)target,&fcc);
}
