# Vertex shader loader complete diagnostics

The existing260-byte body at RVA007188B0 returns at007189B3 and is followed
by INT3. Its absolute string operands at+168/+232 name VA01120CB8 and
VA01120C98. Local retail bytes contain respectively
`Failed to allocate memory to load shader\n \0` (43 bytes) and
`Failed to create shader\n \0` (26 bytes). The old source ended each string
at the newline, omitting the following space. Function bytes alone masked
these relocation operands; the old prefix literal checker also accepted them.

Restore exactly the two missing spaces. The full strings including their
NUL terminators are now compared using the reviewed definitions from
7bfaf884e4:tools/build.py. This changes no identity, extent, callee signature,
source layout, shared header or verifier rule. Other diagnostics are retained.
