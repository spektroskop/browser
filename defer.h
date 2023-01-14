#pragma once

struct Defer {
    Defer(std::function<void()> defer) : defer(defer) { }
   ~Defer() { defer(); }
    std::function<void()> defer;
};


