#include "person.h"

//works, test more
bool str_isalpha(const string str){
    for(int i = 0; i < str.size(); i++)
    	if((isalpha(str[i]) == 0) || (str[i] == ' '))
    		return false;
    return true;
}

//doesn't work? fix? test?
bool str_isalnum(const string s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && (std::isdigit(*it) || std::isalpha(*it))){ ++it;}
    
    return !s.empty() && it == s.end();
}

Person::Person() 
  : username(""), firstname(""), lastname(""), age(0), tagline("") {
}

//set up using set fxns
Person::Person(string _username, string _firstname, string _lastname, 
               int _age, string _tagline)
  : username(_username), firstname(_firstname), lastname(_lastname),
    age(_age), tagline(_tagline) {
        bool user = set_username(_username);
        bool first = set_firstname(_firstname);
        bool last = set_lastname(_lastname);
        bool a = set_age(_age);
        bool tag = set_tagline(_tagline);
        if(!(user && first && last && a && tag)){
            username = "";
            firstname = "";
            lastname = "";
            age = 0;
            tagline = "";
        }
}

string Person::get_username() {
    return username;
}
string Person::get_firstname() {
    return firstname;
}
string Person::get_lastname() {
    return lastname;
}
int Person::get_age() {
    return age;
}
string Person::get_tagline() {
    return tagline;
}
string Person::get_info() {
    string ret = "";
    std::string age_str = std::to_string(age);
    ret += username + ", " + firstname + ", " + lastname + ", " + age_str + ", " + tagline;
    return ret;
}

bool al_and_num(string s){
    int has_al = 0;
    int has_num = 0;
    for(int i = 0; i < s.length(); i++){
        if(isalpha(s[i])){
            has_al = 1;
        }else if(isdigit(s[i])){
            has_num = 1;
        }
    }
    return has_al && has_num;
}

bool Person::set_username(string _username) {
    if (_username.length() > 32 || _username == ""){
        return false;
    }else if (isdigit(_username[0]) || !al_and_num(_username)){
        return false;
    }
    username = _username;
	return true;
}

bool Person::set_firstname(string _firstname) {
	if (_firstname.length() > 32 || !str_isalpha(_firstname)) {
        return false;
    }
    else {
        firstname = _firstname;
        return true;
    }
}


bool Person::set_lastname(string _lastname) {
	if (_lastname.length() > 32 || !str_isalpha(_lastname)) {
        return false;
    }
    else {
        lastname = _lastname;
        return true;
    }
}

bool Person::set_age(int _age) {
    if (_age >= 13 && _age <= 100) {
        age = _age;
        return true;
    }
    else {
        return false;
    }
}
bool Person::set_tagline(string _tagline) {
    if (_tagline.length() < 129) {
        tagline = _tagline;
        return true;
    }
    else {
        return false;
    }
}


bool Person::set_info(string _username, string _firstname, string _lastname,
                      int _age, string _tagline) {
    // test
    string curr_u = get_username();
    string curr_f = get_firstname();
    string curr_l = get_lastname();
    int curr_a = get_age();
    string curr_tag = get_tagline();
    bool s_age = set_age(_age);
    bool s_fn = set_firstname(_firstname);
    bool s_ln = set_lastname(_lastname);
    bool s_un = set_username(_username);
	bool s_tag = set_tagline(_tagline);
	if(!(s_age && s_fn && s_ln && s_un && s_tag)){
        set_age(curr_a);
        set_username(curr_u);
        set_firstname(curr_f);
        set_lastname(curr_l);
        set_tagline(curr_tag);
    }
    return s_age && s_fn && s_ln && s_un && s_tag;
}

void Person::add_to_block_list(string _username){
	block_list.insert(_username);
}

bool Person::in_block_list(string _username){
	return block_list.count(_username) == 1;
}

bool Person::send_msg(Person &recipient, string msg) {
	if (recipient.in_block_list(username)){
        return false;
    }else{
        recipient.get_msg_with_info(msg, this);
        return true;
    }
}

void Person::get_msg_with_info(string msg, Person* sender) {
    if(in_block_list((*sender).get_username())){
        return;
    }else{
	    inbox_stat.push({msg, *sender});
    }
}

int Person::get_msgstat(Person recipient){
    int count = 0;
    queue<pair<string, Person>> copy = inbox_stat;
    while (!copy.empty())
    {
        string front_user = get<1>(inbox_stat.front()).username;
        if(front_user == recipient.get_username()){
            count++;
        }
        copy.pop();
    }
	return count;
}

bool Person::read_msg() {
	// print the message if there any message inbox
    if(inbox_stat.size() == 0){
        return false;
    }else{
        pair<string, Person> temp (inbox_stat.front());
        cout << std::get<0>(temp);
        inbox_stat.pop();
        return true;
    }
}

