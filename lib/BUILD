cc_library(
  name = "PumpkinSpice",
  srcs = [
    "PumpkinSpice.cpp",
    "AbstractComponent.cpp",
  ],
  hdrs = [
    "PumpkinSpiceComponentObject.h",
    "PumpkinSpiceObject.h",
    "PumpkinSpice.h",
    "AbstractComponent.h",
    "Input.h",
    "ButtonComponent.h",
    "InputComponent.h",
    "CommonTypes.h",
    "Style.h",
    "SpiceFactory.h",
    "CommonUtils.h"
  ],
  deps = [
    "@rapidxml//:rapidxml",
    "@json//:json",
    ":stb_truetype",
    ":stb_image"
  ],
  data = [
    "pumpkin.xsd",
  ],
  visibility = ["//visibility:public"]
)


cc_library(
    name = "stb_truetype",
    hdrs = ["@stb_truetype//file"],
    visibility = ["//visibility:public"],
    strip_include_prefix = "/external/stb_truetype/file",
    include_prefix = "",
    copts = [
        "-Wno-unused",
        "-Wno-unused-function",
    ],
)

cc_library(
    name = "stb_image",
    hdrs = ["@stb_image//file"],
    visibility = ["//visibility:public"],
    strip_include_prefix = "/external/stb_image/file",
    include_prefix = "",
    copts = [
        "-Wno-unused",
        "-Wno-unused-function",
    ],
)