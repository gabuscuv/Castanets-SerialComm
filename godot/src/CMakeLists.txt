# SPDX-License-Identifier: Unlicense

target_sources( ${PROJECT_NAME}
    PRIVATE
        gdcastanet_server.h
        gdcastanet_server.cpp
        gdcastanet_node.h
        gdcastanet_node.cpp
        init.h
        init.cpp
)

target_include_directories( ${PROJECT_NAME}
    PRIVATE
        "src"
)
