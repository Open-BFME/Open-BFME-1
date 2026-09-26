# GameSpyConfig constructor — 00628BA0

Identity comes from the independently matched GameSpyConfigInterface::create
at0062A0A0, called by SetUpGameSpy. The factory allocates0x90 bytes and passes
its owning AsciiString argument to this constructor through ILT00015681.
The constructor installs vtableVA01118050, whose deleting-destructor slot
routes through ILT000362F5 to00629F60 and the verified complete destructor
00629F90. The readable Zero Hour config parser agrees. The full3751-byte body
ends with RET4 at +EA4..EA6, followed by INT3 padding.

The 0x90 layout is independently corroborated by the matched destructor
GameSpyConfigDestructorProbe.cpp and getManglerLocation00628580. In particular
that getter indexes hosts+30 with stride4 and ports+3C with stride2, then stores
an unsigned-short output through its third argument. The constructor stores
its ten rank defaults at+64..+88:0,5,10,30,50,150,500,1000,2000,5000. Other
field meanings follow aligned accesses and the reference declaration; the
name oracle currently has no GameSpyConfig witness to override those names.

The source uses canonical AsciiString and the complete matched
StringBase<char>::compare(const char*) body. Visibility reproduces the three
initial inline comparisons and25 later out-of-line comparisons. The char
concat delegates to the existing length-taking base method and naturally
creates the one-byte newline temporary. Both follow StringBase.cpp's real
implementations. No asm, emitted bytes or manual EH stores are introduced.

The retail cleanup66-byte body at006286B0 calls node-pool deallocation0082E5F0
with12-byte node sizes. Using the existing BFME_STLP_NODE_ALLOC shim, rather
than the reference new-allocator macro, restores the missing five-byte EH
state store. The first twelve allocation calls target0082E540, the already
verified pool allocator also carrying a legacy __new_alloc ledger alias.
Changing destructor declarations was not retained.

Three bounded callee pins accompany the constructor:

* list<AsciiString>::push_back at00080220: full48-byte body independently
  allocates a12-byte node, calls ILT00007554 ->000620B0 on node+8, then links
  it at the tail. The complete66-byte _Construct at000620B0 calls the native
  StringBase<char> copy constructor00887B60. Both typed ping/QM list fields
  are also present in the matched factory/destructor/reference family.
* _List_base<const bool*>::~_List_base at006286B0: the eight list insertions
  own addresses of this parser's eight boolean section flags. The independent
  EH map, state9, invokes cleanup00C3FEED at frame-3C, then wrapper00628AC0,
  ILT00007365 and this exact66-byte node cleanup. No value destructor exists
  for its pointer payload. The existing unrelated ICF ledger owner is retained.
* vector<unsigned short>::push_back at00628AD0: complete52-byte body reads
  and writes a word, advances finish by2 and returns4. Independent matched
  getter00628580 proves the unsigned-short port contract. Its overflow call
  is ILT0004802C ->006288F0, already verified and pinned as the scoped
  Rva006288F0InsertOverflow body by vector_ushort_fill_insert.cpp. The local
  include reuses that existing address-qualified helper identity instead of
  adding a competing pin to the different003C16A0 code-generation variant.

Each of those three emitted helper bodies was separately run through
build.verify_functions with an explicit temporary row set, preserving all
real ledger ownership. All3/3 passed with their actual callee relocations;
this is additional dependency verification, not new byte credit. Only the
3751-byte constructor row is moved, and only its naked thunk is removed.
The original GSConfig.cpp remains the existing emitter of its verified
siblings and generated cleanup claims; its reference constructor is unclaimed.

Verification: exact3751/3751 with202 aligned relocations; scoped main gate1/1;
49 literals plus16 empty-string references verified; separate dependency
callee gate3/3; pin_consistency --check passed, no baseline or header changes.
Model GPT-6; work began21:55 UTC, exact22:03 UTC, callee verification22:08 UTC.
