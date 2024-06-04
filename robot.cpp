#include "robot.h"
#include <algorithm>
#include <iostream>
//
// Created by dcy on 24-6-3.
//

std::vector<robot> Manage::All;
normal Manage::robnum = 0;

void Addrobot(normal te, normal robflag, normal robottype) {
    if (robottype == 0) {
        Manage::All.emplace_back(); // 新对象
        Manage::All.back().setTeam(te);
        Manage::All.back().setRobotflag(robflag);
        Manage::All.back().setRobotType(robottype);
        Manage::soldierinit();
        Manage::robnum++; // 增加机器人数量
    }else if(robottype == 1) {
        Manage::All.emplace_back(); // 新对象
        Manage::All.back().setTeam(te);
        Manage::All.back().setRobotflag(robflag);
        Manage::All.back().setRobotType(robottype);
        Manage::engineinit();
        Manage::robnum++; // 增加机器人数量
    }
}
/**
 *newknlge：
 * auto shuaaaang!
 * 此处auto的类型是某种迭代器（好像）
 * [=] 使得lambda表达式中的变量能看见全局变量，全局变量所以class robot中相关成员函数使用静态函数
 * lambda表达式：[capture-list](parameter-list) -> return-type { function-body }//类似现场定义现场使用的函数；
 */
__gnu_cxx::__normal_iterator<robot*,vector<robot>> findrobot(normal te, normal robflag) {
    return std::find_if(Manage::All.begin(), Manage::All.end(),
                          [=](const robot& r) {
                              return r.GetTeam() == te && r.GetRobflag() == robflag;
                          });
}

void loseHP(normal te, normal robflag, normal Hp) {

    findrobot(te,robflag)->deHP(Hp);
}//AI

void riseHT(normal te, normal robflag, normal Ht) {
    findrobot(te,robflag)->setHT(Ht);
}

void setlevel(normal te, normal robflag, normal lv) {
    findrobot(te,robflag)->setLv(lv);
}

bool commandtrue(char c) {
    if (c == 'A' || c == 'F' || c == 'U' || c == 'H') return true;
    return false;
}

void commandin() {
    char command;
    normal time,para1, para2, para3;
    std::cin>>time;
    std::cin>>command>>para1>>para2>>para3;
    if(commandtrue(command))
    switch (command) {
        case 'A':
            Addrobot(para1, para2, para3);
            break;
        case 'F':
            loseHP(para1, para2, para3);
            break;
        case 'U':
            riseHT(para1, para2, para3);
            break;
        case 'H':
            setlevel(para1, para2, para3);
            break;
        default:;
    }
}
