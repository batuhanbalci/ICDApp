#include "Serial.h"

Serial::Serial(char* port)
{
	this->port = port;
}

void Serial::openConnection()
{
	this->isConnected = false;

	hComm = CreateFileA(port,
		GENERIC_READ | GENERIC_WRITE, //Read/Write
		0,                            // No Sharing
		NULL,                         // No Security
		OPEN_EXISTING,// Open existing port only
		0,            // Non Overlapped I/O
		NULL);        // Null for Comm Devices

	if (hComm == INVALID_HANDLE_VALUE)
	{
		printf("Error in opening serial port");
	}
	else
	{
		printf("Opening serial port successful");

		DCB dcbSerialParameters = { 0 };

		if (!GetCommState(hComm, &dcbSerialParameters))
			printf("failed to get current serial parameters");
		else
		{
			this->isConnected = true;

			dcbSerialParameters.BaudRate = baud;
			dcbSerialParameters.ByteSize = 8;
			dcbSerialParameters.StopBits = ONESTOPBIT;
			dcbSerialParameters.Parity = NOPARITY;
			dcbSerialParameters.fDtrControl = DTR_CONTROL_ENABLE;

			if (!SetCommState(hComm, &dcbSerialParameters))
				printf("ALERT: could not set Serial port parameters\n");
			else
			{
				PurgeComm(hComm, PURGE_RXABORT |
					PURGE_RXCLEAR |
					PURGE_TXABORT |
					PURGE_TXCLEAR);
			}
		}
	}
}

unsigned int Serial::available()
{
	ClearCommError(this->hComm, &this->errors, &this->status);
	return this->status.cbInQue;
}

int Serial::read()
{
	DWORD bytesRead;
	unsigned int toRead = 1;
	unsigned int bytesAvailable = available();
	char buffer[] = { ' ' };

	if (bytesAvailable)
		if (ReadFile(this->hComm, buffer, toRead, &bytesRead, NULL))
			return buffer[0];

	return -1;
}

int Serial::read(char buffer[], unsigned int bufSize)
{
	DWORD bytesRead;
	unsigned int toRead;
	unsigned int bytesAvailable = available();

	if (bytesAvailable > bufSize)
		toRead = bufSize;
	else
		toRead = bytesAvailable;

	if (ReadFile(this->hComm, buffer, toRead, &bytesRead, NULL))
		return bytesRead;

	return 0;
}

bool Serial::write(char c)
{
	DWORD bytesSend = 1;
	unsigned int buf_size = 1;
	char buffer[] = { c };

	if (!WriteFile(this->hComm, buffer, buf_size, &bytesSend, 0))
	{
		ClearCommError(this->hComm, &this->errors, &this->status);
		return false;
	}
	else
		return true;
}


bool Serial::write(const char buffer[], unsigned int bufSize)
{
	DWORD bytesSend;

	if (!WriteFile(this->hComm, buffer, bufSize, &bytesSend, 0))
	{
		ClearCommError(this->hComm, &this->errors, &this->status);
		return false;
	}
	else
		return true;
}

bool Serial::write(const std::string message)
{
	DWORD bytesSend;
	size_t bufSize = message.size();

	char* buffer = new char[message.size() + 1];
	message.copy(buffer, message.size() + 1);
	buffer[message.size()] = '\0';

	if (!WriteFile(this->hComm, buffer, bufSize, &bytesSend, 0))
	{
		ClearCommError(this->hComm, &this->errors, &this->status);
		return false;
	}
	else
		return true;
}



bool Serial::println(const std::string message)
{
	bool result = this->write(message);
	if (result)
		result = this->write('\n');
	return result;
}


Serial::operator bool()
{
	return this->connected();
}

bool Serial::connected()
{
	if (this->isConnected)
		return this->isConnected;
	else
		this->openConnection();

	return this->isConnected;
}



void Serial::closeConnection()
{
	if (this->isConnected)
	{
		this->isConnected = false;
		CloseHandle(this->hComm);
	}
}