#include "GameplayFrame.hpp"

namespace xon
{

GameplayFrame::GameplayFrame():
    timestamp_{std::chrono::system_clock::now()},
    enemy_{},
    player_{},
    field_{},
    enemy_speed_k_{default_enemy_speed_k}
{
}

auto GameplayFrame::enemyAdd() -> Item&
{
    Item& new_enemy = enemy_.emplace_back();
    size_t enemy_count = enemy_.size();

    bool on_border = (enemy_count > 2U) ? RandBool() : (bool)(enemy_count - 1U);

    bool enemy_is_valid = false;
    while(!enemy_is_valid)
    {
        if(on_border) 
        {
            initItemInBorder(new_enemy);
        }
        else
        {
            initItemInSea(new_enemy);
        }
        DEBUG("Try to add new enemy at R:" << (int)new_enemy.row << " C: " << (int)new_enemy.col);

        bool has_collision = false;
        for(size_t chk_idx=0U; chk_idx < (enemy_count-1U); ++chk_idx)
        {
            if(new_enemy.checkAround(enemy_[chk_idx], init_collision_distance))
            {
                DEBUG("Collision with enemy R:" << (int)enemy_[chk_idx].row << " C: " << (int)enemy_[chk_idx].col << "; Need init enemy again!");
                has_collision = true;
                break;
            }
        }
        enemy_is_valid = !has_collision;
    }

    return new_enemy;
}

bool GameplayFrame::enemyDel()
{
    if(!enemy_.size())
    {
        return false;
    }

    enemy_.erase(enemy_.cbegin() + enemy_.size() - 1U);
    return true;
}

auto GameplayFrame::generateRandEnemySpeed() -> double
{
    double new_speed = default_player_speed/enemy_speed_k_ + (default_player_speed*enemy_speed_k_ - default_player_speed/enemy_speed_k_) * RandDbl();
    DEBUG("Generate new speed=" << std::setprecision(9) << new_speed);
    return new_speed;
}

auto GameplayFrame::generateRandEnemyAngle() -> double
{
    return 360 * RandDbl();
}

void GameplayFrame::initItemInSea(Item& item)
{
    item.row = field_.getBorderDbl() + (field_.getRowsDbl() - 2 * field_.getBorderDbl()) * RandDbl();
    item.col = field_.getBorderDbl() + (field_.getColsDbl() - 2 * field_.getBorderDbl()) * RandDbl();
    item.speed = generateRandEnemySpeed();
    item.angle = generateRandEnemyAngle();
}

void GameplayFrame::initItemInBorder(Item& item, bool need_run)
{
    bool select_zone_row = RandBool();
    item.row = select_zone_row ? field_.getRowsDbl() * RandDbl() : (RandBool() ? (field_.getRowsDbl() - field_.getBorderDbl() + field_.getBorderDbl() * RandDbl()) : (field_.getBorderDbl() * RandDbl()));
    //DEBUG("  calc row=" << item.row);
    bool safe_zone = (item.row < (field_.getBorderDbl() - 0.5)) || ((field_.getRowsDbl() - item.row) > (field_.getRowsDbl() - field_.getBorderDbl() + 0.5));
    //DEBUG("  calc safe_zone=" << std::boolalpha<< safe_zone);
    bool path_switch = RandBool();
    //DEBUG("  calc path_switch=" << std::boolalpha<< path_switch);
    item.col = safe_zone ? (field_.getColsDbl() * RandDbl()) : (path_switch ? (field_.getColsDbl() - field_.getBorderDbl() + field_.getBorderDbl() * RandDbl()) : (field_.getBorderDbl() * RandDbl()));
    item.speed = need_run ? generateRandEnemySpeed() : 0.0;
    item.angle = need_run ? generateRandEnemyAngle() : 0.0;
}

bool GameplayFrame::init(const size_t rows, const size_t cols)
{
    if(!field_.set_new_size(rows, cols))
    {
        return false;
    }

    for(size_t idx=0U; idx < default_enemy_count; ++idx)
    {
        enemyAdd();
    }

    initPlayer();

    timestamp_ = std::chrono::system_clock::now();

    return true;
}

void GameplayFrame::initPlayer()
{
    bool player_is_valid = false;
    while(!player_is_valid)
    {
        initItemInBorder(player_, false);
        DEBUG("Try to add player at R:" << (int)player_.row << " C: " << (int)player_.col);

        bool has_collision = false;
        for(size_t chk_idx=0U; chk_idx < enemy_.size(); ++chk_idx)
        {
            if(player_.checkAround(enemy_[chk_idx], init_collision_distance*2))
            {
                DEBUG("Collision with enemy R:" << (int)enemy_[chk_idx].row << " C: " << (int)enemy_[chk_idx].col << "; Need init player again!");
                has_collision = true;
                break;
            }
        }
        player_is_valid = !has_collision;
    }
}

auto GameplayFrame::enemiesCbegin() const -> decltype(enemy_)::const_iterator
{
    return enemy_.cbegin();
}

auto GameplayFrame::enemiesCend() const -> decltype(enemy_)::const_iterator
{
    return enemy_.cend();
}

auto GameplayFrame::getField() const -> const Field&
{
    return field_;
}

auto GameplayFrame::getPlayer() const -> const Item&
{
    return player_;
}

auto GameplayFrame::operator=(const GameplayFrame& src) -> GameplayFrame&
{
    //if(enemy_.size() && src.enemy_.size())
    //{
    //    DEBUG("Copy #1 OLD point (R:"<<enemy_[0U].row<<", C:"<<enemy_[0U].col<<")  NEW point (R:"<<src.enemy_[0U].row<<",C:"<<src.enemy_[0U].col<<")");
    //}

    timestamp_ = src.timestamp_;
    enemy_ = src.enemy_;
    player_ = src.player_;

    field_ = src.field_;

    enemy_speed_k_ = src.enemy_speed_k_;

    return *this;
}

void GameplayFrame::moveStep(TimeStamp new_time)
{
    TimeInterval ti = new_time - timestamp_;

    if(ti.count() < 0.001)
    {
        //DEBUG("Skip, time interval too small; need wait ("<<ti.count()<<")");
        return;
    }

    //const std::time_t t_c = std::chrono::system_clock::to_time_t(new_time);
    //DEBUG("Processing timestamp "<<  std::put_time(std::localtime(&t_c), "%c %Z"));

    for(size_t idx=0U; idx < enemy_.size(); ++idx)
    {
        enemy_[idx].move(ti, field_);
    }

    player_.move(ti, field_, false);
    
    timestamp_ = new_time;
}

void GameplayFrame::setPlayerRun(double new_angle, double new_speed) noexcept
{
    player_.angle = new_angle;
    player_.speed = new_speed;
}

void GameplayFrame::checkCollisions()
{

}


} // namespace xon
