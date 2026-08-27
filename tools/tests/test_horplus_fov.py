"""Numerical checks for the native tactical-camera Hor+ conversion."""

from math import atan, degrees, radians, tan
from unittest import TestCase


REFERENCE_DISPLAY_ASPECT = 4.0 / 3.0
REFERENCE_HORIZONTAL_FOV = radians(50.0)


def reference_viewport_aspect(display_width, display_height, tactical_width, tactical_height):
    current_viewport_aspect = tactical_width / tactical_height
    current_display_aspect = display_width / display_height
    return current_viewport_aspect * REFERENCE_DISPLAY_ASPECT / current_display_aspect


def reference_vertical_fov(reference_aspect):
    return 2.0 * atan(tan(REFERENCE_HORIZONTAL_FOV / 2.0) / reference_aspect)


def hor_plus_horizontal_fov(current_aspect, reference_aspect):
    return 2.0 * atan(tan(reference_vertical_fov(reference_aspect) / 2.0) * current_aspect)


TARGETS = (
    ("4:3", 640, 480),
    ("16:10", 1920, 1200),
    ("16:9", 1920, 1080),
    ("2560x1080", 2560, 1080),
    ("3440x1440", 3440, 1440),
    ("3840x1600", 3840, 1600),
    ("32:9", 3840, 1080),
)


class HorPlusFovTest(TestCase):
    def test_hor_plus_preserves_default_tactical_vertical_fov(self):
        for name, display_width, display_height in TARGETS:
            with self.subTest(name=name):
                tactical_width = display_width
                tactical_height = int(display_height * 0.80)
                current_aspect = tactical_width / tactical_height
                reference_aspect = reference_viewport_aspect(
                    display_width, display_height, tactical_width, tactical_height)
                horizontal_fov = hor_plus_horizontal_fov(current_aspect, reference_aspect)
                vertical_fov = 2.0 * atan(tan(horizontal_fov / 2.0) / current_aspect)

                self.assertAlmostEqual(
                    vertical_fov, reference_vertical_fov(reference_aspect), places=7)
                self.assertLess(horizontal_fov, radians(179.0))

    def test_reference_4_3_keeps_retail_horizontal_fov(self):
        reference_aspect = reference_viewport_aspect(640, 480, 640, int(480 * 0.80))
        self.assertAlmostEqual(degrees(hor_plus_horizontal_fov(640 / 384, reference_aspect)), 50.0)

    def test_wider_viewports_reveal_more_horizontal_world(self):
        reference_aspect = 5.0 / 3.0
        reference_horizontal = hor_plus_horizontal_fov(5.0 / 3.0, reference_aspect)

        for aspect in (2.0, 20.0 / 9.0, 3440.0 / 1152.0, 3.0, 40.0 / 9.0):
            self.assertGreater(hor_plus_horizontal_fov(aspect, reference_aspect), reference_horizontal)


if __name__ == "__main__":
    import unittest

    unittest.main()
