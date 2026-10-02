# LivingWorldRegion constructor at RVA 0x0061AF80

The complete retail body is 304 bytes, ending in `ret 4` at +0x12D and
then INT3. It returns the receiver in EAX and constructs the object used by
the already matched region parser and destructor family.

Its vtable VA 0x01117258 supplies direct in-executable owner evidence:
slot zero contains ILT VA 0x00440B6A -> scalar-deleting wrapper 0x0061AB30;
slot two contains ILT VA 0x0040A6A0 -> RVA 0x0061A850. The latter six-byte
body returns VA 0x0111726C, whose exact string is `LivingWorldRegion`.
Both routes and the string were independently read from the unpacked image.
The existing matched destructor at 0x0061A780 uses the same owner/layout.
This establishes the constructor identity without guessing an EA type name.

## Native lifetimes and initialization

Retail EH handler 0x00C3EF58 references FuncInfo 0x00E2E91C. The six states
independently decoded by `tools/eh_info.py` describe:

1. Receiver base cleanup through 0x00001C80 -> Snapshot at 0x0005C520.
2. Member +4 through 0x0004178B -> matched 0x0061A5F0 destructor.
3. Member +0x9C through 0x00023A7E -> the native vector destructor at
   0x0061A200, whose element stride is 0x24.
4. String +0xB8 through 0x0000D828 -> AsciiString at 0x0005EE90.
5. Vector +0xD4 through 0x00026AB2 -> 0x000658A0.
6. Operator delete for the allocated 0x2C-byte object if its constructor
   throws, followed by transition back to state 4.

The source uses those actual C++ lifetimes: the existing base vtable view,
the matched `Rva0061A5F0` constructor/member, a native STLport vector with
the already established `Gen0061A200` element, canonical AsciiString, and
the existing `Rva0076F980Mid` vector view. Ordinary `new Gen_0061A3D0(name)`
supplies the allocation cleanup and null branch. Its existing signature
takes `const StringBase<char>&`; the real AsciiString public base conversion
provides that argument. The source's 0x2C-byte view preserves its observed
byte field at +0x18.

The bank omitted the required zeros at +0xAC and +0xF0 and used raw placement
construction, an explicit vtable constant, volatile writes, and barriers.
The reconstruction initializes those fields and reproduces all six unwind
states with an eight-byte local frame using native initialization instead.
Two address-derived pairs at +0xBC/+0xC0 and +0xE0/+0xE4 express adjacent
zero-initialization groups. Their constructors recover retail's scheduling
of the vector address and allocation preparation. They are source-shape
views of the observed stores, not claims about EA aggregate names or field
semantics. No volatile or barrier is needed.

All six direct calls agree with `tools/callees.py` and existing bindings:
member constructor 0x0061A9A0 via 0x0000A1FF; 0x003C9220 via 0x00002B8F
with two zero arguments and a used EAX return; ordinary operator new;
allocated-object constructor 0x0061A3D0 via 0x00048EAF; canonical string
release 0x00887940; and vector erase 0x00065960 via 0x00024C17.
Strict verification resolves all calls and the owner vtable and matches
all 304 bytes. No new pin, shared header, generated source, or assembly
is required.
