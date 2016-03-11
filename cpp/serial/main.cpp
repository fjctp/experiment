#include <wiringSerial.h>
#include <iostream>

using namespace std;

int main(int argc, const char* argv[])
{

    int fd = serialOpen("/dev/ttyAMA0", 115200);
    if (fd == -1) 
    {
        cout << "Cannot open serial port" << endl;
        return 1;
    }

    serialFlush(fd);
    char buffer[] = "i00";
    while (buffer[0] != 'q')
    {
        serialPuts(fd, buffer);
        cin >> buffer;
    }

    serialClose(fd);
    return 0;
}
