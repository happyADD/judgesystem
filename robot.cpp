#include "robot.h"
#include <algorithm>
#include <iostream>
//
// Created by dcy on 24-6-3.
//

std::vector<robot> Manage::All;
std::vector<robot> Manage::Dead;
normal Manage::liverob = 0;

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
                            return r.GetTeam() == te && r.GetRobflag() == robflag && r.Getstate();
                        });
} //AI

__gnu_cxx::__normal_iterator<robot *, vector<robot> > findDeath(normal te, normal robflag) {
    return std::find_if(Manage::Dead.begin(), Manage::Dead.end(),
                        [=](const robot &r) {
                            return r.GetTeam() == te && r.GetRobflag() == robflag;
                        });
}

/**
 * @brief 问题在于如何有效的删除All的容器内的对象？
 *
 */
void RobDeath(robot &it) {
    it.setHP((0));
    it.die();
    //Manage::Dead.emplace_back(it);
    // Manage::Dead.back().setTeam(it.GetTeam());
    // Manage::Dead.back().setRobotflag(it.GetRobflag());
    Manage::liverob--;
    std::cout << "D " << it.GetTeam() << ' ' << it.GetRobflag() << endl;
}


bool is_overheat(robot *ptr) {
    if(ptr->Getmax_ht() <= ptr->GetHT() && ptr->GetRobType() == 0) return true;
    return false;
}

/**
 * @brief 新建一个迭代器，指向All容器，判断是否过热，在判断是否会导致死亡；
 *        导致死亡就调用死亡处理函数，传入当前迭代器和迭代器指向的对象成员；
 *        此时的迭代器begin（）？？应该就是？？需要移动到Death的对象成员；
 *
 *        应当传入时间，可能出现两个时间间隔中过热状态的变化
 *
 *        使用了大于300的奇技淫巧
 * @param ti time
 */
void RefreshState(normal ti) {
    for (auto &it: Manage::All) {
        if(it.Getstate())
        if(is_overheat(&it)) {
            // if(ti - it.Gettime()>it.GetHT()-it.Getmax_ht()) it.deHP(it.GetHT()-it.Getmax_ht());
            // else it.deHP(ti - it.Gettime());
            it.deHP(min(ti - it.Gettime(),it.GetHT()-it.Getmax_ht()));//简化写法，扣除血量应当为 时间间隔和热量超量 的较小值
            if(it.GetHP() > 301) RobDeath(it);
        }//血量处理
        if(it.GetHT() >= ti - it.Gettime())
            it.setHT(it.GetHT() - (ti - it.Gettime()));//HT
        else it.setHT(0);
        //热量处理
        it.settime(ti);
        //时间处理
        /*if (is_overheat(&it)) {
            if (min(ti - it.Gettime(),it.GetHT()-it.Getmax_ht()) >= it.GetHP() && !it.Getstate()) {
                RobDeath(it);
            } else {
                it.deHP(min(ti - it.Gettime(),it.GetHT()-it.Getmax_ht()));
            }
        }//de HP
        if(it.GetHT() >= ti - it.Gettime())
            it.setHT(it.GetHT() - (ti - it.Gettime()));//HT
        else it.setHT(0);
        it.settime(ti);*/
    }
}

void Addrobot(normal ti,normal te, normal robflag, normal robottype) {
    if (findrobot(te, robflag) == Manage::All.end()) {
        Manage::All.emplace_back(); // 新对象
        Manage::All.back().settime(ti);
        Manage::All.back().setTeam(te);
        Manage::All.back().setRobotflag(robflag);
        Manage::All.back().setRobotType(robottype);
        if (robottype == 0) Manage::soldierinit();
        else if (robottype == 1) Manage::engineinit();
        Manage::liverob++; // 增加机器人数量
    }
}

void loseHP(normal te, normal robflag, normal Hp) {
    auto t = findrobot(te, robflag);
    if (t != Manage::All.end()) {
        if (t->GetHP() <= Hp) RobDeath(*t); //RobDeath((*t));
        else t->deHP(Hp);
    }
}

void riseHT(normal te, normal robflag, normal Ht) {
    auto t = findrobot(te, robflag);
    if (t->GetRobType() == 0) t->upHT(Ht);
}

void setlevel(normal te, normal robflag, normal lv) {
    auto t = findrobot(te, robflag);
    if (t->GetLv() <= lv && t->Getstate() && lv<=3) {
        t->setLv(lv);
        if (t->GetRobType() == 1) {
            if (lv == 2) {
                t->setMax_hp(150);
                t->setMax_ht(200);
                t->setHP(150);
            } else if (lv == 3) {
                t->setMax_hp(250);
                t->setMax_ht(300);
                t->setHP(250);
            }
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
                Addrobot(time,para1, para2, para3);
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

void Manage::DeathReport() {
    for (auto it: Manage::All) {
        if (!it.Getstate()) cout << "D " << it.GetTeam() << ' ' << it.GetRobflag() << endl;
    }
}
