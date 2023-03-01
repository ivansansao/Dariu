#ifndef TOOLS_H
#define TOOLS_H

class Tools {
   public:
    Tools();

    static int getStartSprite(int, int);
    static float ceil_special(float num, float biggerthan);
    static float floor_special(float num, float lessthan);
};
#endif
