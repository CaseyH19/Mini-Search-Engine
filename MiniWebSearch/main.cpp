//  Casey Hittinger
//  main.cpp
//
//  Created by Casey on 10/24/16.
//  This program is a mini-search engine that based on the query will return the documents that abide by the query


#include <iostream>
#include <fstream>
#include "parser.h"


int main(int argc, const char* argv[])
{
    
    Parser parser;
    
    //take arguments and save them as strings
    std::string inputdoc(argv[1]);
    std::string query(argv[2]);
    std::string ouput(argv[4]);
    std::string stopwords(argv[3]);
    
    std::ofstream outputdoc;
    outputdoc.open(ouput);
    
    
    parser.populateSTOP(stopwords);
    parser.parseDocuments(inputdoc);
    parser.queryInput(query, outputdoc);
    
    
    
}
