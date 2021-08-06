#include "PluginManager.h"
#include <stdio.h>
#include <stdlib.h>
#include "FASTQCPlugin.h"

void FASTQCPlugin::input(std::string file) {
 inputfile = file;
 std::ifstream ifile(inputfile.c_str(), std::ios::in);
 while (!ifile.eof()) {
   std::string filename;
   ifile >> filename;
   fastqFiles.push_back(filename);
 }
}

void FASTQCPlugin::run() {
   
}

void FASTQCPlugin::output(std::string file) {
 // alpha_diversity.py -i filtered_otu_table.biom -m observed_species,chao1,shannon,PD_whole_tree -t rep_set.tre -o alpha.txt
   std::string command = "fastqc ";
 for (int i = 0; i < fastqFiles.size(); i++) {
	 if (fastqFiles[i].size() != 0) {
    command += std::string(PluginManager::prefix())+"/"+fastqFiles[i];
    command += " ";
	 }
 }
 command += "-o "+file;
 std::cout << command << std::endl;

 system(command.c_str());
}

PluginProxy<FASTQCPlugin> FASTQCPluginProxy = PluginProxy<FASTQCPlugin>("FASTQC", PluginManager::getInstance());
