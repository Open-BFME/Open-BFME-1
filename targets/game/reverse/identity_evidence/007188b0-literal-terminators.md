# Vertex shader loader complete diagnostics

The existing260-byte body at RVA007188B0 returns at007189B3. The outlined catch-handler stub follows at007189B4
through007189C4; INT3 starts007189C5. No padding is swallowed by the260B
primary-body claim. Its absolute string operands at+168/+232 name VA01120CB8 and
VA01120C98. Local retail bytes contain respectively
`Failed to allocate memory to load shader\n \0` (43 bytes) and
`Failed to create shader\n \0` (26 bytes). The old source ended each string
at the newline, omitting the following space. Function bytes alone masked
these relocation operands; the old prefix literal checker also accepted them.

Restore exactly the two missing spaces. The full strings including their
NUL terminators are now compared using the reviewed definitions from
7bfaf884e4:tools/build.py. This changes no identity, extent, callee signature,
source layout, shared header or verifier rule. Other diagnostics are retained.
