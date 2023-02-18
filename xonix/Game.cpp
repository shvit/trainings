#include <unistd.h> 

#include "Game.hpp"

namespace xon
{

Game::Game():
    rr_{},
    gp_{},
    need_exit_{true}
{
}

void Game::init()
{
    openlog("xonix",LOG_CONS | LOG_NDELAY | LOG_PID, LOG_USER);
    rr_.init();
    gp_.init(rr_.getRows(), rr_.getCols());
    need_exit_ = false;
}

void Game::close()
{
    rr_.close();
    closelog ();
}

void Game::loop()
{
    while(!need_exit_)
    {
        // Draw
        rr_.draw(gp_.frameForOutput());

        // Check player actions
        switch(rr_.get_event())
        {
            case Event::Exit:
                need_exit_ = true;
                break;
            case Event::Up:
                gp_.playerRun(0);
                break;
            case Event::Down:
                gp_.playerRun(180);
                break;
            case Event::Left:
                gp_.playerRun(270);
                break;
            case Event::Right:
                gp_.playerRun(90);
                break;
            case Event::Nop:
            default:
                break;
        }

        // Movements
        gp_.moveStep();

        // Check collisions

        //usleep(10000);
    }
}

} // namespace xon