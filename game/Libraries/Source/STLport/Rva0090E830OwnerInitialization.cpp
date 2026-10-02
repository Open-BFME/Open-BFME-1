// cl: /DNDEBUG /MD /EHsc
// Retail37B INT3-delimited through RET4 at +0x22.
// Two words zeroed before an 11-byte subobject initializer at +8.
// Callee0090E390 ignores its first reference, stores its second stack dword
// at this+0, returns this in EAX and ends RET8. Independently probed exact.
// Legacy template names do not prove a specialization; these ABI views
// retain their retail addresses and make no original owner-name claim.
struct Rva0090E830Argument {};
struct Rva0090E390Subobject {
    unsigned field00;
    Rva0090E390Subobject(const Rva0090E830Argument &,unsigned);
};
struct Rva0090E830Owner {
    unsigned field00,field04;
    Rva0090E390Subobject field08;
    Rva0090E830Owner(const Rva0090E830Argument &);
};
Rva0090E830Owner::Rva0090E830Owner(const Rva0090E830Argument &argument)
  : field00(0),field04(0),field08(argument,0) {}
