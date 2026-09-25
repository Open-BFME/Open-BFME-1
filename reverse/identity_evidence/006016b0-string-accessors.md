# Address-qualified string return accessors

The full 32-byte bodies at RVA006016B0 and RVA006ED320 read members at
owner+0x48 and owner+4 respectively. Each pushes ECX and ESI, loads hidden
return storage from original ESP+4, adjusts the original owner to its member,
pushes that source pointer and uses return storage as the copy receiver.
It returns the same storage in EAX and pops4 bytes. The saved stack slot is
zeroed before the copy. This is an owning value copy, not a pointer return.

The direct call at +0x14 reaches RVA00887B60 for the first body and
RVA00888400 for the second. The corresponding complete 121-byte bodies are
StringBase<char> and StringBase<unsigned short> copy constructors. Both copy
the shared buffer pointer and increment its reference count under the string
lock; neither allocates list nodes. Each accepts the source on stack, returns
the destination and pops4 bytes. MSVC7.1's default wchar_t is unsigned short,
so the wide relocation is ??0?$StringBase@G@@AAE@ABV0@@Z. The narrow one is
??0?$StringBase@D@@AAE@ABV0@@Z. Existing independently matched string claims
provide both pins; no new pin is needed.

Canonical string headers define the owned layout. The wide copy forwarding
body is visible only in this TU to reproduce the observed direct StringBase
call, mirroring the canonical AsciiString forwarding constructor. The actual
owner identities remain unknown, so address-derived names and original ledger
dup tokens are preserved. Prior reference GameSpyConfig/list and User claims
were not evidence of BFME owner identity. Full extents remain unchanged;
these repairs add no net byte coverage.
