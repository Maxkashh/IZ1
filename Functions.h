#pragma once
typedef struct
{
    const char* name;
    const  char* open_tag;
    const  char* close_tag;
    char** atributes;

}HTMLTag;
bool isTag_open();
char* get_closeTag(const char* string);
char* get_name(const char* string);
const char** get_atribut(int n);
char* get_tag();
HTMLTag* init(const char* tag);
void printObj(HTMLTag* obj);
void deleteMemory(HTMLTag* obj);