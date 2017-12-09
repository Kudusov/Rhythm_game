#include "responseparser.h"

quint8 ResponseParser::getErrorMsg(QByteArray &in) {

    QDataStream ss(in);
    quint8 err_code;
    ss >> err_code;
    return err_code;

}

quint8 ResponseParser::getMusic(QByteArray &in, std::string &res) {

    QByteArray music = in;
    QString track_name("new.vaw");
    QString path = createPathToMusic(track_name);
    QFile file2(path);

     if (!file2.open(QIODevice::WriteOnly)){

         return ErrorCodes::FILE_NOT_CREAT;

     }

     file2.write(music.data(), music.size());
     file2.close();
     res = path.toStdString();
     //is_executed_response = true;
     return ALL_OK;

}

quint8 ResponseParser::getParsedMusic(QByteArray &in, std::string &res) {

    QByteArray parsed_music = in;
    QString file_name("parsed.txt");
    QString path = createPathToParsedMusic(file_name);
    QFile file(path);

    if (!file.open(QIODevice::WriteOnly)) {
        return ErrorCodes::FILE_NOT_CREAT;
    }

    file.write(parsed_music);
    file.close();
    res = path.toStdString();
    return ALL_OK;

}

quint8 ResponseParser::getPlaylist(QByteArray &in, std::vector<std::string> &res) {

    QByteArray playlist = in;
    std::string str = playlist.toStdString();
    std::replace(str.begin(), str.end(), '\n', ' ');
    std::stringstream ss(str);
    res.clear();
    std::string tmp;
    while(ss >> tmp){
        res.push_back(tmp);
    }

    return ALL_OK;

}


QString ResponseParser::createPathToMusic(QString& track){

    MusicRouter rout;
    return rout.getPath() + track;
//    return track;

}


QString ResponseParser::createPathToParsedMusic(QString& track) {

    ParsedMusicRouter rout;
    return rout.getPath() + track;

}
