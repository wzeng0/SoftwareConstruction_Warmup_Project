#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <queue>
#include <iostream>
#include <algorithm>
#include <map>
#include <set>

using namespace std;
class Person {

  private:

    string username;
    string firstname;
    string lastname;
    int age;
    string tagline;

    // store received messages
    // similar as inbox, except also recording sender 
    // when a message is retrieved, delete it immediately
    queue<pair<string,Person> > inbox_stat;
    //  block list 
    set<string> block_list;    
  public:
   
    Person();
    Person(string _username, string _firstname, string _lastname, 
           int _age, string _tagline);

    string get_username();
    string get_firstname();
    string get_lastname();
    int get_age();
    string get_tagline();
    string get_info();

    bool set_username(string _username);
    bool set_firstname(string _firstname);
    bool set_lastname(string _lastname);
    bool set_age(int _age);
    bool set_tagline(string _tagline);
    bool set_info(string _username, string _firstname, string _lastname,
                  int _age, string _tagline);
    void add_to_block_list(string username);
    bool in_block_list(string username);
    bool send_msg(Person &recipient, string msg);
    void get_msg_with_info(string msg, Person* sender);
    int  get_msgstat(Person recipient); //return how many unread messages from recipent in inbox
    bool read_msg(); //return value indicates whether the inbox is empty or not
};

bool str_isalpha(const string str);
bool str_isalnum(const string str);

#endif /* COMMUNITY_H */

