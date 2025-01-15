#include "../header/grid.h"
void Grid::setTaken(bool b)
{
    taken = b;
}
bool Grid::getTaken() const
{
    return taken;
}
void Grid::setVal(std::string value)
{
    if(value == "0" || value == "1")
        type = value;
    val = value;
}
std::string Grid::getVal() const
{
    return val;
}
std::string Grid::getType() const
{
    return type;
}
void Grid::setTeamName(std::string teamname) {
    teamName = teamname;
}
std::string Grid::getTeamName() const {
    return teamName;
}