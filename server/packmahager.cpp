#include "packmahager.h"

ResponseStruct PackManager::packToStruct(QDataStream& in) {
    std::cout << "packToStruct" << std::endl;
    ResponseStruct out;
    quint8 comm;
    in >> comm;
    out.comand = comm;
    switch(comm) {
        case(GET_MUSIC) :{
            std::cout << "packToStruct Get Music" << std::endl;
            packMusic(in, out);
            break;
        }

        case(GET_PARSED_MUSIC): {
            packParsedMusic(in, out);
            break;
        }

        case(GET_PLAYLIST): {
            packPlaylist(out);
            break;
        }
    }

    return out;
}


void PackManager::packMusic(QDataStream &in, ResponseStruct &res) {
    QString track;
    in >> track;
    QString path = getPathToMusicsFile() + track;
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)){
        //std::cout << "music not found" << std::endl;
        //sendErrorMsgToClient(client, ErrorCodes::TRACK_NOT_FOUND);
        packErrorMsg(res, ErrorCodes::TRACK_NOT_FOUND);
        return;
    }

    QByteArray track_bytes = file.readAll();
    QDataStream out(&(res.data), QIODevice::WriteOnly);
    out << QByteArray(track_bytes.data(), track_bytes.size());
}

void PackManager::packParsedMusic(QDataStream &in, ResponseStruct &res) {
    QString track;
    in >> track;
    QString path = getPathToParsedMusic() + track;
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly)) {
        // audio_handler.parse_music( ... )
        //std::cout << "Parsed Track is not found" << std::endl;
        //sendErrorMsgToClient(client, ErrorCodes::PARSED_MUSIC_ERROR);
        packErrorMsg(res, ErrorCodes::PARSED_MUSIC_ERROR);
        return;
    }

    /* Вынести на отдельный уровень */
    QTextStream in2(&file);
    QString line = in2.readAll();
    file.close();
    QDataStream out(&(res.data), QIODevice::WriteOnly);
    out << line.toUtf8();
}

void PackManager::packPlaylist(ResponseStruct &res) {

    QFile file(getPathToPlaylist());

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cout << "Playlists is not found" << std::endl;
        //sendErrorMsgToClient(client, ErrorCodes::PLAYLIST_NOT_FOUND);
        packErrorMsg(res, ErrorCodes::PLAYLIST_NOT_FOUND);
        return;
    }

    /* Вынести на отдельный уровень */
    QTextStream in2(&file);
    QString line = in2.readAll();
    file.close();
    QDataStream out(&(res.data), QIODevice::WriteOnly);
    out << line.toUtf8();

}

void PackManager::packErrorMsg(ResponseStruct &res, quint8 err_code) {

    res.comand = Commands::ERROR;
    QDataStream out(&(res.data), QIODevice::WriteOnly);
    out << quint8(err_code);
}
