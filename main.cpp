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

int monsterHp, hp, atk, def, monsterAtk, monsterDef, hurt, monsterHurt, agi, monsterAgi;

static void adjustHuman(int choice);
static void adjustMonster(int choice);

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
  srandom((unsigned int)t ^ (unsigned int)getpid());
  monsterHp = std::rand() % 50 + 60;
  hp = std::rand() % 20 + 80;

  while (hp > 0 || monsterHp > 0) {
    std::cout << "What do you want to do?\n1 - Normal Attack\n2 - Advanced Attack\n3 - Defensive moves\n" << std::flush;
    do {
      std::cin >> choice;
    } while (choice > 3 || choice < 1);

    adjustHuman(choice);
    adjustMonster(std::rand() % 3);

    monsterHurt = (atk - monsterAgi) - (monsterDef / atk);
    if (monsterHurt < 0) {
      monsterHurt = 0;
    }
    monsterHp -= monsterHurt;
    std::cout << "You did " << monsterHurt << " damage to the monster!\n" << std::flush;
    std::cin.get();
    if (monsterHp < 1) {
      std::cout << "You killed the beast!! You won with " << hp << " hp left.\n" << std::flush;
      std::cin.get();
      return EXIT_SUCCESS;
    }

    std::cout << "The monster now have " << monsterHp << " hp left.\n" << std::flush;
    hurt = (monsterAtk - agi) - (def / monsterAtk);
    if (hurt < 0) {
      hurt = 0;
    }
    hp -= hurt;
    std::cout << "The monster hit you for " << hurt << " damage.\n" << std::flush;
    if (hp < 1) {
      std::cout << "You died. The beast still has " << monsterHp << " hp left.\n" << std::flush;
      std::cin.get();
      return EXIT_SUCCESS;
    }
    std::cout << "You now have " << hp << " hp left.\n\n" << std::flush;
  }
  return EXIT_SUCCESS;
}

static void adjustHuman(int choice) {
  atk = rand() % (choice == 1) ? 20 + 10 : ((choice == 2) ? 5 + 10 : 10 + 10);
  def = rand() % (choice == 1) ? 10 + 10 : ((choice == 2) ? 10 + 10 : 20 + 10);
  agi = rand() % (choice == 1) ? 5 : ((choice == 2) ? 15  : 5);
}

static void adjustMonster(int choice) {
  monsterAtk = rand() % (choice == 1) ? 20 + 10 : ((choice == 2) ? 5 + 10 : 10 + 10);
  monsterDef = rand() % (choice == 1) ? 10 + 10 : ((choice == 2) ? 10 + 10 : 20 + 10);
  monsterAgi = rand() % (choice == 1) ? 5 : ((choice == 2) ? 15  : 5);
}
