#ifndef LOG_HEADER_H
#define LOG_HEADER_H

#include <string>
#include <fstream>
#include <time.h>
#include <iomanip>
#include <iostream>
#include <filesystem>

namespace filesystem = std::filesystem;

bool FileExists(std::string file_path) {
	if ( filesystem::exists(file_path) )
		return true;
	else
		return false;
}

class Logs 
{
public:
	std::string log_output_path;
	std::string log_output_filename;
	std::string log_output_file_extension = ".log";

	void CreateLog(std::string OutputPath, std::string OutputFileName) {
		if ( FileExists(OutputPath) )
		{
			// set global variables to be used across different functions
			Logs::log_output_path = output_path;
			Logs::log_output_filename = output_file_name;
			Logs::log_output_file_extension = ".log";
			std::string sLogFilePath = Logs::log_output_path + "\\" + Logs::log_output_filename + Logs::log_output_file_extension;
			if ( sLogFilePath.size() > _MAX_PATH )
				throw std::runtime_error("ERROR: Path is longer than 260 characters: " + sLogFilePath);
			else
			{
				if ( !FileExists(sLogFilePath) )
				{
					std::cout << sLogFilePath << std::endl;
					std::ofstream LogFile(sLogFilePath);
				}
				else
					throw std::invalid_argument("ERROR1404: File already exists:  " + sLogFilePath);
			}

		}
		else
			throw std::invalid_argument("ERROR1012: File or directory not found: " + Logs::log_output_path);
	}

	void OpenLog(std::string LogPath, std::string LogFileName) {
		std::string sLogFilePath = LogPath + "\\" + LogFileName + Logs::log_output_file_extension;
		std::fstream LoggingFile;

		if ( FileExists(sLogFilePath) )
		{
			if ( LoggingFile.is_open() )
				throw std::runtime_error("ERROR2009: File is already OPEN: " + sLogFilePath);
			else
			{
				Logs::log_output_path = LogPath;
				Logs::log_output_filename = LogFileName;
			}
		}
		else
			throw std::invalid_argument("ERROR1012: File or directory not found: " + sLogFilePath);
	}

	int CloseLog(std::string LogPath, std::string LogFileName) {
		std::string sLogFilePath = LogPath + "\\" + LogFileName + Logs::log_output_file_extension;
		std::fstream LoggingFile;

		if ( FileExists(sLogFilePath) )
		{
			if ( !LoggingFile.is_open() )
				throw std::runtime_error("ERROR2009: File is already CLOSED: " + sLogFilePath);
			else
			{
				LoggingFile.close();
				return 0;
			}
		}
		else
			throw std::invalid_argument("ERROR1012: File or directory not found: " + sLogFilePath);
	}

	void Log(std::string cMessage) {
		// Get date and time to put in the log //
		time_t time = std::time(nullptr);
		tm pTime = *std::localtime(&time);
		auto formattedTime = std::put_time(&pTime, "%Y-%d-%m %r %p");

		// Get path to output log file
		if ( Logs::log_output_path.empty() || Logs::log_output_filename.empty() || Logs::log_output_file_extension.empty() )
			throw std::runtime_error("ERROR1000: No Logging File Opened");
		else
		{
			std::string sLogFilePath = Logs::log_output_path + "\\" + Logs::log_output_filename + Logs::log_output_file_extension;
			std::cout << sLogFilePath << std::endl;
			if ( FileExists(sLogFilePath) )
			{
				std::fstream LogFile;

				LogFile.open(sLogFilePath, std::ios::app);
				LogFile << "\n" << formattedTime << " :: " << cMessage;
				LogFile.close();

			}
			else
				throw std::runtime_error("ERROR1012: File or directory not found: " + sLogFilePath);
		}
	}

	void ClearLog(std::string LogPath, std::string LogFileName) {
		std::string sLogFilePath = LogPath + "\\" + LogFileName + Logs::log_output_file_extension;
		std::fstream LoggingFile;

		if ( FileExists(sLogFilePath) )
		{
			LoggingFile.open(sLogFilePath, std::ios::out);

			OpenLog(LogPath, LogFileName);
			Log("Log Cleared");

			LoggingFile.close();
		}
		else
			throw std::invalid_argument("ERROR1012: File or directory not found: " + sLogFilePath);
	}

	std::string GetLogPath() {
		std::string sLogFilePath = Logs::log_output_path + "\\" + Logs::log_output_filename + Logs::log_output_file_extension;
		if ( !Logs::log_output_path.empty() || !Logs::log_output_filename.empty() )
			std::cout << "Current Log File Path is: " << sLogFilePath << std::endl;
		else
			std::cout << "WARNING8028: Log File Path Not Found" << std::endl;

		return sLogFilePath;
	}
};

#endif


