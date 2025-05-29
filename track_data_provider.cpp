#include "track_data_provider.h"
#include <fstream>
#include "time_utils.h"

std::vector<TrackPoint> TrackDataProvider::getTracks(const std::string& filepath) {
    std::vector<TrackPoint> tracks;
    std::ifstream file(filepath);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file");
    }
    std::string str;
    TrackPoint current_track{};
    bool has_data = false;
    while(getline(file, str)) {
        if (str.find("<trkpt") != std::string::npos) {
            if (has_data) {
                tracks.push_back(current_track);
                current_track = {};
            }
            if (str.find("lat=") != std::string::npos
            && str.find("lon=") != std::string::npos)
            {
                current_track.latitude = std::stod(str.substr(str.find("lat=") + 5, str.find("\" ") - (str.find("lat=") + 5)));
                current_track.longitude = std::stod(str.substr(str.find("lon=") + 5, str.find("\">") - (str.find("lon=") + 5)));
            }
        }
        if (str.find("<time>") != std::string::npos and str.find('+') == std::string::npos)
        {
            current_track.timestamp = parseISO8601(str.substr(str.find("<time>") + 6, str.find("<Z/time>") - (str.find("<time>") + 6) ));
        }
        if (str.find("<ele>") != std::string::npos) {
            current_track.elevation = std::stod(str.substr(str.find("<ele>") + 5, str.find("</ele>") - (str.find("<ele>") + 5)));
            has_data = true;
        }
    }
    if (has_data) {
        tracks.push_back(current_track);
    }
    file.close();
    return tracks;
}