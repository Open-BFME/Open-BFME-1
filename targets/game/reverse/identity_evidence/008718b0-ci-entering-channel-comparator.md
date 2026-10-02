# `_ciEnteringChannelComparator` at 0x008718B0

The address is a six-byte import jump, not an inline duplicate of the string
comparison. Retail bytes are `FF 25 3C 93 35 01` at `0x008718B0`, followed by
ten `CC` padding bytes; the next matched body `_ciIsEnteringChannel` begins at
`0x008718C0`. The retail slot `0x0135933C` resolves through
`tools/import_binding.py` to `msvcr71.dll!_strcmpi`. The matched `_ciChannelLeft`
and `_ciChannelEntered` callers pass the body address `0x00C718B0`, so this
forwarding body must exist for their already-matched callback references.

The name comes from the 2007 GameSpy Chat source that this repository's
`GameSpy/PROVENANCE.txt` identifies as the reconstruction source for `chat/`.
Its `ciEnteringChannelComparator` takes two callback pointers and compares the
channel names with `strcasecmp`; `name` is the first `ciChatChannel` member.
The local function compares those same zero-offset strings with the retail
MSVCRT import. Source: [GameSpy Chat `chatChannel.c`](https://github.com/nitrocaster/GameSpy/blob/master/src/GameSpy/Chat/chatChannel.c#L297-L302).

Under the TU's `/O2` flags, the ordinary C forwarding function emits object
bytes `FF 25 00 00 00 00` with a DIR32 relocation at offset 2 to
`__imp___strcmpi`. `dir32_addresses.csv` binds that import to `0x0135933C`,
which yields the exact six retail bytes. Scoped byte and import gates pass for
both affected translation units. The per-file link census was unavailable and
is not represented as a pass.
