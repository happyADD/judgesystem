//
// Created by dcy on 24-6-3.
//

#ifndef ROBOT_H
#define ROBOT_H
#include <algorithm>
#include <vector>
using namespace std;

typedef unsigned int normal;

class robot {
protected:
    normal time; //上次更新状态的时间
    normal max_hp;
    normal max_ht;
    normal HP;
    normal HT;
    normal team;
    normal RobFlag; //标识符
    normal RobType;
    normal Level;

public:
    robot() {
        time = 0;
        max_hp = 0;
        max_ht = 0;
        HP = 0;
        HT = 0;
        team = 0;
        RobType = 65535;
        RobFlag = 65535;
        Level = 0;
    }

    void settime(normal n) { time = n; }
    void setMax_hp(normal n) { max_hp = n; }
    void setMax_ht(normal n) { max_ht = n; }
    void deHP(normal n) { HP -= n; } //n扣除血量
    void setHP(normal n) { HP = n; }
    void setHT(normal n) { HT += n; }
    void setTeam(normal n) { team = n; }
    void setRobotflag(normal n) { RobFlag = n; }
    void setRobotType(normal n) { RobType = n; }
    void setLv(normal n) { Level = n; }
    normal Gettime() { return time; }
    normal Getmax_hp() { return max_hp; }
    normal Getmax_ht() { return max_ht; }
    normal GetHP() { return HP; }
    normal GetHT() { return HT; }
    normal GetTeam() const { return team; }
    normal GetRobflag() const { return RobFlag; }
    normal GetRobType() const { return RobType; }
    normal GetLv() const { return Level; }
};

class soldier : virtual robot {
    //0
public:
    soldier(): robot() {
        setMax_hp(100);
        setHP(100);
        setMax_ht(100);
        setHT(0);
        setLv(1);
    }
};

class engine : virtual robot {
    //1
public:
    engine(): robot() {
        setMax_hp(300);
        setHP(300);
        setMax_ht(0);
        setHT(0);
        setLv(0);
    }
};

class Manage {
    static std::vector<robot> All;
    static normal robnum; //机器人数量
public:
    static void setrobnum(normal n) { robnum = n; }
    static normal getrobnum() { return robnum; }

    static void soldierinit() {
        All.back().setMax_hp(300);
        All.back().setHP(300);
        All.back().setMax_ht(0);
        All.back().setHT(0);
        All.back().setLv(0);
    }

    static void engineinit() {
        All.back().setMax_hp(100);
        All.back().setHP(100);
        All.back().setMax_ht(100);
        All.back().setHT(0);
        All.back().setLv(1);
    }

    friend __gnu_cxx::__normal_iterator<robot *, vector<robot> > findrobot(normal te, normal robflag);

    friend void Addrobot(normal, normal, normal);

    friend void RefreshState(normal);

    friend void loseHP(normal, normal, normal, normal);

    friend void riseHT(normal, normal, normal, normal);

    friend void setlevel(normal, normal, normal, normal);
};

void RobDeath(robot &ptr);

bool is_overheat(robot *ptr);

void RefreshState(normal ti);

void Addrobot(normal, normal, normal, normal);

void loseHP(normal, normal, normal, normal);

void riseHT(normal, normal, normal, normal);

void setlevel(normal, normal, normal, normal);

void commandin();

bool commandtrue(char c);


#endif //ROBOT_H
