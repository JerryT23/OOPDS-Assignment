#include "../header/shiptype.h"

std::string Team::getTeamName() const {
    return Team::teamName;
};
void Team::setTeamName(std::string s) {
    Team::teamName = s;
};
void Team::setShips() {
    Team::ships;
};