#include "log-header.hpp"
#include <iostream>
#include <Windows.h>

// fake installer for program which utilizes log-header.h
int main() {	
	Logs Logging;
	// Log the crash and what happened
	Logging.CreateLog("C:\\users\\ethan", "Crash-Log");
	Logging.OpenLog("C:\\users\\ethan", "Crash-Log");
	Logging.GetLogPath();
	Logging.ClearLog("c:\\users\\ethan", "Crash-Log");
	Logging.Log("Attempting to reinstall dependencies in background.");
	Logging.Log("Sucessfully installed dependencies.");
	Logging.Log("Fatal Error - Unhandled exception at 0x7fff2ff7d4f0");
	Logging.Log("Could not fully install application.");
	Logging.Log("Waiting for computer restart to resume installing.");
	Logging.CloseLog(Logging.log_output_path, Logging.log_output_filename):
	return 1;
}