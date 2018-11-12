/*
*  \file  main.c
*  \brief  main function to execute the program.
*  \author  Amin, Basti, Semir and Daniel 
*  \copyright  See the LICENSE file.
*/

#include <stdio.h>
#include "brick.h"
#include "ev3_tacho.h"
#include "draw.h"
#include "ev3.h"
#include "ev3_port.h"
#include "ev3_sensor.h"

// WIN32 /////////////////////////////////////////
#ifdef __WIN32__

#include <windows.h>

// UNIX //////////////////////////////////////////
#else

#include <unistd.h>
#define Sleep( msec ) usleep(( msec ) * 1000 )

//////////////////////////////////////////////////
#endif

int main( void )
{
	int x;
	int y;
 
	node* head = NULL;
	node* tmp = NULL;
	callback disp = display;
	
	printf( "Initializing the robot...\n" );
	//check if the 
	if ( !brick_init()) return ( 1 );
	if ( ev3_init() < 1 ) return ( 1 );
	if(init() && ev3_sensor_init()){
		printf( "The drawing process is starting...\n" );
		/*
		//needed points for bugs bunny
		int bugsbunny[174][2] = {
		{-8, -8}, {-7, -7}, {-6, -5}, {-6, -4}, {-5, -2}, {-5, -1}, {-7, 1}, {-9, 4}, {-10, 6}, {-11, 9}, {-12, 13}, {-12, 16}, {-11, 19}, {-10, 19}, {-9, 16}, {-5, 9}, {-4, 6}, {-3, 4}, {-2, 1}, {-1, 0}, {0, 1}, {1, 0}, {2, 1}, {3, 4}, {4, 6}, {5, 9}, {9, 16}, {10, 19}, {11, 19}, {12, 16}, {12, 13}, {11, 9}, {10, 6}, {9, 4}, {7, 1}, {5, -1}, {5, -2}, {6, -4}, {6, -5}, {7, -7}, {8, -8}, {10, -8}, {12, -9}, {13, -11}, {13, -12}, {12, -14}, {11, -15}, {9, -16}, {7,-18}, {5,-19}, {4,-20}, {1,-21}, {-1,-21}, {-4,-20}, {-5,-19}, {-7,-18}, {-9,-16}, {-11,-15}, {-12,-14}, {-13,-12}, {-13,-11}, {-12,-9}, {-10,-8}, {-7,-8}, {-4,-9}, {-2,-10}, {0,-12}, {2,-10}, {4,-9}, {7,-8}, {8,-8},


		{-22, -22},
			

		{-4, -9}, {-5, -7}, {-5,-4}, {-4,-2}, {-3,-2}, {-2,-4}, {-1,-7}, {-1,-9}, {-2,-10}, {-2,-7}, {-1,-9}, {-2, -10}, {-2,-7}, {-3,-6}, {-4,-7}, {-4,-9},


		{-22, -22},


		{4,-9}, {5,-7}, {5,-4}, {4,-2}, {3,-2}, {2,-4}, {1,-7}, {1,-9}, {2,-10}, {2,-7}, {3,-6}, {4,-7}, {4,-9},


		{-22, -22},


		{-4,1}, {-4,2}, {-7,9}, {-8,11}, {-9,14}, {-10,16}, {-11,17}, {-11,12}, {-10,9}, {-9,7}, {-7,4}, {-4,1},


		{-22, -22},

		{4,1}, {4,2}, {7,9}, {8,11}, {9,14}, {10,16}, {11,17}, {11,12}, {10,9}, {9,7}, {7,4}, {4,1},


		{-22, -22},


		{-5,-1}, {-4,0}, {-3,0}, {-2,-1},
			
			
		{-22, -22},
			

		{-3,-12}, {-2,-16}, {0,-17}, {2,-16}, {3,-12}, {2,-11},
			
			
		{-22, -22},
			

		{0,-13}, {0,-17},
			
			
		{-22, -22},
			

		{5,-19}, {6,-17},
			
			
		{-22, -22},
			

		{-5,-19}, {-6,-17},
			
			
		{-22, -22},
			

		{3,-11}, {11,-8}, {13,-8},
			
			
		{-22, -22},
			

		{4,-11}, {10,-10}, {14,-10},
			
			
		{-22, -22},
			

		{5,-11}, {8,-11}, {14,-12},
			
			
		{-22, -22},
			

		{-3,-11}, {-11,-8}, {-13,-8},
			
			
		{-22, -22},
			

		{-4,-11}, {-10,-10}, {-14,-10},
			
			
		{-22, -22},
			

		{-5,-11}, {-8,-11}, {-14,-12},
			
			
		{-22, -22},
			
		};
		*/
		
		//needed points for batman
		int batman[70][2] = {
			{0,-12}, {4,-6}, {5,-5}, {6,-5}, {7,-6}, {8,-8}, {9,-6}, {10,-5}, {11,-5}, {12,-6}, {13,-8}, {13,-9}, {12,-11}, {11,-12}, {14,-11}, {17,-9}, {19,-7}, {20,-5}, {21,-2}, {21,1}, {20,4}, {19,6}, {17,8}, {14,10}, {11,11}, {12,10}, {13,8}, {13,7}, {12,5}, {11,4}, {9,3}, {6,3}, {3,4}, {3,12}, {1,9}, {-1,9}, {-3,12}, {-3,4}, {-6,3}, {-9,3}, {-11,4}, {-12,5}, {-13,7}, {-13,8}, {-12,10}, {-11,11}, {-14,10}, {-17,8}, {-19,6}, {-20,4}, {-21,1}, {-21,-2}, {-20,-5}, {-19,-7}, {-17,-9}, {-14,-11}, {-11,-12}, {-12,-11}, {-13,-9}, {-13,-8}, {-12,-6}, {-11,-5}, {-10,-5}, {-9,-6}, {-8,-8}, {-7,-6}, {-6,-5}, {-5,-5}, {-4,-6}, {0,-12}
		};
		
		//add 21 to all points to avoid minus values
		int i;
		int j;		
		for ( i = 0; i < 70; i++ ) {
			for ( j = 0; j < 2; j++ ) {
				batman[i][j] = batman[i][j] + 21;
			}
		}
		//add all the values to the list
		head = prepend(head,batman[0][0],batman[0][1]);
		for ( i = 1; i < 70; i++ ) {
			head = append(head,batman[i-1][0],batman[i-1][1]);
		}
		//draw the picture
		draw(head);
		printf( "The drawing process terminated.\n" );
	}
	//uninitialize the robot
	brick_uninit();
	return ( 0 );
}
