# Tree singleton storage at VA 0x0133F468

The eight retail bytes at 0x0133F468 are zero. The initializer at
RVA 0x00C6DCF0 passes that address as the receiver of the constructor
at 0x009009B0. That constructor writes a sentinel pointer at +0 and
sets the count at +4 to zero. The clear body at 0x00900960 tests and
clears the same count at VA 0x0133F46C and uses the same base address.
The registered cleanup at 0x00C70FC0 passes that same address to
0x008FFF30. These independent uses bound the two-word storage and
show that the data definition must not schedule its own constructor.

The definition uses the already pinned COFF spelling expected by
both the initializer and clear unit. Its declared class is the
existing opaque two-word storage view. This evidence does not settle
the template payload or the other provisional typed consumer names
at this address. The pinned BFME2 reference was searched for the
corresponding tree/initializer identities and supplied no target
evidence for this storage.
