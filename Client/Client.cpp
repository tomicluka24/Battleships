#include "UserMenu.h"


#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#pragma warning (disable:4996)
#define SERVER_IP_ADDRESS "127.0.0.1"
#define SERVER_PORT 27016
#define BUFFER_SIZE 256

// TCP client that use non-blocking sockets
int main()
{


#pragma region Connection

	// Socket used to communicate with server
	SOCKET connectSocket = INVALID_SOCKET;

	// Variable used to store function return value
	int iResult;

	// Buffer we will use to store message
	char dataBuffer[BUFFER_SIZE];

	// WSADATA data structure that is to receive details of the Windows Sockets implementation
	WSADATA wsaData;

	// Initialize windows sockets library for this process
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		printf("WSAStartup failed with error: %d\n", WSAGetLastError());
		return 1;
	}

	// create a socket
	connectSocket = socket(AF_INET,
		SOCK_STREAM,
		IPPROTO_TCP);

	if (connectSocket == INVALID_SOCKET)
	{
		printf("socket failed with error: %ld\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}

	// Create and initialize address structure
	sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;								// IPv4 protocol
	serverAddress.sin_addr.s_addr = inet_addr(SERVER_IP_ADDRESS);	// ip address of server
	serverAddress.sin_port = htons(SERVER_PORT);					// server port

																	// Connect to server specified in serverAddress and socket connectSocket
	iResult = connect(connectSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress));
	if (iResult == SOCKET_ERROR)
	{
		printf("Unable to connect to server. Error %d\n", WSAGetLastError());
		closesocket(connectSocket);
		WSACleanup();
		return 1;
	}

	unsigned long  mode = 1;
	if (ioctlsocket(connectSocket, FIONBIO, &mode) != 0)
		printf("ioctlsocket failed with error.");
#pragma endregion


	user_menu(connectSocket);
	int game_mode = game_menu(connectSocket);
	LIST *head = NULL;


	bool is_won = false;

	if (game_mode == 0)
	{
		// logging out
		iResult = shutdown(connectSocket, SD_BOTH);

		// Check if connection is succesfully shut down.
		if (iResult == SOCKET_ERROR)
		{
			printf("Shutdown failed with error: %d\n", WSAGetLastError());
			closesocket(connectSocket);
			WSACleanup();
			return 1;
		}

		Sleep(1000);

		// Close connected socket
		closesocket(connectSocket);

		// Deinitialize WSA library
		WSACleanup();
	}
	else 
	{
		system("cls");
		//head = get_random_battlefield();
		place_battleships(&head);
		draw_table(head);
		save_battlefield(head);
		printf("Battleships placed. This is your battlefield. Good luck!\n");
		getchar();
		getchar();
	}

	is_won = play_game(connectSocket, &head, game_mode);

	if (is_won)
	{
		system("cls");
		printf("********WINNER********\n");
	}
	else
	{
		system("cls");
		printf("********LOOSER********\n");
	}
	ClearList(&head);
	// Shutdown the connection since we're done
	iResult = shutdown(connectSocket, SD_BOTH);

	// Check if connection is succesfully shut down.
	if (iResult == SOCKET_ERROR)
	{
		printf("Shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(connectSocket);
		WSACleanup();
		return 1;
	}

	// Close connected socket
	closesocket(connectSocket);

	// Deinitialize WSA library
	WSACleanup();
	getchar();
	getchar();
	return 0;
}