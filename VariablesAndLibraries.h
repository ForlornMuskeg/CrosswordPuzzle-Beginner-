#pragma once

#include <iostream>  

#include <iomanip>   /* contains stream manipulators setw(int): to allocate the field to display 
													 setfill('*'): to fill the allocated but undisplayed field with '*' 
													 left or right: alignment of the text */
													
#include <string>    /* contains getline(): to take the entire line as input including spaces */

#include <conio.h>   /* contains _getch(): to hold the screen until user presses a key */

#include <windows.h> /* contains GetKeyState(key & 0x8000): to get the state whether key is pressed or not by user
								 SetConsoleTextAttributes(): to change console display colour */

#include <fstream>   /* filestream: to read information from other files */

#include <map>       /* STL CONTAINER MAP (Dynamic container which consists of pairs) std::map<key, value> */

#include <vector>    /* STL CONTAINER VECTOR (Similar to array but dynamic) std::vector<value> */

#include <chrono>    /* contains time_point<system_clock>, duration<> */


static constexpr int width {80};                                                  /* constant declaration and initialization at compile time(constexpr),
																					 it exists during the program life time(static) */

																				  /* time variables declarations */
std::chrono::time_point<std::chrono::system_clock> StartTime, PauseTime, EndTime; /* to record system_clock at the spesific point of the program */
std::chrono::duration<double> ElapsedTimeInPause, RealPlayTime;                   /* to find the difference between time_points (by using math operators) */

std::vector <std::string> Questions;											  /* containers declarations */
std::map <std::string, std::string> Answers;
std::map <std::string, std::string> RightAnswers;







