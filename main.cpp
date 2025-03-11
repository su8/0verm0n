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
#include <cstdlib>
#include <string>
#include <cstring>
#include <unistd.h>
#include <functional>

int monsterHp, hp, atk, def, monsterAtk, monsterDef, hurt, monsterHurt, agi, monsterAgi;

static void adjustHumanAndMonster(int choice, int firstEntry);

int main(void) {
  time_t t;
  int choice;
  atk = 10;
  def = 15;
  agi = 5;
  monsterAtk = 10;
  monsterDef = 15;
  monsterAgi = 5;

  t = time(NULL);
  srandom(static_cast<unsigned int>(t) ^ static_cast<unsigned int>(getpid()));
  monsterHp = std::rand() % 50 + 60;
  hp = std::rand() % 20 + 80;

  while (hp > 0 || monsterHp > 0) {
    std::cout << "What do you want to do?\n1 - Normal Attack\n2 - Advanced Attack\n3 - Defensive moves\n" << std::flush;
    do { std::cin >> choice; } while (choice > 3 || choice < 1);

    adjustHumanAndMonster(choice, 1);
    adjustHumanAndMonster(std::rand() % 3, 0);

    monsterHurt = (atk - monsterAgi) - (monsterDef / atk);
    if (monsterHurt < 0) { monsterHurt = 0; }
    monsterHp -= monsterHurt;
    std::cout << "You did " << monsterHurt << " damage to the monster!\n" << std::flush;
    std::cin.get();
    if (monsterHp < 1) {
      std::cout << "You killed the beast!! You won with " << hp << " hp left.\n" << std::flush;
      return EXIT_SUCCESS;
    }

    std::cout << "The monster now have " << monsterHp << " hp left.\n" << std::flush;
    hurt = (monsterAtk - agi) - (def / monsterAtk);
    if (hurt < 0) { hurt = 0; }
    hp -= hurt;
    std::cout << "The monster hit you for " << hurt << " damage.\n" << std::flush;
    if (hp < 1) {
      std::cout << "You died. The beast still has " << monsterHp << " hp left.\n" << std::flush;
      return EXIT_SUCCESS;
    }
    std::cout << "You now have " << hp << " hp left.\n\n" << std::flush;
  }
  return EXIT_SUCCESS;
}

static void adjustHumanAndMonster(int choice, int HumanEntry) {
  int x = 0;
  static int arr[] = {
    rand() % (choice == 1) ? 20 + 10 : ((choice == 2) ? 5 + 10 : 10 + 10),
    rand() % (choice == 1) ? 10 + 10 : ((choice == 2) ? 10 + 10 : 20 + 10),
    rand() % (choice == 1) ? 5 : ((choice == 2) ? 15  : 5)
  };
  static std::reference_wrapper<int> HumanVars[] = { atk, def, agi };
  static std::reference_wrapper<int> MonsterVars[] = { monsterAtk, monsterDef, monsterAgi };

  if (HumanEntry == 1) { for (auto &z : HumanVars) { z.get() = arr[x++]; } return; }
  for (auto &z : MonsterVars) { z.get() = arr[x++]; }
}
