# PartitionManager forwarder at 0x008F73C0 (pin ?rva008F73C0@PartitionManager@@QAEXPAURva00C9EE28Base@@@Z)

The 8-byte body at 0x008F73C0 is `mov ecx,[ecx+0xC]; jmp 0x008F8D00`, so it is a
thiscall member that forwards its one stack argument to a sub-object at +0xC. The
jump target returns with `ret 4` and never reads ECX. Its ledger row is a generated
placeholder, `?m@Gen_008f73c0@@QAEXXZ`, which declares no argument.

- **Caller.** Object::~Object (0x001D4010, landed) calls it at +0x188, directly and
  not through an ILT. It loads ECX from 0x012ED5BC, which dir32_addresses.csv
  records as `?TheShroudManager@@3PAVPartitionManager@@A`, and pushes EDI =
  Object+0x64. That base subobject carries the vbptr at +0x68, and 0x008F8D00
  reaches the virtual base through the argument's +4 word.
- **Zero Hour position.** The call sits where Zero Hour's destructor runs
  `ThePartitionManager->unRegisterObject(this)`, guarded the same way by the
  Object's partition data at +0x3B0.

The meaning is not proven beyond that position, so the pin keeps an
address-derived member name. The stash placeholder `remove` is not kept, because
nothing in the binary supplies that spelling.
