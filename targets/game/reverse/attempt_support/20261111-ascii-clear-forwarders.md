# String clear forwarding

Water.cpp and Rva00362670Reset.cpp now explicitly call StringBase<char>::clear at their five existing narrow-string clear sites, exactly the operation forwarded to by canonical AsciiString::clear. Normal gate passes all three function rows and two data rows; both COFF objects omit clear@AsciiString. Other record clear operations and wide-string cleanup remain unchanged. No layouts, pins, names or ledger changes.

Reviewed prior clear/set-family emitter findings and BFME 2 76f0baefa6f285d54bc1ca922397674312a5913f connection-auth-string-cleanup-20261028-codex.md. Donor is contextual; this repair uses BFME 1 canonical forwarding and complete caller verification. Current linking gain unknown; no family-wide pin retirement or provider correctness claimed.
