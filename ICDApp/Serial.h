#pragma once
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

class Serial {
private:
	HANDLE hComm;
	DWORD errors;
	COMSTAT status;

	char* port;
	int baud = CBR_9600;
	bool isConnected;

public:
	Serial(char* port);

	void openConnection();
	void closeConnection();

	int read();
	int read(char buffer[], unsigned int bufSize);
	bool write(char c);
	bool write(const char buffer[], unsigned int bufSize);
	bool write(const std::string message);

	bool println(const std::string message);
	operator bool();

	unsigned int available();
	bool connected();
};

extern Serial Serial;