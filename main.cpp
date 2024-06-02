#include <iostream>
typedef unsigned int normal;
class robot {
private:
    normal max_hp;
    normal max_ht;
    normal HP;
    normal HT;
    normal team;
    normal RobFlag;
public:
    void setMax_hp(normal n) {max_hp =n;}
    void setMax_ht(normal n) {max_ht = n;}
    void setHP(normal n) {HP = n;}
    void setHT(normal n) {HT = n;}
    void setTeam(normal n) {team = n;}
    void setRobotflag(normal n){RobFlag = n;}
    int Getmax_hp() {return max_hp;}
    int Getmax_ht() {return max_ht;}
    int GetHP() {return HP;}
    int GetHT() {return HT;}
    int GetTeam() {return team;}
    int GetRobflag() {return RobFlag;}
};

class infantry:private robot {

};
int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
