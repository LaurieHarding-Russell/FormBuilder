
def loadGraphicsLinux_X86_64bit(visibility=None):    
    native.new_local_repository(
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