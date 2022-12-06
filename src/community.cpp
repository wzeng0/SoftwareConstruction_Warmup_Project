#include "community.h"

Community::Community()
  : name(""), people(map<string,Person>()) {
}

Community::Community(string _name, map<string,Person> _people) 
  : name(_name), people(_people) {
    bool valid = set_name(name);
    if (!valid) {
        name = "";
        people = map<string,Person>();
    }
}

string Community::get_name() {
	return name;
}

bool Community::set_name(string _name) {
    // each letter in the string has to be alphanumeric
    for (int i = 0; i < _name.length(); i++) {
        if (!isalnum(_name[i]))
            return false;
    }

    // name cannot be longer than 64 letters and first letter cannot be a digit
    if (_name.length() > 64 || _name.length() == 0 || isdigit(_name[0]))
        return false;

    // set name
    name = _name;
    return true;
}

bool Community::add_person(Person _person) {
    if (people.find(_person.get_username()) != people.end() || _person.get_username() == "") {
    	return false;
    }
    people.insert({_person.get_username(), _person});
    return true;
}

// return the person object for a given username
Person& Community::get_member(string username) {
    if (people.find(username) != people.end()) {
    	return people[username];
    }
    else {
    	Person* p = new Person();
	return *p;
    }
}
    
list<string> Community::get_all_usernames() {
    list<string> usernames;
    auto iter = people.begin();
    while (iter != people.end()) {
        usernames.push_back(iter->second.get_username());
        iter++;
    }
    return usernames;
}

void Community::print_all_usernames() {
    // print all usernames of members to the console
    list<string> usernames = get_all_usernames();
    for (auto it = usernames.begin(); it != usernames.end(); it++) {
        std::cout << *it  << std::endl;
    }
}

list<Person> Community::find_member(string firstname) {
    list<Person> ret;
    // find users with a certain first name
    auto iter = people.begin();
    while (iter != people.end()) {
        if (iter->second.get_firstname() == firstname) {
            ret.push_back(iter->second);
        }
        iter++;
    }
    return ret;
}

list<Person> Community::find_member(int age_lb, int age_ub) {
  list<Person> ret;
  // find users within certain ages [age_lb, age_ub], both lower bound and upper bound shall be inclusive
  auto iter = people.begin();
    while (iter != people.end()) {
        if (iter->second.get_age() <= age_ub && iter->second.get_age() >= age_lb) {
            ret.push_back(iter->second);
        }
        iter++;
    }
  return ret;
}

bool Community::send_msg(list<string> usernames, string msg) {
	// send msg to a Person addressed by username
	// make sure the username is validated
    bool valid = true;
    for (auto it = usernames.begin(); it != usernames.end(); it++) {
        if (people.find(*it) != people.end()) {
            Person person;
            get_member(*it).get_msg_with_info(msg, &person);
        }
        else
            valid = false;
    }
	return valid;
}
