import os
from conan import ConanFile
from conan.tools.scons import SConsDeps
from conan.tools.layout import basic_layout


class PlanarConan(ConanFile):
    requires = (
        "fmt/11.1.3",
        "funky/0.3.0",
    )

    def layout(self):
        basic_layout(self, src_folder="src")

    def generate(self):
        SConsDeps(self).generate()

    def build_requirements(self):
        self.test_requires("gtest/1.12.1")
