workspace(name="formLib")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")


new_local_repository(
        name = "system_include_x86_64_linux",
        path = "/usr/include/linux",
        build_file_content = """
cc_library(
    name = "x11",
    hdrs = glob(["X11"]),
    visibility = ["//visibility:public"],
)
"""
)

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

http_archive(
    name = "rules_m4",
    urls = ["https://github.com/jmillikin/rules_m4/releases/download/v0.2/rules_m4-v0.2.tar.xz"],
    sha256 = "c67fa9891bb19e9e6c1050003ba648d35383b8cb3c9572f397ad24040fb7f0eb",
)
load("@rules_m4//m4:m4.bzl", "m4_register_toolchains")
m4_register_toolchains()

http_archive(
    name = "rules_flex",
    urls = ["https://github.com/jmillikin/rules_flex/releases/download/v0.2/rules_flex-v0.2.tar.xz"],
    sha256 = "f1685512937c2e33a7ebc4d5c6cf38ed282c2ce3b7a9c7c0b542db7e5db59d52",
)
load("@rules_flex//flex:flex.bzl", "flex_register_toolchains")
flex_register_toolchains()

http_archive(
    name = "rules_bison",
    urls = ["https://github.com/jmillikin/rules_bison/releases/download/v0.2/rules_bison-v0.2.tar.xz"],
    sha256 = "6ee9b396f450ca9753c3283944f9a6015b61227f8386893fb59d593455141481",
)
load("@rules_bison//bison:bison.bzl", "bison_register_toolchains")
bison_register_toolchains()