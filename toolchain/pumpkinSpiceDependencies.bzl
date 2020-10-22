load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_file")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def load_pumpkin_spice_deps():

    http_archive(
        name = "rapidxml",
        url = "https://github.com/dwd/rapidxml/archive/f0058ab9374643018c1db3de521e44d4d52b8f5d.tar.gz",
        build_file_content = """
cc_library(
    name = "rapidxml",
    hdrs = glob(["*.hpp"]),
    visibility = ["//visibility:public"],
)
""",
      strip_prefix = "rapidxml-f0058ab9374643018c1db3de521e44d4d52b8f5d",
      sha256 = "29278163bd6aaf847296acf34cc4efc3bb0891b45c2f8decacfcf5eb46972767"
    )

    http_archive(
        name = "json",
        url = "https://github.com/nlohmann/json/archive/456478b3c50d60100dbb1fb9bc931f370a2c1c28.tar.gz",
        build_file_content = """
cc_library(
    name = "json",
    hdrs = ["single_include/nlohmann/json.hpp"],
    visibility = ["//visibility:public"],
)
""",
      strip_prefix = "json-456478b3c50d60100dbb1fb9bc931f370a2c1c28",
      sha256 = "d5119019bbf376ee8c9c4093f80fa087dd3ef052b824d0b0e3136d8d4f912f37",
    )

    http_archive(
        name = "nothings",
        urls = ["https://github.com/nothings/stb/archive/b42009b3b9d4ca35bc703f5310eedc74f584be58.tar.gz"],
        strip_prefix = "stb-b42009b3b9d4ca35bc703f5310eedc74f584be58",
        build_file_content = """
cc_library(
    name = "stb_truetype",
    hdrs = ["stb_truetype.h"],
    visibility = ["//visibility:public"],
    include_prefix = "",
    copts = [
        "-Wno-unused",
        "-Wno-unused-function",
    ],
)

cc_library(
    name = "stb_image",
    hdrs = ["stb_image.h"],
    visibility = ["//visibility:public"],
    include_prefix = "",
    copts = [
        "-Wno-unused",
        "-Wno-unused-function",
    ],
)
""",
    sha256 = "13a99ad430e930907f5611325ec384168a958bf7610e63e60e2fd8e7b7379610",
    )
    
    http_archive(
        name = "glm",
        strip_prefix = "glm-b3f87720261d623986f164b2a7f6a0a938430271",
        urls = [
            "https://github.com/g-truc/glm/archive/b3f87720261d623986f164b2a7f6a0a938430271.tar.gz",
        ],
        build_file_content = """
cc_library(
    name = "glm",
    includes = ["."],
    srcs = glob(["glm/**/*.hpp"]) + glob(["glm/**/*.h"]),
    hdrs = glob(["glm/**/*.inl"]),
    visibility = ["//visibility:public"],
    defines = [
        "GLM_FORCE_RADIANS",
        "GLM_FORCE_LEFT_HANDED",
        "GLM_FORCE_DEPTH_ZERO_TO_ONE",
    ],
)""",
        sha256 = "db66eca1a396bbb7c5e286b9fa84b7d82d9ba317968bbb316805f80f45ca0cd8",
    )