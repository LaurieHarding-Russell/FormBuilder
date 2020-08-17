workspace(name="formLib")

# FIXME, maybe split these out into multiple files via starlark functions?

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# #########################################
# X11 + OpenGL
# #########################################

load('@formLib//toolchain:linux_graphics_dep.bzl', 'loadGraphicsLinux_X86_64bit')
loadGraphicsLinux_X86_64bit()

new_local_repository(
        name = "openGL_x86_64_linux",
        path = "/usr/include/GL",
        build_file_content = """
cc_library(
    name = "GL",
    hdrs = glob(["**/*.h"]),
    visibility = ["//visibility:public"],
)
"""
)

http_archive(
    name = "glew",
    strip_prefix = "glew-a38094b249974f219f9c23f54b5b60a620777a13",
    urls = [
        "https://github.com/Lunarsong/glew/archive/a38094b249974f219f9c23f54b5b60a620777a13.tar.gz",
    ],
    build_file_content = """
cc_library(
name = "glew",
includes = ["include"],
srcs = [
    "src/glew.c",
],
hdrs = [
    "include/GL/glew.h",
    "include/GL/eglew.h",
    "include/GL/glxew.h",
    "include/GL/wglew.h",

],
defines = [
    "GLEW_STATIC",
],
visibility = ["//visibility:public"],
)

    """
)

# #########################################
# Pumpkin Spice!
# #########################################

http_archive(
    name = "rapidxml",
    strip_prefix = "rapidxml-f0058ab9374643018c1db3de521e44d4d52b8f5d",
    urls = [
        "https://github.com/dwd/rapidxml/archive/f0058ab9374643018c1db3de521e44d4d52b8f5d.tar.gz",
    ],
    build_file_content = """
cc_library(
    name = "rapidxml",
    hdrs = glob(["*.hpp"]),
    visibility = ["//visibility:public"],
)
"""
)

http_archive(
    name = "json",
    strip_prefix = "json-ee4028b8e4cf6a85002a296a461534e2380f0d57",
    sha256 = "a6882efbf49ba6d8a5bcea900c39e68b37630ecaf8128e61298a2efd0db99a6f",
    urls = [
        "https://github.com/nlohmann/json/archive/ee4028b8e4cf6a85002a296a461534e2380f0d57.tar.gz",
    ],
    build_file_content = """
cc_library(
    name = "json",
    hdrs = glob(["//single_include/nlohmann/*.hpp"]),
    visibility = ["//visibility:public"],
)
"""
)

http_file(
    name = "stb_truetype",
    downloaded_file_path = "stb_truetype.h",
    urls = ["https://github.com/nothings/stb/blob/master/stb_truetype.h"],
    
)

# #########################################
# Test
# #########################################
http_archive(
    name = "gtest",
    url = "https://github.com/google/googletest/archive/release-1.10.0.zip",
    strip_prefix = "googletest-release-1.10.0",
    sha256 = "94c634d499558a76fa649edb13721dce6e98fb1e7018dfaeba3cd7a083945e91"
)