cc_library(
  name = "PumpkinSpice",
  srcs = [
    "PumpkinSpiceFactory.cpp",
    "AbstractComponent.cpp",
  ],
  hdrs = [
    "PumpkinSpiceFactory.h",
    "AbstractComponent.h",
    "Input.h",
    "CommonTypes.h"
  ],
  deps = [
    "@rapidxml//:rapidxml",
    "@json//:json",
    ":stb_truetype",
  ],
  visibility = ["//visibility:public"]
)

exports_files(["default.style", "pumpkin.xsd"])



cc_library(
    name = "stb_truetype",
    hdrs = ["@stb_truetype//file"],
    visibility = ["//visibility:public"],
    strip_include_prefix = "/external/stb_truetype/file",
    include_prefix = "stb_truetype"
)