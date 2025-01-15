#ifndef GRID_H
#define GRID_H
#include<string>
class Grid {
    bool taken;
    std::string val; //string bcs store *1 if ship is at the location
    std::string type; // 0/1
    std::string teamName;
    public:
    void setTaken(bool b);
    bool getTaken() const;
    void setVal(std::string value);
    std::string getVal() const;
    std::string getType() const;
    void setTeamName(std::string teamname);
    std::string getTeamName() const;
};
#endif