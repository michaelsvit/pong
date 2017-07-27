#pragma once
#include <map>

#define neonBlue al_map_rgb(103,200,255)

const int WIDTH = 800;
const int HEIGHT = 500;

enum ID{PLAYER, COMPUTER, BALL, POWERUP, BORDER};
extern std::map<int, bool> collisions;