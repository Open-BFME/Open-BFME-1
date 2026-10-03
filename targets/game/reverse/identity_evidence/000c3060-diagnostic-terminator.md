# Victory-system diagnostic terminator

The261-byte body at000C3060 returns at000C3164, followed by INT3.
Its diagnostic operand at+173 references VA010839C0. Retail stores
`TheVictorySystem has not been initialized!.\n\0`; source omitted
that newline and put NUL there instead. Restore the one missing byte.
The existing identity, class declarations, callees and extent are retained.
This literal-only repair uses reviewed7bfaf884e4 complete-string checking
in addition to the ordinary strict gate; no verifier or baseline is relaxed.
