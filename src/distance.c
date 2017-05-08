#ifndef distance_
#define distance_

#define getDistance getDistance__perimeter
// #define getDistance getDistance__linear
// #define getDistance getDistance__oneComponent

#define _dargs int x1, int x2, int y1, int y2

int getDistance__perimeter(_dargs) {
  return abs(x1 - x2) + abs(y1 - y2);
}

int getDistance__linear(_dargs) {
  return sqrt(((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2)));
}

int getDistance__oneComponent(_dargs) {
  return abs(x1 - x2);
}


#endif