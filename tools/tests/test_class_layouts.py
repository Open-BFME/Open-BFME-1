"""class_layouts: CodeView parsing and the VC7.1 overloaded-virtual slot rule."""
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import class_layouts  # noqa: E402


def toolchain():
    try:
        class_layouts.build_module().vc71_root()
        return True
    except SystemExit:
        return False


@unittest.skipUnless(toolchain(), "MSVC 7.1 not available")
class SlotOrder(unittest.TestCase):
    def test_probe_agrees_with_vcall_thunks(self):
        rows, ok = class_layouts.run_probe()
        self.assertTrue(ok, rows)
        self.assertEqual(len(rows), 6)

    def test_naive_reading_is_caught(self):
        # Positive control: taking CodeView's shared group offset at face value
        # must disagree with the thunks, or the probe proves nothing.
        class_layouts.REVERSED_GROUPS = False
        try:
            rows, ok = class_layouts.run_probe()
        finally:
            class_layouts.REVERSED_GROUPS = True
        self.assertFalse(ok, rows)


class Bodies(unittest.TestCase):
    def test_private_views_skip_templates_and_comments(self):
        text = ("// class Fake {\nstruct Coord3D { float x, y, z; };\n"
                "template <class T>\nclass StringBase { T *p; };\nclass AsciiString : public StringBase<char> {};\n")
        self.assertEqual(class_layouts.class_bodies(text), ["Coord3D", "AsciiString"])

    def test_mangled_numbers(self):
        self.assertEqual(class_layouts.mangled_number("7AE")[0], 8)
        self.assertEqual(class_layouts.mangled_number("M@AE")[0], 12)
        self.assertEqual(class_layouts.mangled_number("BI@AE")[0], 24)


if __name__ == "__main__":
    unittest.main()
