cc_binary(
    name="test",
    srcs = [
        "main.cpp",
    ],
    deps = [
        # "//lib:PumpkinSpice",
        ":stb_truetype",
    ],
    data = [
        "style.spice",
        "test.xml",
        "@font//:Bangers",
    ]
)

cc_library(
    name = "stb_truetype",
    hdrs = ["@stb_truetype//file"],
    visibility = ["//visibility:public"],
    strip_include_prefix = "/external/stb_truetype/file",
    include_prefix = "",
)