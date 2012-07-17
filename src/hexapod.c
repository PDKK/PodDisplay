
#include "support.h"		// support routines
#include "keys.h"		// defines key indexes for key down boolean array
#include "obj.h"		// loading and displaying wavefront OBJ derived shapes
#include "input.h"
#include "primitive.h"

#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>		// usleep

#include <kazmath.h>		// matrix manipulation routines

#include "hexapod.h"

void initDoublePod(doublepod * pod) {
    kmVec3Fill(&pod->baseLocation.position, 1,1,0);
}

void placePlatform(doublepod * pod, kmVec3 * position, kmVec3 * rotation) {
    
}

void drawDoublePod(doublepod * pod) {
}
