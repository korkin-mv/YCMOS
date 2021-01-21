#pragma once

#include <stdint.h>

#include "../Pt.hpp"

namespace ycmos::core
{

class Task
{
public:
    enum class ExitCode : uint8_t
    {
        None,
        Success,
        UnknownError
    };

public:
    Task();
    virtual ~Task() = default;

    virtual PtResult run(Pt *pt) = 0;

    ExitCode exitCode() const;

protected:
    void setExitCode(ExitCode code);

protected:
    ExitCode _exitCode;
};

inline Task::Task() :
    _exitCode(ExitCode::None)
{

}

inline Task::ExitCode Task::exitCode() const
{
    return _exitCode;
}

inline void Task::setExitCode(Task::ExitCode code)
{
    _exitCode = code;
}

}
