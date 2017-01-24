//  Casey Hittinger
//  parser.h
//  MiniWebSearch
//
//  Created by Casey on 10/29/16.
//
//  Parses through xml file getting title, id, url to add to its own class for each document. Each class will also have its own vector of words in the document

#ifndef parser_h
#define parser_h

#include <iostream>
#include <sstream>
#include <fstream>
#include "porter2_stemmer.hpp"
#include "file.h"
#include "AVLTree.h"
#include "DSVector.hpp"


class Parser
{
public:
    
    Vector<std::string> stopwords;
    AVLTree<File> documents;
    
    
    // inputs the stop words into a vector to later be compared
    void populateSTOP(std::string doc)
    {
        std::ifstream stop;
        stop.open(doc);
        
        // until teh end of the doc, words will be added to list
        while(!stop.eof())
        {
            std::string word;
            std::getline(stop, word);
            stopwords.add(word);
            
        }
        
        // TESTING
//        for(int i = 0; i < stopwords.size(); i++)
//        {
//            std::cout << stopwords[i] << std::endl;
//        }
        
    }
    
    
    bool checkStop(std::string word)
    {
        for(int i = 0; i < stopwords.size(); i++)
        {
            if(stopwords[i] == word)
            {
                return true;
            }
        }
        return false;
    }
    
    
    // parses thorugh xml document and gets the id, title, and url
    void parseDocuments(std::string doc)
    {
        
        std::ifstream input;
        input.open(doc);
        int numDoc = 0;
        std::string line;
        // while there are more lines, this loop will continue
        while(std::getline(input, line))
        {
            std::string title = "";
            std::string url = "";
            std::string iiD = "";
            int iD = 0;
            
            
            //std::cout << line << std::endl;
            
            
            std::stringstream words(line);
            std::string w;
            while(std::getline(words, w, ' '))
            {
                //std::cout << w << std::endl;
                
                //gets id number and converts it into int, cause easier to use
                if(w.substr(0,2) == "id")
                {
                    int lengthline = w.length() - 4;
                    iiD = w.substr(4, lengthline-1);
                    iD = std::stoi(iiD);
                    //std::cout << iD << std::endl;
                }
                
                //gets the url and saves it as a string
                else if(w.substr(0,3) == "url")
                {
                    int lengthline = w.length() - 5;
                    url = w.substr(5, lengthline-1);
                    //std::cout << url << std::endl;
                    
                }
                
                // gets the title of teh document and saves it
                else if(w.substr(0,5) == "title")
                {
                    if(!words.eof())
                    {
                        int lengthline = w.length() - 7;
                        title = w.substr(7, lengthline);
                        //std::cout << title << std::endl;
                        
                        std::string nline;
                        std::getline(words, nline);
                        //std::cout << nline << std::endl;
                        nline = removePunct(nline);
                        //std::cout << nline << std::endl;
                        
                        title = title + " " + nline;
                        //std::cout << title << std::endl;
                    }
                    else
                    {
                        int lengthline = w.length() - 7;
                        title = w.substr(7, lengthline-2);
                        //std::cout << title << std::endl;
                    }
                }
                
                
            }
            
            // adds title, url, and id to the file class
            File file(title, iD, url);
            //std::cout << file.docName << "\n" << file.url << "\n" << file.ID << std::endl;
            
            // will conitnue big loop up until the </doc> or document being closed. This will add each word to the file vector
            while(line != "</doc>")
            {
                std::getline(input, line);
                if(line == "</doc>")
                {
                    break;
                }
                line = removePunct(line);
                line = toLower(line);
                //std::cout << line << std::endl;
                
                std::stringstream words(line);
                std::string w;
                while(words >> w)
                {
                    // if it is not a stop word, it will stem the word and check to see if the word isnt already present
                    if(checkStop(w) == false)
                    {
                        //std::cout << "\n" << w << std::endl;
                        Porter2Stemmer::stem(w);
                        //std::cout << w << std::endl;
                        
                        if(file.searchWords(w) == false)
                        {
                            //std::cout << w << std::endl;
                            file.words.add(w);
                        }
                        else
                        {
                            //std::cout << w << std::endl;
                            //std::cout << "Not added duplicate" << std::endl;
                        }
                    }
                    else
                    {
                        //std::cout << "Not added stopword" << std::endl;
                    }
                }
                
                
            }
            //add file class to the avltree
            documents.insert(file);
            
            //for(int i = 0; i < file.words.size(); i++)
            //{
              //  std::cout << file.words[i] << std::endl;
            //}
            
            // testing to see end of doc, also increases the number of documnets just incase i need it later
            //std::cout << "END OF DOCUMENT\n" << std::endl;
            numDoc++;
        }
        
        // Testing to see if all doc have been added to the avltree and in the correct order
        //std::cout << "\n NUMDOC = " << numDoc << std::endl;
        //documents.postOrder();
    }
    
    // iterates through a line and deletes the punctuation
    std::string removePunct(std::string line)
    {
        for(int i=0; i < line.length(); i++)
        {
            if(std::ispunct(line[i]))
            {
                line[i]= ' ';
            }
        }
        
        return line;
    }
    
    // iterated through and changes each character to its lowercase value
    std::string toLower(std::string line)
    {
        for(int i=0; i < line.length(); i++)
        {
            line[i] = std::tolower(line[i]);
            
        }
        
        return line;
    }
    
    
    // deals with query file
    void queryInput(std::string doc, std::ofstream &outputs)
    {
        std::ifstream query;
        query.open(doc);
        
        // gets teh number of queries the user wants
        int numQ;
        std::string numQR;
        std::getline(query, numQR);
        numQ = std::stoi(numQR);
        //testing output
        //std::cout << "\n" << numQ << std::endl;
  
        // loops thorugh the desired amount of queries
        int counter = 0;
        
        // whiel the counter does not become greater than or equal to the number of queries
        while(counter < numQ)
        {
            // gets the query line
            std::string line = "";
            std::getline(query, line);
            // test to see if gets correct line
            //std::cout << line << std::endl;
            outputs << line << std::endl;
            
            std::stringstream word(line);
            std::string andOr;
            // gets either AND or OR for query results
            word >> andOr;
            //std::cout << andOr << std::endl;
  
   
           
            // boolean to see if there is a false in the query
            bool nOT = false;
            int wordCountAtNot = 0;
            int count = 0;
            std::string w = "";
   
            Vector<std::string> searches;
            
            // goes word by word thorugh the line string
            while(word >> w)
            {
                //std::cout << w << std::endl;
                
                if(w == "NOT")
                {
                    nOT = true;
                    wordCountAtNot = count;
                    //std::cout << wordCountAtNot << std::endl;
                }
                
                else
                {
                    w = toLower(w);
                    searches[count] = w;
                    count++;
                 
                }
                
            }
 
            //for(int i = 0; i <= 2; i++)
            //{
              //  std::cout << searches[i] << std::endl;
            //}
 
            std::string one = searches[0];
            std::string two = searches[1];
            std::string three = searches[2];
 
            // stems the queries
            Porter2Stemmer::stem(one);
            Porter2Stemmer::stem(two);
            Porter2Stemmer::stem(three);
            
            //testing to make sure stemming works on queries
            //std::cout << one << std::endl;
            //std::cout << two << std::endl;
            //std::cout << three << std::endl;
            
            
            //std::cout << "\nSearch: " << counter+1 << std::endl;
            documents.searchWord(andOr, one, two, nOT, three, wordCountAtNot, outputs);
     
            counter++;
            //std::cout << "\n";
            outputs << "\n";
        }
        
    }
    
};


#endif /* parser_h */
