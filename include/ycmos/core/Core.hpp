#pragma once

#include "Scheduler.hpp"

namespace ycmos::core
{

class Core
{
public:
    virtual ~Core() = default;

    [[noreturn]] void run();

    virtual Scheduler *scheduler() = 0;
};

inline void Core::run()
{
    scheduler()->schedule();
}

extern Core * const core;

}
