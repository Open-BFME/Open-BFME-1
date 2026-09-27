// cl: /DNDEBUG /MD /EHsc
// 0x0037A610 transfers a versioned record through chained virtual writers.
struct Version37A610 { unsigned char kind, version; };
class MidVirtualSlot90Receiver { public:
 virtual void pad00();
 virtual void pad04();
 virtual void pad08();
 virtual void pad0C();
 virtual bool skip();
 virtual void pad14();
 virtual void pad18();
 virtual void pad1C();
 virtual void pad20();
 virtual void pad24();
 virtual MidVirtualSlot90Receiver *version(Version37A610 *);
 virtual void pad2C();
 virtual void pad30();
 virtual void pad34();
 virtual void pad38();
 virtual void pad3C();
 virtual void pad40();
 virtual void pad44();
 virtual void pad48();
 virtual void pad4C();
 virtual void pad50();
 virtual void pad54();
 virtual void pad58();
 virtual void pad5C();
 virtual MidVirtualSlot90Receiver *slot60(void *);
 virtual void pad64();
 virtual void pad68();
 virtual MidVirtualSlot90Receiver *slot6C(void *);
 virtual void pad70();
 virtual void pad74();
 virtual void pad78();
 virtual MidVirtualSlot90Receiver *slot7C(void *);
 virtual void pad80();
 virtual void pad84();
 virtual void pad88();
 virtual MidVirtualSlot90Receiver *slot8C(void *);
};
// The established declarations say void; retail callers consume EAX from
// the forwarded slot 0x90. Cast only the return ABI at these call sites.
void Rva0010C3C0(MidVirtualSlot90Receiver *,void *);
void Rva0010C180(MidVirtualSlot90Receiver *,void *);
void Rva0010C160(MidVirtualSlot90Receiver *,void *);
void Rva0010C1A0(MidVirtualSlot90Receiver *,void *);
void Rva0010C200(MidVirtualSlot90Receiver *,void *);
typedef MidVirtualSlot90Receiver *(*Writer37A610)(MidVirtualSlot90Receiver *,void *);
class VersionedRecord37A610 { public:
 char bytes[0x48];
 void transfer(MidVirtualSlot90Receiver *target);
};
void VersionedRecord37A610::transfer(MidVirtualSlot90Receiver *target)
{
 if (target->skip()) return;
 Version37A610 v; v.kind=1; v.version=2;
 MidVirtualSlot90Receiver *out = ((Writer37A610)Rva0010C1A0)(
  ((Writer37A610)Rva0010C160)(
   ((Writer37A610)Rva0010C180)(
    ((Writer37A610)Rva0010C3C0)(target->version(&v),bytes+4)->slot7C(bytes+8),bytes+0xc),bytes+0x10),bytes+0x14);
 out = out->slot6C(bytes+0x18)->slot8C(bytes+0x1c);
 out = ((Writer37A610)Rva0010C3C0)(((Writer37A610)Rva0010C200)(out->slot6C(bytes+0x20),bytes+0x24),bytes+0x28);
 out->slot60(bytes+0x2c)->slot6C(bytes+0x38)->slot6C(bytes+0x3c)->slot6C(bytes+0x40)->slot6C(bytes+0x44);
 if (v.version >= 2) target->slot8C(bytes+0x1d);
}
