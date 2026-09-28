# RVA 0x009004A0: cdecl render-object factory

The retired name `?Create_Render_Obj@W3DAssetManager@@QAEPAVRenderObjClass@@XZ`
claims a no-argument thiscall. Retail never consumes incoming ECX and ends in
plain `ret` at RVA 0x0090095C. The complete extent is 1213 bytes.

Independent caller evidence: the call at RVA 0x00778A3F in the
ModelConditionInfo::validateCachedBones body pushes three vector references,
a color word, a float scale (fstp to a pushed stack slot), and the model name.
It executes `add esp,0x18` immediately afterward. The call at 0x007562C9
in body 0x00755F70 independently repeats the same six arguments and cleanup.
Thus the old thiscall identity is contradicted by both callers and the callee.
The replacement keeps the unique address token and describes only the
factory behavior, without assigning this BFME-only overload to a guessed class.

The body lowercases a model name, obtains a counted registry prototype,
creates the unmodified render object when no modifications are requested,
otherwise formats a cache key and constructs the prototype at 0x009002C0.
It then creates the resulting object through vtable slot 0x3c and calls
0x0091FCC0, whose established body copies the original name to offset 0xa4.
The whole flow was read from GhidraSQL and checked against retail disassembly.

Callee integration reuses RegistryPrototypeLookup.cpp, P8ZeroingCtors.cpp,
Rva00900FF0Constructor.cpp and BfmeConv1354.cpp declarations and signatures.
The retail calls use these witnessed ILT routes:

- 0x0003BC23 -> 0x0053AE60: narrow string push_back. The target reads a byte
  from its one argument, grows the three-pointer buffer when necessary,
  writes that byte and a terminating zero, increments finish, and returns 4.
- 0x0001642D -> 0x000A5120: narrow-string three-pointer deallocator. This is
  the destructor already pinned under the narrow basic_string identity.
- 0x0003D915 -> 0x001F9520: copy constructor of the pointer-sized vector
  emitted by the established Rva00900FF0 constructor TU. The target reads
  source begin/end, divides byte distance by four, allocates, copies those
  bytes and sets finish; ECX is destination and its single argument is a
  const source reference; returns 4. The pointer-qualified element spelling
  is retained from the established constructor rather than renamed.

The raw relative jumps were decoded from the current retail baseline; these
are routes to existing bodies, not newly inferred semantic identities.
The resolver already handles the first two routes. Only the existing vector
copy constructor object-symbol needs a pin, at its true body 0x001F9520.
The two string-vector copies call the already pinned 0x008FFB80 directly.
The factory's 0x74 allocation agrees with the established prototype layout.
Its float scale is passed as unchanged bits to that constructor's existing
integer-qualified argument; this does not change the ABI or claim a new name.

The isolated TU is placed beside W3DAssetManager.cpp because that TU's current
ZH class declaration lacks the proven cdecl signature. No shared header or
existing class identity is changed. The native WWMath bitwise Fabs expression,
an empty iterator tag, and inline character reference forwarding reproduce
retail without hand-written assembly. Probe reports 1213 bytes exact with
44 relocation sites; source acceptance still requires the scoped byte gate.
