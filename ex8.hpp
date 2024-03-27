#pragma once
#include <string>
#include <cstdio>

struct Cat {
    std::string name = "Shashimi";
    int whiskers = 16;

    void meow() { std::puts("Meow!\n"); }
};