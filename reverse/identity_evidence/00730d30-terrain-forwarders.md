# Distinct terrain forwarding contracts

The three padded15-byte functions at00730D30,00730D50,00730D70 each load the
receiver member at+0x10, test it, and tail-call a distinct ILT if nonnull;
the null path returns with ret12. Routes independently decoded from retail:
00730D30 ->00023439 ->006C8890 (58 bytes);
00730D50 ->0002A833 ->006C88E0 (61 bytes);
00730D70 ->0001A492 ->006C8930 (18 bytes).

The first complete callee reads all three arguments and forwards them to the
member at+0x3098 via ILT000449F4 ->00720C20. It forwards only the first two
to member+0x309C via000020CC ->007023C0, then pops12 bytes. The independently
matched183-byte Rva00720BB0Context::scan at00720C20 dereferences a 3-float
position, computes a radius test using its second float argument and forwards
the third context pointer. The matched223-byte BfmeI1015BRemoveNearby.cpp body
at007023C0 likewise dereferences the point and treats the second word as float.
These consumers establish the point/float/context ABI of006C8890 independently
of the desired wrapper bytes. Its existing BfmeConv1015.cpp reconstruction uses
legacy integer parameters; the new address-qualified declaration uses the
witnessed types. It does not assert a recovered owner or original method name.

006C88E0 is the independently matched two-buffer construction-clearing body
in BfmeBaseHeightMapRemoveTreesAndProps.cpp; it passes position, geometry and
angle to both buffers.006C8930 is the separately matched prop-buffer-only
forwarder: member+0x309C, tail-call ILT0001B054, or ret12. Both have the
position/geometry-reference/float contract. Their existing declarations and
pins are reused. No integer type punning is needed in any wrapper.

The old W3DTerrainVisual construction claim at00730D30 instead used the
006C8930 target. Its geometry argument is inconsistent with the radius float
consumed by00720C20 and007023C0. The two dup rows reused that same emitted
function despite different targets. Each corrected wrapper retains its own
address-derived owner; the dup ledger tokens remain for the latter two.
Full extents and covered ranges are unchanged. This repairs15 failed bytes
and preserves30 additional bytes, with no net byte gain.
