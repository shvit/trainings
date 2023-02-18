#include <ncurses.h>
#include <cmath>

#include "Common.hpp"
#include "Render.hpp"

namespace xon
{

Render::Render():
    screen_rows_{0U},
    screen_cols_{0U}
{
}

Render::~Render()
{
}

void Render::init()
{
    initscr();
    curs_set(0);
    //raw();
    //timeout(-1);
    //cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    screen_rows_ = getDeviceRows();
    screen_cols_ = getDeviceCols();
    DEBUG("Init render with R:" << LINES << " C: " << COLS);
}

void Render::close()
{
    endwin();
}

auto Render::getDeviceRows() const -> size_t
{
    return (size_t)LINES;
}

auto Render::getDeviceCols() const -> size_t
{
    return (size_t)COLS;
}

auto Render::getRows() const -> size_t
{
    return screen_rows_;
}

auto Render::getCols() const -> size_t
{
    return screen_cols_;
}

bool Render::draw(const GameplayFrame& frame)
{
    size_t new_rows = getDeviceRows();
    size_t new_cols = getDeviceCols();

    if((screen_rows_ != new_rows) || (screen_cols_ != new_cols))
    {
        ERROR("Changed screen size (R:" << new_rows << ", C:" << new_cols << ")");
        return false;
    }

    if((new_rows != frame.getField().get_rows()) ||(new_cols < frame.getField().get_cols()))
    {
        ERROR("Not syncronized screen size and field size (R:" <<  frame.getField().get_rows() << ", C:" << frame.getField().get_cols() << ")");
        return false;
    }

    // Render world
    for(size_t row = 0U; row < screen_rows_; ++row)
    {
        for(size_t col = 0U; col < screen_cols_; ++col)
        {
            char out_ch = ' ';
            switch(frame.getField().get_char(row, col))
            {
                case xon::CellValue::base:
                    out_ch = '.';
                    break;
                default:
                    break;
            }
            mvprintw(row, col, "%c", out_ch);
        }

    }

    // Render enemies
    for(auto en = frame.enemiesCbegin(); en != frame.enemiesCend(); en++)
    {
        mvprintw((int)std::round(en->row), (int)std::round(en->col), "%c", '@');
    }

    // Render player
        mvprintw((int)std::round(frame.getPlayer().row), (int)std::round(frame.getPlayer().col), "%c", '$');

    refresh();

    return true;
}

auto Render::get_event() const -> Event
{
    int ch = getch();

    switch(ch)
    {
        case 27:        
        case 32:        return Event::Exit;
        case KEY_UP:    return Event::Up;
        case KEY_DOWN:  return Event::Down;
        case KEY_LEFT:  return Event::Left;
        case KEY_RIGHT: return Event::Right;
        default: return Event::Nop;
    }
}



} // namespace xon