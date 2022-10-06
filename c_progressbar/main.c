#include <stdio.h>
#include <windows.h>
#include <locale.h>

#define BAR_LEN 50

char* progressbar(unsigned int current_value, unsigned int max_value, char* buffer, unsigned int length)
{
	if (buffer == NULL) {
		buffer = malloc(((length != 0 ? length : BAR_LEN) + 4) * sizeof(char));
	}
	
	float part = (float)current_value / (float)max_value;

	unsigned int fill = part * length;
	unsigned int pos = 0;

	buffer[pos++] = '\r';
	buffer[pos++] = '[';
	for (unsigned int i = 0; i <= fill; i++) {
		buffer[pos++] = '•';
	}
	for (unsigned int i = fill+1; i < length; i++) {
		buffer[pos++] = ' ';
	}
	buffer[pos++] = ']';
	buffer[pos] = '\0';

	return buffer;
}

DWORD WINAPI print(LPVOID lpparam)
{
	while (!*(char*)lpparam);
	while (*(char*)lpparam) {
		printf("%s", (char*)lpparam);
	}
	return 0;
}

int main()
{
	setlocale(LC_ALL, "");
	SetConsoleOutputCP(1251);

	char* buffer = malloc(128*sizeof(char));
	*buffer = 0;
	HANDLE T = CreateThread(NULL, 0, print, buffer, 0, NULL);
	

	for (unsigned int i = 0; i < (unsigned int)-1 >> 7; i++) {
		progressbar(i, (unsigned int)-1 >> 7, buffer, BAR_LEN);
		//printf("%s", progressbar(i, (unsigned short)-1, buffer, BAR_LEN));
	}

	*buffer = 0;
	free(buffer);


	return 0;
}