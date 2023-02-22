cmake_minimum_required(VERSION 3.16)

idf_component_register(
    SRCS "NimBLE.cpp"
    INCLUDE_DIRS "include"
    INCLUDE_DIRS "include/BLE"
    REQUIRES bt
    )
