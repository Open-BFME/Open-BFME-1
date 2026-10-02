# RVA 0x000D0A30: opaque table begin ABI owner

Baseline retail-1.03-unpacked SHA256 1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75.
The prior tg_000d0a30 row used an object-symbol for a byte-identical native
hashtable<int,Relationship>::begin instantiation in Player.cpp. Its bytes prove
the generic bucket-walk implementation; they do not establish that concrete
template instantiation as the unique retail identity. Retail has no ICF.

The retail 78-byte body reads bucket begin/end at ECX+4/+8, walks four-byte
node pointers, and writes a two-pointer iterator (node and original ECX) to
the hidden stack return storage. RET4 ends the body. It calls nothing.
The Player table transfer at DA250 reaches this body through ILT CFE5 and
uses the returned iterator with Player+200 AsciiString-keyed enum HashB;
see 000da250-player-hashtable-xfer.md for independent caller/table proof.
Other generic begin consumers cannot resolve its original template spelling.

Replace the unproven concrete object-symbol identity with one address-derived
Rva000D0A30::method ABI provider. Its local view preserves the four-byte
unknown prefix and native STLport vector of node pointers at +4. Its source
uses the actual native vector size/index expressions and returns the native
HashB iterator. The address-derived owner claims no original class or template
identity. The previous Player.cpp emission may remain incidental but has no
second retail ledger claim. No compiler alias or alternative name is needed.

Fresh probes: build/playerhash/vector-helper.log is EXACT78B/0 relocations.
The native hash_map begin wrapper aggregate-return behavior is replicated by
a clean inline wrapper around this opaque provider: wrapper-main.log is
EXACT395B with 12 relocation sites. Direct calls without the wrapper read
EAX instead of stack iterator storage and fail119 bytes; those are rejected.
The canonical template begin itself is independently EXACT78B in begin.log.
A pin for the sole opaque owner at ILT CFE5 must have route=D0A30 and pass
pin_consistency; strict production gates remain required for both bodies.

Pristine donor confirmation: inputs/vendor/stlport/stl/_hashtable.h lines
325-333 implement this exact first-bucket walk and empty iterator return;
_hash_map.h line159 wraps it with inline begin returning _M_ht.begin().
Both donor hypotheses are independently checked against retail instructions.
