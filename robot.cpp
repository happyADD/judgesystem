#include "robot.h"
#include <algorithm>
#include <iostream>
//
// Created by dcy on 24-6-3.
//

std::vector<robot> Manage::All;
normal Manage::robnum = 0;

/**
 *newknlge：
 * auto shuaaaang!
 * 此处auto的类型是某种迭代器（好像）
 * [=] 使得lambda表达式中的变量能看见全局变量，全局变量所以class robot中相关成员函数使用静态函数
 * lambda表达式：[capture-list](parameter-list) -> return-type { function-body }//类似现场定义现场使用的函数；
 */
__gnu_cxx::__normal_iterator<robot *, vector<robot> > findrobot(normal te, normal robflag) {
    return std::find_if(Manage::All.begin(), Manage::All.end(),
                        [=](const robot &r) {
                            return r.GetTeam() == te && r.GetRobflag() == robflag;
                        });
} //AI

void RobDeath(robot &ptr) {
    std::cout << "D " << ptr.GetTeam() << ' ' << ptr.GetRobflag() << endl;
    ptr.setHP(0);
}

bool is_overheat(robot *ptr) {
    if (ptr->Getmax_ht() >= ptr->GetHT()) return true;
    return false;
}


void RefreshState(normal ti) {
    for (auto &it: Manage::All) {
        if (is_overheat(&it)) {
            if (ti - it.Gettime() >= it.GetHP()) RobDeath(it);
            else it.deHP(ti - it.Gettime());
        }
        it.settime(ti);
    }
}

void Addrobot(normal te, normal robflag, normal robottype) {
    if (findrobot(te, robflag) == Manage::All.end()) {
        Manage::All.emplace_back(); // 新对象
        Manage::All.back().setTeam(te);
        Manage::All.back().setRobotflag(robflag);
        Manage::All.back().setRobotType(robottype);
        if (robottype == 0) Manage::soldierinit();
        else if (robottype == 1) Manage::engineinit();
        Manage::robnum++; // 增加机器人数量
    }
}

void loseHP(normal te, normal robflag, normal Hp) {
    auto t = findrobot(te, robflag);
    if (t != Manage::All.end()) {
        if (t->GetHP() <= Hp) RobDeath((*t));
        else t->deHP(Hp);
    }
}

void riseHT(normal te, normal robflag, normal Ht) {
    auto t = findrobot(te, robflag);
    if (t->GetRobType() == 0) t->setHT(Ht);
}

void setlevel(normal te, normal robflag, normal lv) {
    auto t = findrobot(te, robflag);
    if (t->GetRobType() == 0 && t->GetLv() <= lv) {
        t->setLv(lv);
        if (lv == 2) {
            t->setMax_hp(150);
            t->setMax_ht(200);
        } else if (lv == 3) {
            t->setMax_hp(250);
            t->setMax_ht(300);
        }
    }
}

bool commandtrue(char c) {
    if (c == 'A' || c == 'F' || c == 'U' || c == 'H') return true;
    return false;
}

void commandin() {
    char command;
    normal time, para1, para2, para3;
    std::cin >> time;
    RefreshState(time);
    std::cin >> command >> para1 >> para2 >> para3;
    if (commandtrue(command))
        switch (command) {
            case 'A':
                Addrobot(para1, para2, para3);
                break;
            case 'F':
                loseHP(para1, para2, para3);
                break;
            case 'H':
                riseHT(para1, para2, para3);
                break;
            case 'U':
                setlevel(para1, para2, para3);
                break;
            default: ;
        }
}
