// -*- coding: utf-8 -*-
/*
 * Alain - Oct 2011
 */
/**
 * Drawing a simple spaceship.
 * Use AntTweakBar to alter some variables
 */
#include "object.h" 
//#if defined(__APPLE__)
//    #include <Glutg/glut.h>
//#else
//    #include <GL/glut.h>
//#endif
#include <GL/glfw.h>
#include <GL/glew.h>

#include <iostream>

#include <cstdlib>
#include "scene.h"
//#include "plane-coord.h"
#include "basis-cube.h"
#include "textbox.h" 
#include "ship.h"
#include "coord_ang.h"
#include "ref_frame.h"
#include "utils.h"

// AntTweakBar
#include <AntTweakBar.h>

// Graphic
ScenePtr _scene = ScenePtr (new Scene);
BasisCubePtr coord;
bool _fg_coord = true;
TextBoxPtr _textbox;
TwBar *_bar;         // Pointer to a tweak bar

// Global variables
float _angX = 0.0;
float _angZ = 0.0;


/**
 * Called after every mouse button pressed.
 * see glfwSetMouseButtonCallback().
 */
void on_mouse_button( int button, int action )
{
  int x, y;
  glfwGetMousePos( &x, &y);
  //std::cout <<"Mouse Button at (" << x <<  ", " << y << ")\n";

  if( !TwEventMouseButtonGLFW( button, action ) )  { // send event to AntTweakBar
    // event has not been handled by AntTweakBar
    // your code here to handle the event
    // ...

    if( action == GLFW_PRESS ) {
      if( button == GLFW_MOUSE_BUTTON_LEFT ) {
	// With SHIFT ??
	if( glfwGetKey( GLFW_KEY_LSHIFT ) || glfwGetKey( GLFW_KEY_RSHIFT)) {
	  _scene->mouse_action_start ("move-resize",x,y);
	}
	else {
	  _scene->mouse_action_start ("rotate",x,y);
	}
      }
      else if( button == GLFW_MOUSE_BUTTON_RIGHT ) {
	_scene->mouse_action_start( "zoom", x, y);
      }
    }
    else if( action == GLFW_RELEASE ) {
      _scene->mouse_action_end( x, y);
    }
  }
}
/**
 * Called when the mouse moves.
 * see glfwSetMousePosCallback().
 */
void on_mouse_move (int x, int y)
{

  if( !TwEventMousePosGLFW( x, y ) )  { // send event to AntTweakBar
    // event has not been handled by AntTweakBar
    // your code here to handle the event
    // ...
    
    _scene->mouse_action (x,y);
    // TODO No equivalence for "glutPostRedisplay()"; ==> needed ??
  }
}
/**
 * Called when a key is pressed.
 * see glfwSetKeyCallback().
 */
void on_key_pressed( int key, int action)
{
    if( !TwEventKeyGLFW( key, action ) )  { // send event to AntTweakBar
    // event has not been handled by AntTweakBar
    // your code here to handle the event
    // ...

      // o or O : display orientation of scene
      if( ((key == 111) || (key == 79))  && (action == GLFW_PRESS)) {
	Orientation orien = _scene->get_orientation();
	std::cout << "Orient = (" << orien.x << ", " << orien.y << ")\n";
      }
      // p or P : plan 0xy
      else if( ((key == 112) || (key == 80))  && (action == GLFW_PRESS)) {
	_scene->set_orientation( 0, 0);
      }
      // c or C : Coordinates are visible/unvisible
      else if( ((key == 99) || (key == 67))  && (action == GLFW_PRESS)) {
	if( _fg_coord ) _fg_coord = false;
	else _fg_coord = true;
	coord->set_visible( _fg_coord );
      }
      
      // else {
      //     std::cout << "key=" << key << " act=" << action << "(" << GLFW_KEY_TAB << ", " << GLFW_PRESS << ")" << std::endl;
      //   }
    }
}
/**
 * Display the Scene, and thus every object in it.
 */
void display (void) {
    glClearColor (1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    _scene->render ();

    // Draw tweak bars
    TwDraw();

    // Swap buffers
    glfwSwapBuffers();
}

int main (int argc, char **argv)
{
  // Some graphic parameters
  int width, height;

  // Initialise GLFW
  if( !glfwInit() ) {
    fprintf( stderr, "Failed to initialize GLFW\n" );
    exit( EXIT_FAILURE );
  }
  
  // TODO Check that same parameters are used than : glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  // Open a window and create its OpenGL context
  if( !glfwOpenWindow( 1000, 480, 0,0,0,0, 0,0, GLFW_WINDOW ) ) {
    fprintf( stderr, "Failed to open GLFW window\n" );
    
    glfwTerminate();
    exit( EXIT_FAILURE );
  }
  glfwSetWindowTitle( "Frame" );
  
  //glutReshapeFunc (reshape);
  //glutDisplayFunc (display);
  glfwSetMouseButtonCallback( on_mouse_button );
  glfwSetMousePosCallback( on_mouse_move );
  glfwSetKeyCallback( on_key_pressed );
  glfwSetCharCallback( (GLFWcharfun)TwEventCharGLFW );
  glfwSetMouseWheelCallback((GLFWmousewheelfun)TwEventMouseWheelGLFW);
  //glutReshapeWindow (400,400);

  // Initialize AntTweakBar
  TwInit(TW_OPENGL, NULL);
  // Create a tweak bar
  _bar = TwNewBar("Ship");
  TwDefine( " GLOBAL help='AntTweak to alter rotation angle.' "); // Msg to the help bar.
  // Add '_angX' to bar : modifiable (RW), FLOAT, [0,360]
  TwAddVarRW( _bar, "angX", TW_TYPE_FLOAT, &_angX, 
	      " label='AngX' min=0 max=360 step=1.0 keyIncr=x KeyDecr=X help='Rotation angle around Oz' ");
  // Add '_angZ' to bar : modifiable (RW), FLOAT, [0,360]
  TwAddVarRW( _bar, "angZ", TW_TYPE_FLOAT, &_angZ, 
	      " label='AngZ' min=0 max=360 step=1.0 keyIncr=z KeyDecr=Z help='Rotation angle around Oy' ");
  

  std::cout << "Init GLEW\n";
  if( !glewInit() ) {
    fprintf( stderr, "Failed to initialize GLEW\n" );
  }
  if (glewIsSupported("GL_EXT_framebuffer_object"))
    std::cout<<"Old EXT FBO available"<<std::endl;
  else
    std::cout<<"Old EXT FBO NOT available"<<std::endl;
  if (glewIsSupported("GL_ARB_framebuffer_object"))
    std::cout<<"Newer ARB FBO available"<<std::endl;
  else
    std::cout<<"Newer ARB FBO NOT available"<<std::endl;

  // Background color for scene
  _scene->set_bg_color (1,1,1,1);

  // Add a system coordinate
  Position pos_rep( -0.5, -0.5, -0.5, 0);
  Range rg_x( -5, 5, 4, 4*5);
  Range rg_y( -5, 5, 4, 4*5);
  Range rg_z( -5, 5, 4, 4*5);

  // Ship
  ShipPtr ship = ShipPtr( new Ship());
  ship->set_size( 0.1, 0.1, 0.1 );
  _scene->add( ship );

  // Some CoordAng
  CoordAngPtr _coord_ang = CoordAngPtr( new CoordAng());
  _coord_ang->set_size( 0.5, 0.5, 0.5 );
  _scene->add( _coord_ang );

  // Some Ref_Frame
  RefFramePtr _ref = RefFramePtr( new RefFrame());
  _ref->set_position( 0, 0, 0.5 );
  _ref->set_size( 0.25, 0.25, 0.25 );
  _ref->_ang_Oz1 = 30.0;
  _ref->_ang_Ox1 = 45.0;
  _ref->_ang_Oz2 =  5.0;
  _scene->add( _ref );
  
  coord = BasisCubePtr (new BasisCube());
  coord->set_range_coord_x( rg_x );
  coord->set_range_coord_y( rg_y );
  coord->set_range_coord_z( rg_z );
  coord->set_title_coord_x("X");
  coord->set_title_coord_y("Y");
  coord->set_title_coord_z("Z");
  coord->set_position( pos_rep );
  _scene->add ( coord );

  // Then a text box with parameters
  _textbox = TextBoxPtr (new TextBox);
  _textbox->set_fg_color (0,0,0,1);
  _textbox->set_bg_color (.9,.9,.9,.1);
  _textbox->set_fontsize (0);
  //update_textbox();
  _textbox->set_buffer( "Coucou" );
  _scene->add( _textbox );

  //_scene->set_zoom(1.8);
  //_scene->set_orientation( 45.0, 45.0 );

  _scene->setup();
  _scene->update();


  // Main loop of GLFW
  _coord_ang->_ang_Oxy = _angX;
  _coord_ang->_ang_Oxz = _angZ;
  do {
    // Get window size (may be different than the requested size)
    glfwGetWindowSize( &width, &height );
    // Special case: avoid division by zero below
    height = height > 0 ? height : 1;
    
    glViewport( 0, 0, width, height );
    TwWindowSize(width, height);
    

    // display
    display();
    
    //_angX += 0.0005;
    //_angZ += 0.0003;
    _coord_ang->_ang_Oxy = clip_rad_2pi( to_rad(_angX) );
    _coord_ang->_ang_Oxz = clip_rad_2pi( to_rad(_angZ) );

  } // Check if the ESC key was pressed or the window was closed
  while( glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS &&
	 glfwGetWindowParam( GLFW_OPENED ) );


  // Terminate AntTweakBar and GLFW
  TwTerminate();
  glfwTerminate();

  return 0;
}
