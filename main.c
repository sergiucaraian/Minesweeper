#include "grafica.h"
#include "logica.h"

void runMainLoop( int val );

int main(int argc, char* args[])
{
    //Initialize FreeGLUT
	glutInit( &argc, args );

	//Create OpenGL 2.1 context
	glutInitContextVersion( 2, 1 );

	//Create Double Buffered Window
	glutInitDisplayMode( GLUT_DOUBLE);
	glutInitWindowSize( SCREEN_WIDTH, SCREEN_HEIGHT );
	glutCreateWindow("Minesweeper");


	//Do post window/context creation initialization
	if( !initGL() )
	{
		printf( "Unable to initialize graphics library!\n" );
		return 1;
	}

    //Set resize function
    glutReshapeFunc( change_size );

	//Set rendering function
	glutDisplayFunc( render );

    //Set mouse handler
    glutMouseFunc( user_input );

	//Set main loop
	glutTimerFunc( 1000 / SCREEN_FPS, runMainLoop, 0 );

	//Start GLUT main loop
	glutMainLoop();

    return 0;
}

void runMainLoop( int val )
{
    render();

    //Run frame one more time
    glutTimerFunc( 1000 / SCREEN_FPS, runMainLoop, val );
}
