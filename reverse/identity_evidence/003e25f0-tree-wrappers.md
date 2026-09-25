# Three distinct hinted tree insertion contracts

Each 31-byte caller passes a one-pointer iterator by value, a const value
pointer and hidden return storage while preserving ECX. Independently decoded
routes are 003E25F0 -> ILT 0003E103 -> body 003DE190;
00401600 -> ILT 000440BC -> body 00400A90; and
00587390 -> ILT 00041B3C -> body 00586D60. All numbers are RVAs.

All three complete callees are 592 bytes. Each begins sub esp,8 / push ebx /
push esi; at +5 it reads original ESP+8, the iterator. After push edi the
load at +0x1E reads original ESP+12, the value pointer. At +0x31 it loads the
return storage from original ESP+4, then writes the node through it at +0x37.
This exit and every remaining exit return the storage in EAX and pop12 bytes;
the final ret12 at +0x24D ends the extent. The full bodies compare tree links,
node keys and walk iterators. These independently witnessed contracts justify
three separate address-qualified declarations and body pins. They do not
prove a ThingTemplate key, an int payload or any shared specialization.

The wrapper's unchanged ECX proves the tree subobject is at offset zero.
The one-pointer iterator has a nontrivial copy constructor to model the
observed hidden-return and stack-copy ABI. Incomplete value types avoid
inventing unwitnessed layouts. Original address-qualified ledger names and
31-byte extents remain. These are repairs of failed existing claims, with no
new coverage; moving reference claims to native source is only accounting.
