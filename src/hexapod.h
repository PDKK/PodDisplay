typedef struct {
    kmVec3 node[6];
} nodeset;

typedef struct {
    kmVec3 position;
    kmVec3 rotation;
} location;

typedef struct {
    nodeset base;
    nodeset middleBottom;
    nodeset middleTop;
    nodeset top;
    location baseLocation;
    location midLocation;
    location topLocation;
} doublepod;
