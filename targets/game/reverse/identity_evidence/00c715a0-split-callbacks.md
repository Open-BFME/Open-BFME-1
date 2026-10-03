# Separate termination callbacks at C715A0 and C715AA

The old generated row spans 32 bytes but combines two independently registered
callbacks. Neither callback requires an invented enclosing cleanup frame.

- RVA `009F6740` pushes VA `010715A0` and calls `atexit` at `009F6745`.
  The ten-byte target loads ECX with global VA `0134FAB8` and ends in E9
  at `00C715A5`. ILT `000309F4` resolves to the existing matched
  `Rva000FFCA0` destructor at RVA `000FFCA0`; it consumes ECX, destroys
  members at +38h/+2Ch, restores a vptr and returns without stack arguments.
- The matched initializer `00C6E2F2` constructs the global at VA `0134FB18`,
  then pushes callback VA `010715AA` at `00C6E2FC` and calls `atexit`.
  Its existing source calls the address-derived `rva00C715AARelease`.
- The second target begins at `00C715AA`, calls ILT `00017EEF`, pushes
  `0134FB1C`, calls imported `DeleteCriticalSection`, and returns at
  `00C715BF`. Thus it is exactly 22 bytes and the next callback begins
  at `00C715C0`.
- ILT `00017EEF` resolves to the matched `BfmeK1040::bfmeGo1040K`
  at `0005BFB0`. Its 42-byte body enters the lock at receiver+4, releases
  the receiver's first-word resource if nonzero, clears that word, leaves
  the lock, and returns without stack arguments. The new source uses this
  existing ABI view, not a newly named method.

Ghidra MCP memory reads of both callbacks and initializer `0106E2F2` agree
with the retail baseline. Its unanalysed xref index reports no entries, so
actual `atexit` operands, not absence of indexed references, prove the entries.
The two small native wrappers probe exactly at their independent extents;
strict add_match verification must also resolve the real callees and imports.
The globals remain external and retain address-derived identities. No global
storage size or source-level ownership beyond the observed receivers is claimed.
