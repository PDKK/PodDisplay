

// turned into a lighting test as 6 planes (a cube) is not idea for // checking frag lighting, there is also a sphere

// press Q & W
// and A & S to rotate the camera and light


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
#define DEGREES_TO_RADIANS(x) ((x)*3.141592654/180.0)

unsigned int cubeNumVerts = 36;

float cubeVerts[] = {
    // f 1/1/1 2/2/1 3/3/1
    0.5, -0.5, -0.5,	0.5, -0.5, 0.5,	-0.5, -0.5, 0.5,
    // f 1/1/1 3/3/1 4/4/1
    0.5, -0.5, -0.5,	-0.5, -0.5, 0.5,	-0.5, -0.5, -0.5,
    // f 5/5/2 8/6/2 7/7/2
    0.5, 0.5, -0.5,	-0.5, 0.5, -0.5,	-0.5, 0.5, 0.5,
    // f 5/5/2 7/7/2 6/8/2
    0.5, 0.5, -0.5,	-0.5, 0.5, 0.5,	0.5, 0.5, 0.5,
    // f 1/9/3 5/10/3 6/11/3
    0.5, -0.5, -0.5,	0.5, 0.5, -0.5,	0.5, 0.5, 0.5,
    // f 1/9/3 6/11/3 2/12/3
    0.5, -0.5, -0.5,	0.5, 0.5, 0.5,	0.5, -0.5, 0.5,
    // f 2/13/4 6/14/4 7/15/4
    0.5, -0.5, 0.5,	0.5, 0.5, 0.5,	-0.5, 0.5, 0.5,
    // f 2/13/4 7/15/4 3/16/4
    0.5, -0.5, 0.5,	-0.5, 0.5, 0.5,	-0.5, -0.5, 0.5,
    // f 3/17/5 7/18/5 8/19/5
    -0.5, -0.5, 0.5,	-0.5, 0.5, 0.5,	-0.5, 0.5, -0.5,
    // f 3/17/5 8/19/5 4/20/5
    -0.5, -0.5, 0.5,	-0.5, 0.5, -0.5,	-0.5, -0.5, -0.5,
    // f 5/21/6 1/22/6 4/23/6
    0.5, 0.5, -0.5,	0.5, -0.5, -0.5,	-0.5, -0.5, -0.5,
    // f 5/21/6 4/23/6 8/24/6
    0.5, 0.5, -0.5,	-0.5, -0.5, -0.5,	-0.5, 0.5, -0.5,
};

float cubeNormals[] = {
    // f 1/1/1 2/2/1 3/3/1
    0, -1, 0,    0, -1, 0,    0, -1, 0,
    // f 1/1/1 3/3/1 4/4/1
    0, -1, 0,    0, -1, 0,    0, -1, 0,
    // f 5/5/2 8/6/2 7/7/2
    0, 1, 0,    0, 1, 0,    0, 1, 0,
    // f 5/5/2 7/7/2 6/8/2
    0, 1, 0,    0, 1, 0,    0, 1, 0,
    // f 1/9/3 5/10/3 6/11/3
    1, 0, 0,    1, 0, 0,    1, 0, 0,
    // f 1/9/3 6/11/3 2/12/3
    1, 0, 0,    1, 0, 0,    1, 0, 0,
    // f 2/13/4 6/14/4 7/15/4
    0, 0, 1,    0, 0, 1,    0, 0, 1,
    // f 2/13/4 7/15/4 3/16/4
    0, 0, 1,    0, 0, 1,    0, 0, 1,
    // f 3/17/5 7/18/5 8/19/5
    -1, 0, 0,    -1, 0, 0,    -1, 0, 0,
    // f 3/17/5 8/19/5 4/20/5
    -1, 0, 0,    -1, 0, 0,    -1, 0, 0,
    // f 5/21/6 1/22/6 4/23/6
    0, 0, -1,    0, 0, -1,    0, 0, -1,
    // f 5/21/6 4/23/6 8/24/6
    0, 0, -1,    0, 0, -1,    0, 0, -1,
};

float cubeTexCoords[] = {
    // f 1/1/1 2/2/1 3/3/1
    0.338526, 0.661474,    0.663522, 0.661474,    0.663522, 0.336478,
    // f 1/1/1 3/3/1 4/4/1
    0.338526, 0.661474,    0.663522, 0.336478,    0.338526, 0.336478,
    // f 5/5/2 8/6/2 7/7/2
    0.005288, 0.994712,    0.329713, 0.994712,    0.329713, 0.670287,
    // f 5/5/2 7/7/2 6/8/2
    0.005288, 0.994712,    0.329713, 0.670287,    0.005288, 0.670287,
    // f 1/9/3 5/10/3 6/11/3
    0.993727, 0.337651,    0.670272, 0.337651,    0.670272, 0.661106,
    // f 1/9/3 6/11/3 2/12/3
    0.993727, 0.337651,    0.670272, 0.661106,    0.993727, 0.661106,
    // f 2/13/4 6/14/4 7/15/4
    0.337449, 0.995051,    0.663207, 0.995051,    0.663338, 0.669686,
    // f 2/13/4 7/15/4 3/16/4
    0.337449, 0.995051,    0.663338, 0.669686,    0.337711, 0.669162,
    // f 3/17/5 7/18/5 8/19/5
    0.004502, 0.663184,    0.331568, 0.663184,    0.331568, 0.336118,
    // f 3/17/5 8/19/5 4/20/5
    0.004502, 0.663184,    0.331568, 0.336118,    0.004408, 0.336118,
    // f 5/21/6 1/22/6 4/23/6
    0.338744, 0.329745,    0.664703, 0.329745,    0.664703, 0.004606,
    // f 5/21/6 4/23/6 8/24/6
    0.338744, 0.329745,    0.664703, 0.004606,    0.338744, 0.004606,
};




void render();			// func prototype

// obj shape textures
GLuint cubeTex,ballTex;

// structures holding various pointers and handles for obj shapes
struct obj_t cubeObj,ballObj,cylObj;

// matrices and combo matrices
kmMat4 model, view, projection, mvp, vp, mv;

int frame = 0;
kmVec3 lightDir, viewDir; // vectors for shader lighting
kmVec3 pEye, pCenter, pUp;	// "camera" vectors
// from position , target position and up direction

float camAng,lightAng;

bool *keys;
int *mouse;
struct joystick_t *joy1;

doublepod pod;

int main()
{
	float deltaMove;
	GLfloat size, aspectRatio;
    // creates a window and GLES context
    if (makeContext() != 0)
        exit(-1);

    // all the shaders have at least texture unit 0 active so
    // activate it now and leave it active
    glActiveTexture(GL_TEXTURE0);

    // The obj shapes and their textures are loaded
    // directly from embedded data in the executable
    cubeTex = loadPNG("resources/textures/grey.png");
    createObj(&cubeObj, cubeNumVerts, cubeVerts, cubeTexCoords, cubeNormals,
              "resources/shaders/textured.vert", "resources/shaders/textured.frag");

    createCylinder(&cylObj);

    // embedding data can waste precious ram, loading from disk is more efficient
    // no redundant data left when verts transfered to GPU
    loadObjCopyShader(&ballObj,"resources/models/sphere.gbo",&cubeObj);
    ballTex = loadPNG("resources/textures/red.png");

    initDoublePod(&pod); 

    kmMat4Identity(&view);

    pEye.x = 5;
    pEye.y = -5;
    pEye.z = 5;
    pCenter.x = 0;
    pCenter.y = 0;
    pCenter.z = 0;
    pUp.x = 0;
    pUp.y = 0;
    pUp.z = 1;

    kmVec3Subtract(&viewDir,&pEye,&pCenter);
    kmVec3Normalize(&viewDir,&viewDir);

    kmMat4LookAt(&view, &pEye, &pCenter, &pUp);

    // these two matrices are pre combined for use with each model render
    // the view and projection
    kmMat4Assign(&vp, &projection);
    kmMat4Multiply(&vp, &vp, &view);

    // projection matrix, as distance increases
    // the way the model is drawn is effected
    kmMat4Identity(&projection);
    kmMat4PerspectiveProjection(&projection, 45,
                                (float)getDisplayWidth() / getDisplayHeight(), 0.1, 20);

    glViewport(0, 0, getDisplayWidth(), getDisplayHeight());
    // initialises glprint's matrix, shader and texture
    initGlPrint(getDisplayWidth(), getDisplayHeight());

    // we don't want to draw the back of triangles
    // the blending is set up for glprint but disabled
    // while not in use
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    
    glClearColor(0.7, 0.7, 0.7, 1);
    glClearDepthf(1.0);

    // count each frame
    int num_frames = 0;

    // set to true to leave main loop
    bool quit = false;

    // get a pointer to the key down array
    keys = getKeys();
    mouse = getMouse();
    joy1=getJoystick(0);
    //setMouseRelative(true);

    while (!quit) {		// the main loop

        doEvents();	// update mouse and key arrays
        updateJoystick(joy1);

        if (keys[KEY_ESC])
            quit = true;	// exit if escape key pressed

        if (keys[KEY_A]) camAng=camAng+1;
        if (keys[KEY_S]) camAng=camAng-1;
        if (keys[KEY_W]) lightAng=lightAng+1;
        if (keys[KEY_Q]) lightAng=lightAng-1;
        deltaMove = keys[KEY_LSHIFT] ? 0.01 : -0.01;
        if (keys[KEY_X]) pod.topLocation.position.x += deltaMove;
        if (keys[KEY_Y]) pod.topLocation.position.y += deltaMove;
        if (keys[KEY_Z]) pod.topLocation.position.z += deltaMove;
        placePlatform(&pod, &pod.topLocation.position, &pod.topLocation.position);
        render();	// the render loop

        usleep(16000);	// no need to run cpu/gpu full tilt

    }

    closeContext();		// tidy up
	releaseJoystick(joy1);

    return 0;
}

int rmx,rmy;


void createCylinderMatrix(kmMat4 * model, float x1, float y1, float z1, float x2, float y2, float z2)
{
    kmMat4 scaleMatrix;
    kmMat4 rotateMatrix;
    kmVec3 v1, v2, diff, cross;
    float dx = x2 - x1;
    float dy = y2 - y1;
    float dz = z2 - z1;
    float l = sqrt(dx*dx + dy*dy + dz*dz);
    float ry = asin(dz/l);
    float rz = atan(dy/dx);
    float dotProduct;

    kmVec3Fill(&v1, x2-x1, y2-y1, z2-z1);
    kmVec3Normalize(&v1, &v1);
    kmVec3Fill(&v2, 0, 0, 1);
    kmVec3Cross(&cross, &v2, &v1);
    dotProduct = kmVec3Dot(&v1,&v2);
    if (abs(dotProduct) > 0.99999999) {
        kmMat4Identity(&rotateMatrix);
    } else {
        kmMat4RotationAxisAngle(&rotateMatrix, &cross, acos(dotProduct));
    }
    kmMat4Scaling(&scaleMatrix, 0.1, 0.1, l);
    kmMat4Translation(model, x1, y1, z1);
    kmMat4Multiply(model, model, &rotateMatrix);
    kmMat4Multiply(model, model, &scaleMatrix);
}


void renderLegWithJoints(float x1, float y1, float z1, float x2, float y2, float z2) {
    kmMat4 scaleMatrix;
    createCylinderMatrix(&model, x1, y1, z1, x2, y2, z2);
    kmMat4Assign(&mvp, &vp);
    kmMat4Multiply(&mvp, &mvp, &model);	// model, view, projection combined matrix
    kmMat4Assign(&mv, &view);
    kmMat4Multiply(&mv, &mv, &model);	// view, model matrix for lighting
    glBindTexture(GL_TEXTURE_2D, cubeTex);
    drawObj(&cylObj, &mvp, &mv,lightDir,viewDir);
//	----
    kmMat4Identity(&model);
    kmMat4Translation(&model, x1, y1, z1);
    kmMat4Scaling(&scaleMatrix, 0.05, 0.05, 0.05);
    kmMat4Multiply(&model, &model, &scaleMatrix);	// model, view, projection combined matrix
    kmMat4Assign(&mvp, &vp);
    kmMat4Multiply(&mvp, &mvp, &model);	// model, view, projection combined matrix
    kmMat4Assign(&mv, &view);
    kmMat4Multiply(&mv, &mv, &model);	// view, model matrix for lighting
    glBindTexture(GL_TEXTURE_2D, ballTex);
    drawObj(&ballObj, &mvp, &mv,lightDir,viewDir);
//	----
    kmMat4Identity(&model);
    kmMat4Translation(&model, x2, y2, z2);
    kmMat4Scaling(&scaleMatrix, 0.05, 0.05, 0.05);
    kmMat4Multiply(&model, &model, &scaleMatrix);	// model, view, projection combined matrix
    kmMat4Assign(&mvp, &vp);
    kmMat4Multiply(&mvp, &mvp, &model);	// model, view, projection combined matrix
    kmMat4Assign(&mv, &view);
    kmMat4Multiply(&mv, &mv, &model);	// view, model matrix for lighting
    glBindTexture(GL_TEXTURE_2D, ballTex);
    drawObj(&ballObj, &mvp, &mv,lightDir,viewDir);
}

void render()
{

    float rad;		// radians of rotation based on frame counter
    kmMat4 scaleMatrix;

    // clear the colour (drawing) and depth sort back (offscreen) buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // count the frame and base a rotation on it.
    frame++;
    rad = frame * (0.0175f);

    // rotate the light direction depending on lightAng
    lightDir.x=cos(lightAng/10.);
    lightDir.z=sin(lightAng/10.);
    lightDir.y=0;


    pEye.x=cos(camAng/10.)*7.;
    pEye.y=sin(camAng/10.)*7.;
    pEye.z=5;

    // recalculate the view direction vector used by lighting
    kmVec3Subtract(&viewDir,&pEye,&pCenter);
    kmVec3Normalize(&viewDir,&viewDir);

    // update view matrix for new cam position
    kmMat4LookAt(&view, &pEye, &pCenter, &pUp);

    // these two matrices are pre combined for use with each model render
    // the view and projection
    kmMat4Assign(&vp, &projection);
    kmMat4Multiply(&vp, &vp, &view);


    drawDoublePod(&pod);

    // see printf documentation for the formatting of variables...
    glPrintf(100, 20, "frame=%i", frame);
    glPrintf(100, 40, "mouse %i  %i   %i", mouse[0],mouse[1],mouse[2]);
	glPrintf(100, 60, "joystick %i,%i  %i",joy1->axis[0],joy1->axis[1],joy1->buttons);
	 
    // swap the front (visible) buffer for the back (offscreen) buffer
    swapBuffers();

}
