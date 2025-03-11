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

int mhp, hp, atk, def, matk, mdef, hurt, mhurt, agi, magi;

static void adjustHuman(int choice);
static void adjustMonster(int choice);

int main(void) {
  int choice;
  atk = 10;
  def = 15;
  agi = 5;
  matk = 10;
  mdef = 15;
  magi = 5;

  srand((unsigned int)time(0));
  mhp = std::rand() % 50 + 60;
  hp = std::rand() % 20 + 80;
  std::cout << "You start.\n==========\n" << std::flush;
  while (hp > 0 || mhp > 0) {
    std::cout << "What do you want to do?\n1 - Normal Attack\n2 - Advanced Attack\n3 - Defensive moves\n" << std::flush;
    do {
      std::cin >> choice;
    } while (choice > 3 || choice < 1);

    adjustHuman(choice);
    adjustMonster(std::rand() % 3);

    mhurt = (atk - magi) - (mdef / atk);
    if (mhurt < 0) {
      mhurt = 0;
    }
    mhp -= mhurt;
    std::cout << "You did " << mhurt << " damage to the monster!\n" << std::flush;
    std::cin.get();
    if (mhp < 1) {
      std::cout << "You killed the beast!! You won with " << hp << " hp left.\n" << std::flush;
      std::cin.get();
      return EXIT_SUCCESS;
    }

    std::cout << "The monster now have " << mhp << " hp left.\n" << std::flush;
    hurt = (matk - agi) - (def / matk);
    if (hurt < 0) {
      hurt = 0;
    }
    hp -= hurt;
    std::cout << "The monster hit you for " << hurt << " damage.\n" << std::flush;
    if (hp < 1) {
      std::cout << "You died. The beast still has " << mhp << " hp left.\n" << std::flush;
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
  matk = rand() % (choice == 1) ? 20 + 10 : ((choice == 2) ? 5 + 10 : 10 + 10);
  mdef = rand() % (choice == 1) ? 10 + 10 : ((choice == 2) ? 10 + 10 : 20 + 10);
  magi = rand() % (choice == 1) ? 5 : ((choice == 2) ? 15  : 5);
}
