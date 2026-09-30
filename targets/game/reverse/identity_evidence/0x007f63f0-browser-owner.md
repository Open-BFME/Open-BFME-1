# Owner evidence for 0x007F63F0

The matched callback file `Rva007F6FE0Callbacks.cpp` declares `Rva007F7000` with a `void *message` argument and an `Rva007F7980Browser *browser` argument. The retail body at `0x007F7000` loads the second argument into ECX, pushes the first argument, and calls `0x007F63F0`.

This proves that retail passes an `Rva007F7980Browser` receiver to the target at `0x007F63F0`. It refutes the banked `Rva007F63F0Owner` type in `handleTicket`. The callback supplies no behavior name, so the landed method keeps address `0x007F63F0`.
