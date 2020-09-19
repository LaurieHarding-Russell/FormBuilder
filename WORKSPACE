workspace(name="formLib")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_file")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load('@formLib//toolchain:pumpkinSpiceDependencies.bzl', 'load_pumpkin_spice_deps')


#graphics
http_archive(
    name = "glut",
    urls = ["https://github.com/LaurieHarding-Russell/FreeGLUT/archive/fb1ce95712dc472aff5279e0e8e19d684549204e.zip"],
    strip_prefix = "FreeGLUT-fb1ce95712dc472aff5279e0e8e19d684549204e",
    sha256 = "6e9034e1f5dd94524cd96c951e8c928a0ea91649d87f8aeb87e25045fa66ba4b",
)

http_archive(
    name = "glfw",
    strip_prefix = "glfw-8d7e5cdb49a1a5247df612157ecffdd8e68923d2",
    urls = [
        "https://github.com/glfw/glfw/archive/8d7e5cdb49a1a5247df612157ecffdd8e68923d2.tar.gz",
    ],
    build_file = "glfw.BUILD",
    sha256 = "66340d8f015381a368ed34e5eb20c3de2cdd916461fa43d2703d624baa48dde8"
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
# Pumpkin Spice deps
# #########################################
load_pumpkin_spice_deps()

###########################################
# Example dependencies 
###########################################

http_archive(
    name = "font",
    url = "https://fonts.google.com/download?family=Bangers",
    type = "zip",
    sha256 = "76f27ee3b9f2a9f28236ef05d867c141b2574e1b23c2ae568e7c05a06e0634a3",
    build_file_content = """
filegroup(
    name = "Bangers",
    srcs = ["Bangers-Regular.ttf"],
    visibility = ["//visibility:public"],
)
    """
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