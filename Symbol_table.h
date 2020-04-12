/**This is a very basic implementation of a symbol table like data structure.
It uses a hash table and chaining as a collision resolution method**/

#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H
#define MAXSIZE 100

#include <string>

/**We want to be able to store an identifier's name, the
line where it was declared, its type and scope**/
class Entry{
    public:
        Entry():next(NULL){}
        Entry(std::string i, int l, std::string t, std::string s):identifier(i),line_num(l),type(t),scope(s),next(NULL){}
        friend class Symbol_table;
    private:
        std::string identifier; ///name
        int line_num; ///line number of declaration
        std::string type;
        std::string scope;
        Entry* next; ///we will use linked lists to resolute the collisions
};

class Symbol_table{
    public:
        Symbol_table(); ///fills hash table with NULLs
        Entry* lookup(std::string id);
        bool insert(std::string i, int l, std::string t, std::string s);
        Entry* delete_entry(std::string id);
        bool modify(std::string i, int l, std::string t, std::string s);
    private:
        int hash(std::string id); ///the hash function
        Entry* searchS1L(Entry* q, std::string id); ///search in one list
        Entry* hash_table[MAXSIZE];
};

#endif
