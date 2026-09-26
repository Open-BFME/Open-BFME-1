# AIBackAwayState constructor at 0x001804B0

The 57-byte body passes the literal `AIBackAwayState` to the common state-base
initializer and installs the dedicated vtable at 0x0109AE00. The independently
matched `BackAwayAndCowerStateMachine` constructor explicitly constructs an
`AIBackAwayState` and reaches this constructor through ILT 0x0001FDA7. The
vtable's slot-zero ILT 0x00025E19 reaches the 30-byte scalar-deleting destructor
at 0x00185890, whose complete-destructor ILT is 0x0004915C. Together the named
caller, class literal, dedicated vtable, and destructor family establish the
identity independently of the byte match.

`BfmeStateAX` was an address-family placeholder used when the constructor was
first converted. This correction preserves the same range and source body while
replacing that placeholder with the evidence-backed retail class name.
