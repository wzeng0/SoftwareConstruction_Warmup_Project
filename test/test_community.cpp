#include "gtest/gtest.h"
#include "person.h"
#include "community.h"

// this class is used for testing public methods in class Community
class test_community: public ::testing::Test {
protected:
	Community community;
	Person person;
};

// you should complete the following test cases
// you should add more if you see fit

TEST_F(test_community, test_construct){
	map<string,Person>goodmap;
	Person p1("user1", "first", "last", 20, "tag");
	goodmap["user1"] = p1;
	Community c1("I have an invalid name!", goodmap);
	Community c2("IHaveAValidName", goodmap);
	EXPECT_STREQ(c1.get_name().c_str(), "");
	EXPECT_EQ(c1.get_all_usernames().size(), 0);
	EXPECT_EQ(c2.get_all_usernames().size(), 1);
}

// test get_name
TEST_F(test_community, get_name) {
	EXPECT_TRUE(community.set_name("AvatarTheLastAirbender"));
	EXPECT_STREQ("AvatarTheLastAirbender", community.get_name().c_str());
}

// test set_name
TEST_F(test_community, set_name) {
	EXPECT_FALSE(community.set_name(""));
	EXPECT_FALSE(community.set_name("THISISALONGASSSTRINGTHATISPROBABLYGOINGTOFAILTHETESTIHOPETHATTHISISMORETHAN64CHARACTERSSOTHATIDOOTGETDOCKEDBYTHECOMPILER"));
	EXPECT_FALSE(community.set_name("THIS IS NOT A VALID NAME"));
	EXPECT_FALSE(community.set_name("!@#$!@$#@notagoodname"));
	EXPECT_TRUE(community.set_name("GOODNAME"));
	EXPECT_STREQ(community.get_name().c_str(), "GOODNAME");
	EXPECT_FALSE(community.set_name("1badname"));
	EXPECT_STREQ(community.get_name().c_str(), "GOODNAME");
}

// test add_person
TEST_F(test_community, add_person) {
	Person p1("user1", "first", "last", 20, "tag");
	Person p2;
	EXPECT_TRUE(community.add_person(p1));
	EXPECT_FALSE(community.add_person(p1));
	EXPECT_FALSE(community.add_person(p2));
}

// test get_all_usernames
//   there's no EXPERT functions for comparing non-built-in types, you need to
//   do some parsing by yourself
TEST_F(test_community, get_all_usernames) {
	Person p1("user1", "first", "last", 20, "tag");
	Person p2("user2", "first", "last", 20, "tag");
	Person p3("user3", "first", "last", 20, "tag");
	list<string> usernames = {"user1", "user2", "user3"};
	list<string> usernames2 = {"user1", "user3"};
	std::set<string> s1(std::begin(usernames), std::end(usernames));
	std::set<string> s2(std::begin(usernames2), std::end(usernames2));
	community.add_person(p1);
	community.add_person(p2);
	community.add_person(p3);
	list<string> community_usernames = community.get_all_usernames();
	std::set<string> c_usernames(std::begin(community_usernames), std::end(community_usernames));
	EXPECT_TRUE(s1 == c_usernames);
	EXPECT_FALSE(s2 == c_usernames);
}

set<string>find_username(list<Person> s) {
    set<string> ret;
    auto iter = s.begin();
    while (iter != s.end()) {
        ret.insert((*iter).get_username());
		iter++;
    }
    return ret;
}

// test find_member by first name and age range
TEST_F(test_community, find_member) {
	Person p1("user1", "first", "last", 20, "tag");
	Person p2("user2", "first", "last", 30, "tag");
	Person p3("user3", "first", "last", 35, "tag");
	community.add_person(p1);
	community.add_person(p2);
	community.add_person(p3);

	list<string> usernames = {"user1", "user2", "user3"};
	list<string> usernames2 = {"user1", "user3"};
	std::set<string> s1(std::begin(usernames), std::end(usernames));
	std::set<string> s2(std::begin(usernames2), std::end(usernames2));
	list<Person> community_williams = community.find_member("first");
	set<string> community_usernames = find_username(community_williams);


	list<string> thirty1 = {"user1", "user2", "user3"};
	list<string> thirty2 = {"user2", "user3"};
	std::set<string> t1(std::begin(thirty1), std::end(thirty1));
	std::set<string> t2(std::begin(thirty2), std::end(thirty2));
	list<Person> community_thirty = community.find_member(30, 40);
	set<string> community_age = find_username(community_thirty);

	EXPECT_TRUE(s1 == community_usernames);
	EXPECT_FALSE(s2 == community_usernames);
	EXPECT_TRUE(t2 == community_age);
	EXPECT_FALSE(t1 == community_age);
}

// test get_member
TEST_F(test_community, get_member) {
	Person p1("user1", "first", "last", 20, "tag");
	Person p2("user2", "first", "last", 30, "tag");
	Person p3("user3", "first", "last", 35, "tag");
	Person p;
	community.add_person(p1);
	community.add_person(p2);
	community.add_person(p3);

	EXPECT_STREQ(p1.get_info().c_str(), community.get_member("user1").get_info().c_str());
	EXPECT_STREQ(p2.get_info().c_str(), community.get_member("user2").get_info().c_str());
	EXPECT_STREQ(p3.get_info().c_str(), community.get_member("user3").get_info().c_str());
	EXPECT_STREQ(p.get_info().c_str(), community.get_member("user4").get_info().c_str());
	EXPECT_STRNE(p.get_info().c_str(), community.get_member("user1").get_info().c_str());
	EXPECT_STRNE(p.get_info().c_str(), community.get_member("user2").get_info().c_str());
	EXPECT_STRNE(p.get_info().c_str(), community.get_member("user3").get_info().c_str());
}

// test send_msg
TEST_F(test_community, send_msg) {
	Person p1("user1", "william", "last", 20, "tag");
	Person p2("user2", "first", "last", 30, "tag");
	Person p3("user3", "william", "last", 50, "tag");
	community.add_person(p1);
	community.add_person(p2);
	community.add_person(p3);
	list<string> usernames = {"user1", "user2", "user3"};
	list<string> F_usernames = {"user1", "user2", "user4"};
	EXPECT_TRUE(community.send_msg(usernames, "this is a test case should return true"));
	EXPECT_TRUE(community.get_member("user1").read_msg());
	EXPECT_TRUE(community.get_member("user2").read_msg());
	EXPECT_TRUE(community.get_member("user3").read_msg());
	EXPECT_FALSE(community.get_member("user1").read_msg());
	EXPECT_FALSE(community.send_msg(F_usernames, "this is a test case should return false"));
	EXPECT_TRUE(community.get_member("user1").read_msg());
	EXPECT_TRUE(community.get_member("user2").read_msg());
	EXPECT_FALSE(community.get_member("user3").read_msg());
}
