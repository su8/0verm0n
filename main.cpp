/*
Copyright 03/11/2025 https://github.com/su8/0verm0n
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
MA 02110-1301, USA.
*/
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <functional>
#include <string>

static void adjustHumanAndMonster(int choice, int HumanEntry);
int monsterHp, hp, atk, def, monsterAtk, monsterDef, hurt, monsterHurt, agi, monsterAgi;

int main(void) {
  time_t t;
  std::string str;
  int choice;
  atk = 10;
  def = 15;
  agi = 5;
  monsterAtk = 10;
  monsterDef = 15;
  monsterAgi = 5;

  t = std::time(0);
#ifdef _WIN32
  std::srand(t);
#else
  srandom(static_cast<unsigned int>(t) ^ static_cast<unsigned int>(getpid()));
#endif /*_WIN32 */
  monsterHp = std::rand() % 50 + 60;
  hp = std::rand() % 20 + 80;

  while (hp > 0 || monsterHp > 0) {
    std::cout << "What do you want to do?\n1 - \033[1;34mNormal Attack\033[0;0m\n2 - \033[1;33mAdvanced Attack\033[0;0m\n3 - \033[1;32mDefensive moves\033[0;0m\n" << std::flush;
    do {
      std::cin >> str;
      choice = static_cast<int>(std::strtol(str.c_str(), static_cast<char **>(NULL), 10));
    } while (choice > 3 || choice < 1);

    adjustHumanAndMonster(choice, 1);
    adjustHumanAndMonster(std::rand() % 3, 0);

    monsterHurt = (atk - monsterAgi) - (monsterDef / atk);
    if (monsterHurt < 0) { monsterHurt = 0; }
    monsterHp -= monsterHurt;
    std::cout << "You did \033[1;33m" << monsterHurt << " \033[0;0mdamage to the monster!\n" << std::flush;
    if (monsterHp < 1) {
      std::cout << "\033[1;32mYou killed the beast!!\033[0;0m You won with \033[1;32m" << hp << " \033[0;0mhp left.\n" << std::flush;
      return EXIT_SUCCESS;
    }
    std::cout << "The monster now have \033[1;31m" << monsterHp << " \033[0;0mhp left.\n" << std::flush;

    hurt = (monsterAtk - agi) - (def / monsterAtk);
    if (hurt < 0) { hurt = 0; }
    hp -= hurt;
    std::cout << "The monster hit you for \033[1;33m" << hurt << " \033[0;0mdamage.\n" << std::flush;
    if (hp < 1) {
      std::cout << "\033[1;31mYou died\033[0;0m. The beast still has \033[1;31m" << monsterHp << " \033[0;0mhp left.\n" << std::flush;
      return EXIT_SUCCESS;
    }
    std::cout << "You now have \033[1;32m" << hp << " \033[0;0mhp left.\n\n" << std::flush;
  }
  return EXIT_SUCCESS;
}

static void adjustHumanAndMonster(int choice, int HumanEntry) {
  unsigned short int x = 0U;
  int arr[] = { std::rand() % 20 + 10,
    std::rand() % (choice == 1 || choice == 2) ? 10 + 10 : 20 + 10,
    std::rand() % (choice == 2) ? 15 : 5
  };
  static std::reference_wrapper<int> HumanVars[] = { atk, def, agi };
  static std::reference_wrapper<int> MonsterVars[] = { monsterAtk, monsterDef, monsterAgi };

  if (HumanEntry == 1) { for (auto &z : HumanVars) { z.get() = arr[x++]; } return; }
  for (auto &z : MonsterVars) { z.get() = arr[x++]; }
}