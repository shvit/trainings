#pragma once

#include "Common.hpp"
#include "Gameplay.hpp"
#include "Render.hpp"

namespace xon
{

class Game
{
private:
    xon::Render rr_;
    xon::Gameplay gp_;
    bool need_exit_;

public:
    Game();

    void init();
    void close();

    void loop();
};

} // namespace xon