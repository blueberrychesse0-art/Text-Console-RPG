#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Goblin.h"
#include "Orc.h"
#include "Troll.h"
#include "Slime.h"

using namespace std;

void createMonsters(int playerLevel)
{
    Goblin goblin(playerLevel);
    Orc orc(playerLevel);
    Troll troll(playerLevel);
    Slime slime(playerLevel);

    cout << "\n===== 몬스터 생성 =====\n";
    cout << "현재 플레이어 레벨: " << playerLevel << "\n\n";

    cout << goblin.getName()
        << " | 체력: " << goblin.getHealth()
        << " | 공격력: " << goblin.getAttack() << endl;

    cout << orc.getName()
        << " | 체력: " << orc.getHealth()
        << " | 공격력: " << orc.getAttack() << endl;

    cout << troll.getName()
        << " | 체력: " << troll.getHealth()
        << " | 공격력: " << troll.getAttack() << endl;

    cout << slime.getName()
        << " | 체력: " << slime.getHealth()
        << " | 공격력: " << slime.getAttack() << endl;
}

int main()
{
    srand((unsigned int)time(NULL));

    int playerLevel = 1;
    char input;

    createMonsters(playerLevel);

    while (true)
    {
        cout << "\n========================\n";
        cout << "R : 몬스터 새로고침\n";
        cout << "E : 플레이어 레벨 변경\n";
        cout << "Q : 종료\n";
        cout << "입력 : ";

        cin >> input;

        if (input == 'r' || input == 'R')
        {
            createMonsters(playerLevel);
        }
        else if (input == 'e' || input == 'E')
        {
            cout << "\n변경할 플레이어 레벨 입력 : ";
            cin >> playerLevel;

            if (playerLevel < 1)
            {
                playerLevel = 1;
            }

            cout << "\n플레이어 레벨이 "
                << playerLevel
                << "(으)로 변경되었습니다.\n";

            createMonsters(playerLevel);
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