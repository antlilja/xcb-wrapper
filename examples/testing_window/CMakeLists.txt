add_executable(xcb_wrapper_testing_window
    main.cpp
)

target_link_libraries(xcb_wrapper_testing_window PRIVATE xcb::wrapper)