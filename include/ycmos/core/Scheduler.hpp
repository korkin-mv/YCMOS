#pragma once

#include "Task.hpp"

namespace ycmos::core
{

class Scheduler
{
public:
    enum class Priority : uint8_t
    {
        Low, Normal, High
    };

public:
    virtual ~Scheduler() = default;

    [[noreturn]] virtual void schedule() = 0;

    virtual bool addTask(Task *task, Priority priority) = 0;

    virtual bool isScheduled(Task *task) = 0;
};

}
