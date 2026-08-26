//-------------------------------------------------------
//
//  StarterViewer.C
//
//  This viewer is a wrapper of the Glut calls needed to
//  display opengl data.  Options for zooming, 
//  labeling the window frame, etc are available for 
//  derived classes to use.
//
//
//  Copyright (c) 2003,2017,2023 Jerry Tessendorf
//
//--------------------------------------------------------


#include <GL/gl.h>   // OpenGL itself.
#include <GL/glu.h>  // GLU support library.
#include <GL/glut.h> // GLUT support library.




#include <iostream>
#include <sstream>
#include <cmath>
#include "StarterViewer.h"
#include <cstring>



using namespace std;
namespace starter{


// These are the GLUT Callbacks that are implemented in StarterViewer.
void cbDisplayFunc()
{
   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );	
   StarterViewer::Instance() -> Display();
   glutSwapBuffers();
   glutPostRedisplay();
}

void cbIdleFunc()
{
   StarterViewer::Instance() -> Idle();
}


void cbKeyboardFunc( unsigned char key, int x, int y )
{
   StarterViewer::Instance() -> Keyboard( key, x, y );
}

void cbMotionFunc( int x, int y )
{
   
   StarterViewer::Instance() -> Motion( x, y );
   glutPostRedisplay();
}

void cbMouseFunc( int button, int state, int x, int y )
{
   StarterViewer::Instance() -> Mouse( button, state, x, y );
}

void cbReshapeFunc( int w, int h )
{
   StarterViewer::Instance() -> Reshape( w, h );
   glutPostRedisplay();
}


StarterViewer* StarterViewer::pStarterViewer = nullptr;
	
StarterViewer::StarterViewer() : 
   initialized    ( false ),
   width          ( 512 ), 
   height         ( 512 ),
   display_mode   ( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH ),
   title          ( string("Starter Viewer") ),
   mouse_x        ( 0 ),
   mouse_y        ( 0 ),
   camera_fov     (35.0),
   camera_aspect  (1.0),
   camera_near    (0.01),
   camera_far     (10000.0),
   camera_eye_x   (0.0),
   camera_eye_y   (0.0),
   camera_eye_z   (-15.0),
   camera_view_x  (0.0),
   camera_view_y  (0.0),
   camera_view_z  (0.0),
   camera_up_x    (0.0),
   camera_up_y    (1.0),
   camera_up_z    (0.0),
   camera_right_x (1.0),
   camera_right_y (0.0),
   camera_right_z (0.0),
   frame          (0)
{
   cout << "StarterViewer Loaded\n";
}

StarterViewer::~StarterViewer(){}

void StarterViewer::Init( const std::vector<std::string>& args )
{
   int argc = (int)args.size();
   char** argv = new char*[argc];
   for( int i=0;i<argc;i++)
   {
      argv[i] = new char[args[i].length() + 1];
      std::strcpy(argv[i], args[i].c_str());
   }

   string window_title = title;

   glutInit( &argc, argv );
   glutInitDisplayMode( display_mode );
   glutInitWindowSize( width, height );
   glutCreateWindow( window_title.c_str() );
   glClearColor(0.5,0.5,0.6,0.0);

   camera_aspect = (float)width/(float)height;

   glutDisplayFunc( &cbDisplayFunc );
   glutIdleFunc( &cbIdleFunc );
   glutKeyboardFunc( &cbKeyboardFunc );
   glutMotionFunc( &cbMotionFunc );
   glutMouseFunc( &cbMouseFunc );
   glutReshapeFunc( &cbReshapeFunc );

   initialized = true;
   cout << "StarterViewer Initialized\n";
}

void StarterViewer::MainLoop()
{
   Usage();
   glutMainLoop();
}


void StarterViewer::Display()
{
   ++frame;
   glLoadIdentity();
   gluPerspective( camera_fov, camera_aspect, camera_near, camera_far );
   gluLookAt( camera_eye_x, camera_eye_y, camera_eye_z,    // Camera eye point
               camera_view_x, camera_view_y, camera_view_z, // Camera view point
               camera_up_x, camera_up_y, camera_up_z        // Camera up direction
             );

   glEnable(GL_DEPTH_TEST);
   glDepthRange( camera_near, camera_far );
}



void StarterViewer::Reshape( int w, int h )
{
   width = w;
   height = h;
   camera_aspect = (float)width/(float)height;

   glViewport( 0, 0, (GLsizei) width, (GLsizei) height );
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
}

void StarterViewer::Keyboard( unsigned char key, int x, int y )
{
   switch (key)
   {
      case 'f':
         camera_fov /= 1.01;
         break;
      case 'F':
         camera_fov *= 1.01;
         if( camera_fov > 170.0){ camera_fov = 170.0; }
	 break;
      case '+':
      case '=':
         ComputeEyeShift(0.07);
         break;
      case '-':
      case '_':
         ComputeEyeShift(-0.07);
         break;
      case 'r':
	     Reset();
        break;
      case 'h':
	     Home();
      break;
      case 'u':
	     Usage();
      break;
   }
}


void StarterViewer::Motion( int x, int y )
{
   float dx = x - mouse_x;
   float dy = y - mouse_y;
   float pos_x = current_raster_pos[0] + dx;
   float pos_y = current_raster_pos[1] - dy;
   glRasterPos2f( pos_x, pos_y ); 

   // camera motion perp to view direction
   if(keystate == GLUT_ACTIVE_SHIFT )
   {
     ComputeEyeUpRight(dx,dy);
   }
   mouse_x = x;
   mouse_y = y;
}


void StarterViewer::Mouse( int b, int state, int x, int y )
{
   mouse_x = x;
   mouse_y = y;
   keystate = glutGetModifiers();
   button = b;
   mouse_state = state;
   glGetFloatv( GL_CURRENT_RASTER_POSITION, current_raster_pos );
}


void StarterViewer::Idle() {}


void StarterViewer::Usage()
{
   cout << "--------------------------------------------------------------\n";
   cout << "StarterViewer usage:\n";
   cout << "--------------------------------------------------------------\n";
   cout << "f/F           reduce/increase the camera FOV\n";
   cout << "+/=           move camera farther from the view point\n";
   cout << "-/_           move camera closer to the view point\n";
   cout << "SHIFT+mouse   move camera perpendicular to the view direction\n";
   cout << "r             reset sim parameters\n";
   cout << "h             home display parameters\n";
   cout << "u             display this usage message\n";
   cout << "--------------------------------------------------------------\n";
}

void StarterViewer::Reset()
{
   std::cout << "Reset\n";
}

void StarterViewer::Home()
{
   std::cout << "Home\n";
   camera_fov     = 35.0;
   camera_near    = 0.01;
   camera_far     = 100.0;
   camera_eye_x   = 0.0;
   camera_eye_y   = 0.0;
   camera_eye_z   = -15.0;
   camera_view_x  = 0.0;
   camera_view_y  = 0.0;
   camera_view_z  = 0.0;
   camera_up_x    = 0.0;
   camera_up_y    = 1.0;
   camera_up_z    = 0.0;
   camera_right_x = 1.0;
   camera_right_y = 0.0;
   camera_right_z = 0.0;
}



void StarterViewer::ComputeEyeUpRight(int dx, int dy)
{

// dx --> rotation around y axis
// dy --> rotation about camera right axis


   float vvx = camera_eye_x-camera_view_x; 
   float vvy = camera_eye_y-camera_view_y; 
   float vvz = camera_eye_z-camera_view_z;
   float vvnorm = std::sqrt( vvx*vvx + vvy*vvy + vvz*vvz );
   vvx /= vvnorm;
   vvy /= vvnorm;
   vvz /= vvnorm;


// Rotate around y axis
//      Rotate view direction
   float cosx = std::cos( -dx*0.006 );
   float sinx = std::sin( -dx*0.006 );
   float nvvx = vvx*cosx + vvz*sinx;
   float nvvz = -vvx*sinx + vvz*cosx;
   float nrightx = camera_right_x*cosx + camera_right_z*sinx;
   float nrightz = -camera_right_x*sinx + camera_right_z*cosx;
   vvx = nvvx;
   vvz = nvvz;
   camera_right_x = nrightx;
   camera_right_z = nrightz;
//      Rotate up direction
   float crossx = camera_up_z;
   float crossy = 0.0;
   float crossz = -camera_up_x;
   float ydotup = camera_up_y;
   camera_up_x = camera_up_x*cosx + crossx*sinx;
   camera_up_y = camera_up_y*cosx + ydotup*(1.0-cosx) + crossy*sinx;
   camera_up_z = camera_up_z*cosx + crossz*sinx;
//      Rotate right direction
   crossx = camera_right_z;
   crossy = 0.0;
   crossz = -camera_right_x;
   ydotup = camera_right_y;
   camera_right_x = camera_right_x*cosx + crossx*sinx;
   camera_right_y = camera_right_y*cosx + ydotup*(1.0-cosx) + crossy*sinx;
   camera_right_z = camera_right_z*cosx + crossz*sinx;


// Rotate around camera-right axis
//     Rotate view direction
   cosx = std::cos( dy*0.006 );
   sinx = std::sin( dy*0.006 );
   float rightdotview = camera_right_x*vvx + camera_right_y*vvy + camera_right_z*vvz;
   crossx = camera_right_y*vvz - camera_right_z*vvy;
   crossy = camera_right_z*vvx - camera_right_x*vvz;
   crossz = camera_right_x*vvy - camera_right_y*vvx;
   nvvx = vvx*cosx + camera_right_x*rightdotview*(1.0-cosx) + crossx*sinx; 
   float nvvy = vvy*cosx + camera_right_y*rightdotview*(1.0-cosx) + crossy*sinx; 
   nvvz = vvz*cosx + camera_right_z*rightdotview*(1.0-cosx) + crossz*sinx; 
   vvx = nvvx;
   vvy = nvvy;
   vvz = nvvz;
//      Rotate up direction
   crossx = camera_right_y*camera_up_z - camera_right_z*camera_up_y;
   crossy = camera_right_z*camera_up_x - camera_right_x*camera_up_z;
   crossz = camera_right_x*camera_up_y - camera_right_y*camera_up_x;
   camera_up_x = camera_up_x*cosx + crossx*sinx; 
   camera_up_y = camera_up_y*cosx + crossy*sinx; 
   camera_up_z = camera_up_z*cosx + crossz*sinx; 


   camera_eye_x = vvx*vvnorm + camera_view_x;
   camera_eye_y = vvy*vvnorm + camera_view_y;
   camera_eye_z = vvz*vvnorm + camera_view_z;
}

void StarterViewer::ComputeEyeShift(float dz)
{
   float vvx = camera_eye_x-camera_view_x; 
   float vvy = camera_eye_y-camera_view_y; 
   float vvz = camera_eye_z-camera_view_z;
   float vvnorm = std::sqrt( vvx*vvx + vvy*vvy + vvz*vvz );
   vvx /= vvnorm;
   vvy /= vvnorm;
   vvz /= vvnorm;

   camera_eye_x += dz*vvx;
   camera_eye_y += dz*vvy;
   camera_eye_z += dz*vvz;
}



void StarterViewer::SetCameraEyeViewUp( float eyex, float eyey, float eyez, float viewx, float viewy, float viewz, float upx, float upy, float upz )
{
   camera_eye_x = eyex;   
   camera_eye_y = eyey;   
   camera_eye_z = eyez;   
   camera_view_x = viewx;   
   camera_view_y = viewy;   
   camera_view_z = viewz;   
   camera_up_x = upx;   
   camera_up_y = upy;   
   camera_up_z = upz;   
}



StarterViewer* CreateViewer() { return StarterViewer::Instance(); }



}


