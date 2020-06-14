cc_library(
        name = "libcircular_buffer",
        srcs = glob(["src/*.cpp"]),
        hdrs = glob(["include/*.h"]),
        linkopts = ["-pthread"],
        visibility = ["//visibility:public"],
        )

cc_test(
        name = "circular_buffer-test",
        srcs = glob(["test/*.cpp", "test/*.h"]),
        copts = ["-Iexternal/gtest/include"],
        deps = [ 
        ":libcircular_buffer",
        "@gtest//:main",
        ],
       )
