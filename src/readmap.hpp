#pragma once
#include "ssconfig.hpp"
#include <string>
#include <vector>
#include <fstream>
//#include <QDebug>

struct GPSPolygon{
	std::vector<double> vlat, vlon;

};

inline int read_map(const std::string& ob_file, const std::string& prefix, std::vector<GPSPolygon>& res){
	sscfg::ConfigFile conf = sscfg::ConfigFile::load(ob_file);
	double base[2] = { 0, 0 };
	double scale   = 1e-5;
	
	if (conf.get("obBaseLatLon", base, 2) != 2){
        qDebug("Error : Failed to get obBaseLatLon\n");
		return -1;
	}
	if (!conf.get("obBaseScale", scale)){
        qDebug("Error : Failed to get obBaseScale\n");
		return -1;
	}

	int k = 0;
	while(1){
		std::string name = prefix + std::to_string(k);
		if (!conf.exist(name+"_dlat")){
			break;
		}

		GPSPolygon poly;
		conf.get(name + "_dlat", poly.vlat);
		conf.get(name + "_dlon", poly.vlon);
		if (poly.vlat.size() == poly.vlon.size()){
			res.push_back(poly);
			GPSPolygon& p = res.back();
			for (size_t i = 0; i < p.vlat.size(); ++i){
				p.vlat[i] = p.vlat[i] * scale + base[0];
				p.vlon[i] = p.vlon[i] * scale + base[1];
			}
		}
		else{
			printf("Warning: Get dlat/dlon with unmatched size\n");
		}
		k++;
	}

	// Return the number of items read
	return k;
}
