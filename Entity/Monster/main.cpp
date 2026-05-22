#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Goblin.h"
#include "Orc.h"
#include "Troll.h"
#include "Slime.h"

using namespace std;

int main()
{
    srand((unsigned int)time(NULL));

    int playerLevel = 1;
    char input;

    Goblin goblin(playerLevel);
    Orc orc(playerLevel);
    Troll troll(playerLevel);
    Slime slime(playerLevel);


    while (true)
    {
        cout << "\n===== 몬스터 상태 =====\n";
        cout << "현재 플레이어 레벨: " << playerLevel << "\n\n";

        cout << goblin.GetName() << " | 체력: " << goblin.GetHealth()
            << " | 공격력: " << goblin.GetAttack() << endl;

        cout << orc.GetName() << " | 체력: " << orc.GetHealth()
            << " | 공격력: " << orc.GetAttack() << endl;

        cout << troll.GetName() << " | 체력: " << troll.GetHealth()
            << " | 공격력: " << troll.GetAttack() << endl;

        cout << slime.GetName() << " | 체력: " << slime.GetHealth()
            << " | 공격력: " << slime.GetAttack() << endl;

        cout << "\n========================\n";
        cout << "A : 몬스터 공격\n";
        cout << "R : 몬스터 새로 고침\n";
        cout << "E : 플레이어 레벨 변경\n";
        cout << "Q : 종료\n";
        cout << "입력 : ";

        cin >> input;

        if (input == 'a' || input == 'A')
        {
            goblin.Attack();
            orc.Attack();
            troll.Attack();
            slime.Attack();
        }
        else if (input == 'r' || input == 'R')
        {
            goblin = Goblin(playerLevel);
            orc = Orc(playerLevel);
            troll = Troll(playerLevel);
            slime = Slime(playerLevel);
        }
        else if (input == 'e' || input == 'E')
        {
            cout << "\n변경할 플레이어 레벨 입력 : ";
            cin >> playerLevel;

            if (playerLevel < 1)
                playerLevel = 1;

            cout << "\n플레이어 레벨이 " << playerLevel << "(으)로 변경되었습니다.\n";

            goblin = Goblin(playerLevel);
            orc = Orc(playerLevel);
            troll = Troll(playerLevel);
            slime = Slime(playerLevel);
        }
        else if (input == 'q' || input == 'Q')
        {
            cout << "\n프로그램 종료\n";
            break;
        }
        else
        {
            cout << "\n잘못된 입력입니다.\n";
        }
    }

    return 0;
}