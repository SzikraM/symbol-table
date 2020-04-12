/**This is a very basic implementation of a symbol table like data structure.
It uses a hash table and chaining as a collision resolution method**/

#include "Symbol_table.h"

using namespace std;

Symbol_table::Symbol_table(){
    for (int i = 0; i < MAXSIZE; i++){
        hash_table[i] = NULL;
    }
}

/**The hash function. The returned index is the ASCII sum of characters
in the identifier modulo the maximum size of the array in our hash table**/
int Symbol_table::hash(string id){
    long sum = 0;
    for (auto c : id){
        sum += (long)c;
    }
    return (sum % MAXSIZE);
}

/**Function to search in one list from the hash table.
Returns a pointer to the entry if a match was found, and NULL otherwise**/
Entry* Symbol_table::searchS1L(Entry* q, std::string id){
    while (q != NULL && q->identifier != id){
        q = q->next;
    }
    return q;
}

/**This is kind of beautiful**/
Entry* Symbol_table::lookup(string id){
    return searchS1L(hash_table[hash(id)], id);
}

/**Function to insert an entry. Returns true if the operation
was successful and false if it was not.**/
bool Symbol_table::insert(std::string i, int l, std::string t, std::string s){
    int ind = hash(i);
    Entry* e = new Entry(i, l, t, s);
    if (searchS1L(hash_table[ind], i) == NULL){
        e->next = hash_table[ind];
        hash_table[ind] = e;
        return true;
    }
    else{
        return false;
    }
}

/**Removes entry from Symbol table based on the identifier name,
returns the removed entry, or NULL if no match was found**/
Entry* Symbol_table::delete_entry(string id){
    int ind = hash(id);
    Entry* p = NULL;
    Entry* q = hash_table[ind];
    while (q != NULL && q->identifier != id){
        p = q;
        q = q->next;
    }
    if (q != NULL){
        if (p == NULL){
            hash_table[ind] = q->next;
        }
        else{
            p->next = q->next;
        }
        q -> next = NULL;
    }
    return q;
}

/**Function to modify an entry based on identifier, returns true
if it was successful, and false if the entry was not found**/
bool Symbol_table::modify(std::string i, int l, std::string t, std::string s){
    Entry* p;
    if ((p = lookup(i)) != NULL){
        p->line_num = l;
        p->type = t;
        p->scope = s;
        return true;
    }
    else{
        return false;
    }
}
