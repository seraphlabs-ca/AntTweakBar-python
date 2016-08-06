#!/usr/bin/env python

from setuptools import find_packages
from common.setuptools_support import setup

setup(
    name = "AntTweakBar",
    packages = find_packages(include=['AntTweakBar']),
    scripts = [],

    install_requires = [],

    # install SWIG modules {module_name: (source_path, target_path)
    swig_modules = {'AntTweakBarSWIG': ('anttweakbar', 'AntTweakBar')},

    # # metadata for upload to PyPI
    description = "AntTweakBar Python wrapper.",
    long_description = "",
    keywords = "",
    url = "",
)
