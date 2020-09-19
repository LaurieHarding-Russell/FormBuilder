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

    http_file(
        name = "stb_truetype",
        downloaded_file_path = "stb_truetype.h",
        urls = ["https://raw.githubusercontent.com/nothings/stb/master/stb_truetype.h"],
        sha256 = "5e28e92519846ef1a6118a454cdec146f6375655fb7e53b6102bfb224d16c17a"
    )

    http_file(
        name = "stb_image",
        downloaded_file_path = "stb_image.h",
        urls = ["https://raw.githubusercontent.com/nothings/stb/master/stb_image.h"],
        sha256 = "8e5b0d717dfc8a834c97ef202d20e78d083d009586e1731c985817d0155d568c"
    )