#pragma once

#include <array>
#include <vector>

#include "Item.hpp"
#include "Field.hpp"
#include "GameplayFrame.hpp"

namespace xon
{

class Gameplay
{
    bool frame_switcher_;
    std::array<GameplayFrame, 2U> frames_;

    void switch_frames();
    auto frameForPrepare() -> GameplayFrame&;

public:
    Gameplay();

    bool init(const size_t rows, const size_t cols);

    auto frameForOutput() -> GameplayFrame&;

    void playerRun(int new_angle);
    void playerStop();

    void moveStep();
};

} // namespace xon