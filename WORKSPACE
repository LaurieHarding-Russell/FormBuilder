workspace(name="formLib")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_file")

# FIXME, maybe split these out into multiple files via starlark functions?

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

#graphics
http_archive(
    name = "glut",
    urls = ["https://github.com/LaurieHarding-Russell/FreeGLUT/archive/fb1ce95712dc472aff5279e0e8e19d684549204e.zip"],
    strip_prefix = "FreeGLUT-fb1ce95712dc472aff5279e0e8e19d684549204e",
    sha256 = "6e9034e1f5dd94524cd96c951e8c928a0ea91649d87f8aeb87e25045fa66ba4b",
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
    strip_prefix = "json-456478b3c50d60100dbb1fb9bc931f370a2c1c28",
    urls = [
        "https://github.com/nlohmann/json/archive/456478b3c50d60100dbb1fb9bc931f370a2c1c28.tar.gz",
    ],
    build_file_content = """
cc_library(
    name = "json",
    hdrs = ["single_include/nlohmann/json.hpp"],
    visibility = ["//visibility:public"],
)
"""
)

http_file(
    name = "stb_truetype",
    downloaded_file_path = "stb_truetype.h",
    urls = ["https://raw.githubusercontent.com/nothings/stb/master/stb_truetype.h"],
    sha256 = "5e28e92519846ef1a6118a454cdec146f6375655fb7e53b6102bfb224d16c17a"
)

http_archive(
    name = "font",
    url = "file:///home/laurie/Downloads/Bangers.zip",
    strip_prefix = "Bangers"
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