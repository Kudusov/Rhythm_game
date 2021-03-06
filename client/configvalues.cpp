#include "configvalues.h"

int ConfigValues::port = 8000;
QString ConfigValues::host = "";
QString ConfigValues::music_path = "";
QString ConfigValues::parsed_music_path = "";
QString ConfigValues::log_file_path = "";

bool ConfigValues::setupConfigs(std::string &path_to_config) {

    QString path = QString::fromStdString(path_to_config);
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        std::cout << "error" << std::endl;
        return false;
    }
    QString file_content = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(file_content.toUtf8());
    QJsonObject objects = doc.object();
    QJsonObject ip_addr = objects["ip_addr"].toObject();

    if (ip_addr.isEmpty()) {
        return false;
    }

    QJsonObject routing_pathes = objects["routing"].toObject();

    if (routing_pathes.isEmpty()) {
        return false;
    }


    QJsonValue port_value = ip_addr.value("port");
    QJsonValue host_value = ip_addr.value("host");
    QJsonValue music_path_value = routing_pathes.value("music_path");
    QJsonValue parsed_music_path_value = routing_pathes.value("parsed_music_path");
    QJsonValue log_file_path_value = routing_pathes.value("log_file_path");

    if (port_value.isUndefined() || music_path_value.isUndefined() ||
            parsed_music_path_value.isUndefined() || log_file_path_value.isUndefined()) {

        return false;

    }


    ConfigValues::port = port_value.toInt();
    ConfigValues::host = host_value.toString();
    ConfigValues::music_path = music_path_value.toString();
    ConfigValues::parsed_music_path = parsed_music_path_value.toString();
    ConfigValues::log_file_path = log_file_path_value.toString();

    return true;

}
