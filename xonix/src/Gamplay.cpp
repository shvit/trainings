#include <numeric>

#include "Gameplay.hpp"

namespace xon
{

Gameplay::Gameplay():
    frame_switcher_{false},
    frames_{}
{
}

void Gameplay::switch_frames()
{
    //size_t idx_curr = frame_switcher_;
    //size_t idx_new = !frame_switcher_;
    //DEBUG("Switch frames from "<<idx_curr<<" to "<<idx_new);
    frameForOutput() = frameForPrepare();

    //DEBUG("Output(R:" << frameForOutput().getField().get_rows() << ", C:" << frameForOutput().getField().get_cols() << "); "
    //      "Draw(R:"   << frameForPrepare().getField().get_rows()   << ", C:" << frameForPrepare().getField().get_cols()   << ")");

    frame_switcher_ = !frame_switcher_;
}

auto Gameplay::frameForPrepare() -> GameplayFrame&
{
    return frames_[frame_switcher_];
}

auto Gameplay::frameForOutput() -> GameplayFrame&
{
    return frames_[!frame_switcher_];
}

bool Gameplay::init(const size_t rows, const size_t cols)
{
    xon::RandInit();

    bool ret = frameForPrepare().init(rows, cols);
    switch_frames();

    //bool ret = frameForOutput().init(rows, cols);


    return ret;
}

void Gameplay::playerRun(int new_angle)
{
    frameForPrepare().setPlayerRun(new_angle, default_player_speed);
}

void Gameplay::playerStop()
{
    frameForPrepare().setPlayerRun(0, 0);
}

void Gameplay::moveStep()
{
    auto & calc_frame = frameForPrepare();
    auto backup_frame{calc_frame};

    if(calc_frame.moveStep(std::chrono::system_clock::now()))
    {
        calc_frame.moveReflections(backup_frame);
        switch_frames();
    }
   

}


} // namespace xon