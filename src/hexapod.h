
typedef struct {
    kmVec3 node[6];
    kmVec3 position;
    kmVec3 rotation;
} top_bottom_location_t;

typedef struct {
    kmVec3 lowerNode[6];
    kmVec3 upperNode[6];
    kmVec3 position;
    kmVec3 rotation;
} middle_location_t;

typedef struct {
    top_bottom_location_t baseLocation;
    middle_location_t midLocation;
    top_bottom_location_t topLocation;
} doublepod;


void drawDoublePod(doublepod * pod); 
void initDoublePod(doublepod * pod); 
