# Copyright(c) 2019-present, Anton Lilja.
# Distributed under the MIT License (http://opensource.org/licenses/MIT)

add_executable(xcb_wrapper_testing_window
    main.cpp
)

target_link_libraries(xcb_wrapper_testing_window PRIVATE xcb::wrapper)