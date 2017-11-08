#include <QApplication>
#include "client.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Client client(getIpAddr(), getPort());
    std::string name("shape2.wav");
    std::string name2("test");
    quint8 error_code = 0;
    client.getParsedTrackFromServer(error_code, name2);
//    for (int i = 0; i < 10; i++) {
//        if (i % 2 == 1){
//            client.getTrackFromServer(error_code, name);
//            if (error_code != 0){
//                std::cout << "Error response" << std::endl;
//                error_code = 0;
//            }

//            client.getParsedTrackFromServer(error_code, name2);
//            if (error_code != 0){
//                std::cout << "Error response get ParsedTrack" << std::endl;
//                error_code = 0;
//            }
//        }
//        else
//            client.getPlaylistFromServer(error_code);

//        delay(1000);
//    }

    std::cout << "all_ok" << std::endl;
    return a.exec();
}