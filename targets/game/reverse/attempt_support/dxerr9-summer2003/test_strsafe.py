"""Compile/read-only regression tests for SDK-free DirectX/strsafe.cpp."""
import struct
import sys
import tempfile
import unittest
from pathlib import Path

import capstone

ROOT = Path(__file__).resolve().parents[5]
sys.path.insert(0, str(ROOT / "tools"))
import build
from coffar import read_archive_bytes

FUNCTIONS = (
    ("?StringCopyWorkerW@@YGJPAGIPBG@Z", 0x00AD5401, 66, 12),
    ("?StringCchCopyA@@YGJPADIPBD@Z", 0x00AFD193, 23, 12),
    ("?StringCchCopyW@@YGJPAGIPBG@Z", 0x00AFD1AA, 23, 12),
    ("?StringCchPrintfA@@YAJPADIPBDZZ", 0x00AFD1C1, 39, 0),
    ("?StringCchPrintfW@@YAJPAGIPBGZZ", 0x00AFD1E8, 39, 0),
)


class StrsafeSourceTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.scratch = tempfile.TemporaryDirectory(prefix="strsafe-test-", dir=ROOT / "build")
        cls.addClassCleanup(cls.scratch.cleanup)
        scratch = Path(cls.scratch.name)
        cls.archive_object = scratch / "native.obj"
        archive = ROOT / "inputs/vendor/dxerr9/dxerr9.lib"
        members = dict(read_archive_bytes(archive.read_bytes(), str(archive)))
        cls.archive_object.write_bytes(members[r"obj\i386\dxerr9.obj"])
        cls.compiled_object = scratch / "strsafe.obj"
        build.compile_source(ROOT / "game/Libraries/Source/DirectX/strsafe.cpp",
                             cls.compiled_object)
        cls.symbols = build.load_symbol_map()

    def bound_body(self, obj, name, rva, size):
        body, relocations = build.read_object_symbol_bytes(obj, name, require_code=True)
        self.assertEqual(len(body), size)
        native = build.read_target_bytes(rva, size)
        bound = bytearray(body)
        for offset, kind, symbol in relocations:
            self.assertEqual(kind, 0x14)
            self.assertLessEqual(offset + 4, size)
            target = rva + offset + 4 + struct.unpack_from("<i", native, offset)[0]
            self.assertIn(target, self.symbols.get(symbol, ()),
                          f"unproved native call/tail route {symbol} -> {target:#x}")
            struct.pack_into("<i", bound, offset, target - rva - offset - 4)
        return bytes(bound), native

    def test_original_public_archive_sections_match_retail(self):
        for name, rva, size, _ in FUNCTIONS:
            with self.subTest(symbol=name):
                bound, native = self.bound_body(self.archive_object, name, rva, size)
                self.assertEqual(bound, native)

    def test_fresh_strsafe_cpp_matches_complete_native_functions(self):
        for name, rva, size, _ in FUNCTIONS:
            with self.subTest(symbol=name):
                bound, native = self.bound_body(self.compiled_object, name, rva, size)
                self.assertEqual(bound, native)

    def test_native_stdcall_and_varargs_cleanup(self):
        decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
        for name, rva, size, cleanup in FUNCTIONS:
            with self.subTest(symbol=name):
                native = build.read_target_bytes(rva, size)
                instructions = list(decoder.disasm(native, rva))
                self.assertEqual(sum(i.size for i in instructions), size)
                returns = [i for i in instructions if i.mnemonic == "ret"]
                self.assertTrue(returns)
                self.assertEqual({int(i.op_str, 0) if i.op_str else 0 for i in returns},
                                 {cleanup})


if __name__ == "__main__":
    unittest.main()
