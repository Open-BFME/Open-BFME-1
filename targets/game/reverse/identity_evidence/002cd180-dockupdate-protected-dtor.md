# DockUpdate's destructor is protected: ??_GDockUpdate@@MAEPAXI@Z / ??1DockUpdate@@MAE@XZ

The scalar-deleting wrapper at 0x002CD180 was ledgered as the public
`??_GDockUpdate@@UAEPAXI@Z`, and symbols.csv pinned the complete destructor
ILT 0x0004418E as the public `??1DockUpdate@@UAE@XZ`, while the matched body
at 0x002CCD10 is already `??1DockUpdate@@MAE@XZ`.

- `python3 tools/ilt_oracle.py check '??_GDockUpdate@@MAEPAXI@Z' 0x002CD180`
  reports CONFIRMED (exact); the `UAE` spelling is CONTRADICTED.
- `python3 tools/ilt_oracle.py check '??1DockUpdate@@MAE@XZ' 0x002CCD10`
  reports CONFIRMED (exact); the `UAE` spelling is CONTRADICTED.
- The wrapper's vtable 0x010CA934 slot zero and the ctor 0x002CD4B0 that
  installs it are unchanged; only the access decoration moves.
