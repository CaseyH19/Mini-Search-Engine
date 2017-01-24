//  Casey Hittinger
//  file.h
//  MiniWebSearch
//
//  Created by Casey on 10/29/16.
//  Class that will store the name, id, and url of the document. Also a vector of the words in the document will also be there.

#ifndef file_h
#define file_h
#include <iostream>

#include "DSVector.hpp"


class File
{
public:
    std::string docName;
    int ID;
    std::string url;
    Vector<std::string> words;
    
    // default constructor
    File()
    {
        docName = "";
        ID = NULL;
        url = "";
        
    }
    
    // constructor with initialization elements
    File(std::string doc, int num, std::string address)
    {
        docName = doc;
        ID = num;
        url = address;
    }
    
    //destructor
    ~File()
    {
        docName = "";
        ID = NULL;
        url = "";
    }
    
    // comparison operator when dealing with sorting avl tree
    bool operator==(const File& rhs)
    {
        if(rhs.docName == docName && rhs.ID == ID && rhs.url == url)
        {
            return true;
        }
        return false;
    }
    
    // greater than operator for comparison of file classes
    bool operator>(const File& rhs)
    {
        if(ID > rhs.ID)
        {
            return true;
        }
        return false;
    }
    
    // adds a word to the word vector of the document
    void addWord(std::string word)
    {
        words.add(word);
        sortVector();
    }
    
    //sorts the vector so that it remains alphabetical
    void sortVector()
    {
        int start, last;
        std::string something;
        
        //organizing the 2-D array in alphabetical order based off the first element of the 2D array
        for (start = 0; start < words.size()-1; start++ )
        {
            
            last = start;
            something = words[start];
        
            for (int inner = start+1; inner < words.size(); inner++)
            {
                if (words[inner] < something)
                {
                    something = words[inner];
                    last = inner;
                }
                
            }
        
            words[last] = words[start];
            words[start] = something;
        }
        
    }
    
    // searches for individual word for teh query
    bool searchWords(std::string word)
    {
        for(int i = 0; i < words.size(); i++)
        {
            if(words[i] == word)
            {
                return true;
            }
        }
        return false;
    }
};



#endif /* file_h */
