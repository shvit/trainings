#pragma once

#include "GameplayFrame.hpp"

namespace xon
{

enum class Event: char
{
    Nop=0,
    Exit,
    Pause,
    Up,
    Down,
    Left,
    Right,
};

class Render
{
    size_t screen_rows_;
    size_t screen_cols_;

    auto getDeviceRows() const -> size_t;
    auto getDeviceCols() const -> size_t;

public:
    Render();
    ~Render();

    void init();
    void close();

    auto getRows() const -> size_t;
    auto getCols() const -> size_t;
    bool draw(const GameplayFrame& field);

    auto get_event() const -> Event;

};


} // namespace xon