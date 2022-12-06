#include "gtest/gtest.h"
#include "person.h"

// this class is used for testing public methods in class Person
class test_person: public ::testing::Test {
protected:
	Person person;
	Person recipient;
};

//testing constructors
//Note: this test uses get_username, get_firstname, etc
//These were tested first, although they are located below
TEST_F(test_person, test_construct){
	Person p1("user1", "first", "last", 20, "tag");
	Person p2("user", "f", "l", 30, "tag");
	Person p3;
	Person p4("user1", "first", "last", 10, "tag");
	EXPECT_STREQ(p2.get_info().c_str(), person.get_info().c_str());
	EXPECT_STREQ(person.get_info().c_str(), p3.get_info().c_str());
	EXPECT_STREQ(p1.get_info().c_str(), "user1, first, last, 20, tag");
	EXPECT_STREQ(person.get_info().c_str(), p4.get_info().c_str());
}

// test get_username and set_username
TEST_F(test_person, test_username) {
	EXPECT_FALSE(person.set_username("aaaaaaaaaaaaaaaaaaaaa1aaaaaaaaaaa"));
	EXPECT_FALSE(person.set_username("a"));
	EXPECT_FALSE(person.set_username(""));
	EXPECT_FALSE(person.set_username("1aaaa"));
	EXPECT_FALSE(person.set_username("aaa aaa"));
	EXPECT_TRUE(person.set_username("cbgravitt1"));
	EXPECT_STREQ(person.get_username().c_str(), "cbgravitt1");
}

// test get_firstname and set_firstname
TEST_F(test_person, test_firstname) {
	EXPECT_FALSE(person.set_firstname("abc123"));
	EXPECT_TRUE(person.set_firstname("Charles"));
	EXPECT_STREQ(person.get_firstname().c_str(), "Charles");
	EXPECT_FALSE(person.set_firstname("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"));
	EXPECT_STREQ(person.get_firstname().c_str(), "Charles");
}

// test get_lastname and set_lastname
TEST_F(test_person, test_lastname) {
 	EXPECT_FALSE(person.set_lastname("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklm"));
	EXPECT_FALSE(person.set_lastname("abcde12"));
	EXPECT_TRUE(person.set_lastname("Gravitt"));
 	EXPECT_STREQ(person.get_lastname().c_str(), "Gravitt");
	EXPECT_FALSE(person.set_lastname("abcdefg0"));
	EXPECT_FALSE(person.set_lastname("abcdefg;"));
	EXPECT_TRUE(person.set_lastname(""));
}

/**you may need to write more test functions.
 *  What we provide here is just for your reference
 */

// test get_age and set_age
//   test_person is the name of class your inherit from the base Test class
//   test_age is the name of this test case, which will show up in the test
//     results
//   make sure you cover every subroutine and branches
//   here we test edge cases of invalid ages
//   also, we test the get_age() method
//   avoid using ASSERT_FALSE here; if there is something wrong in ASSERT,
//   it will abort the whole testing which will hinder the grading process
TEST_F(test_person, test_age) {
	EXPECT_FALSE(person.set_age(-1));
	EXPECT_TRUE(person.set_age(18));
	EXPECT_EQ(person.get_age(), 18);
	EXPECT_FALSE(person.set_age(149));
}

// test get_tagline and set_tagline
TEST_F(test_person, test_tagline) {
	EXPECT_FALSE(person.set_tagline("This is a very long tagline. I'm not sure how long 128 chars is, but I must be getting close, right? I think this is probably long enough now. Goodbye!"));
	EXPECT_TRUE(person.set_tagline("This is a reasonable tagline."));
	EXPECT_TRUE(person.set_tagline("Short"));
	EXPECT_STREQ(person.get_tagline().c_str(), "Short");
}

// test get_info and set_info
TEST_F(test_person, test_info) {
	EXPECT_TRUE(person.set_info("user1","f","l",20,"tag"));
	EXPECT_STREQ(person.get_info().c_str(), "user1, f, l, 20, tag");
	EXPECT_FALSE(person.set_info("user", "newf", "newl", 21, "newtag"));
	EXPECT_STREQ(person.get_info().c_str(), "user1, f, l, 20, tag");
}

// test get_msgstat, send_msg, get_msg_with_info and read_msg
//   to make your code shorter, we suggest combining these tests together; you
//   can also separate them into several test cases
//user f l age tag
TEST_F(test_person, test_msg) {
	EXPECT_TRUE(person.send_msg(recipient, "msg"));
	EXPECT_EQ(recipient.get_msgstat(person), 1);
	EXPECT_TRUE(recipient.read_msg());
	recipient.get_msg_with_info("msg1", &person);
	EXPECT_EQ(recipient.get_msgstat(person), 1);
	EXPECT_TRUE(recipient.read_msg());
	EXPECT_FALSE(person.read_msg());
	EXPECT_EQ(recipient.get_msgstat(person), 0);
	EXPECT_FALSE(recipient.read_msg());
	person.set_username("person1");
	recipient.add_to_block_list("person1");
	EXPECT_TRUE(recipient.in_block_list("person1"));
	EXPECT_FALSE(person.send_msg(recipient, "msg"));
	EXPECT_EQ(recipient.get_msgstat(person), 0);
	EXPECT_FALSE(recipient.read_msg());
	person.set_username("person2");
	EXPECT_TRUE(person.send_msg(recipient, "msg"));
	EXPECT_TRUE(person.send_msg(recipient, "msg"));
	EXPECT_TRUE(person.send_msg(recipient, "msg"));
	EXPECT_EQ(recipient.get_msgstat(person), 3);
	EXPECT_TRUE(recipient.read_msg());
	EXPECT_EQ(recipient.get_msgstat(person), 2);
}

//testing str_isalpha str_isalnum
TEST_F(test_person, test_str_isalnum){
	EXPECT_FALSE(str_isalpha("this is not alphas only since there are spaces"));
	EXPECT_TRUE(str_isalpha("thisisalphaonly"));
	EXPECT_FALSE(str_isalpha("123"));
	EXPECT_FALSE(str_isalpha("welp."));
	EXPECT_FALSE(str_isalpha("(psssst)"));
	EXPECT_TRUE(str_isalnum("justalpha"));
	EXPECT_TRUE(str_isalnum("1234"));
	EXPECT_TRUE(str_isalnum("abc123"));
	EXPECT_FALSE(str_isalnum("uh oh1234"));
	EXPECT_FALSE(str_isalnum("punctuation."));
}
