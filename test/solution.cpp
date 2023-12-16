#include "catch2/catch_all.hpp"
#include "simulator-lib/LinkedList.h"
using namespace std;

TEST_CASE("LinkedList adding elements") {
	LinkedList<int> list;

	SECTION("initial size should be zero") {
		REQUIRE(list.getSize() == 0);
	}

	SECTION("adding element should increase the size") {
		list.push_at(1, 0);
		REQUIRE(list.getSize() == 1);
	}

	SECTION("adding element should increase the size") {
		list.push_at(1, 0);
		CHECK(list.getSize() == 1);
		list.push_at(2, 0);
		CHECK(list.getSize() == 2);
		list.push_at(12, 1);
		CHECK(list.get(1) == 12);	
	}
	SECTION("Adding of element out of range should throw out of range error") {
		REQUIRE_THROWS_AS(list.push_at(10, 10), std::out_of_range);
	}
}

TEST_CASE("LinkedList getting elements") {
	LinkedList<int> list;
	list.push_at(1, 0);
	list.push_at(10, 0);
	list.push_at(100, 0);
	list.push_at(1000, 0);
	
	list.push_at(15, 1);
	list.push_at(16, 2);

	SECTION("non exising position should throw out of rance") {
		REQUIRE_THROWS_AS(list.get(100), std::out_of_range);
	}
	SECTION("adding element should increase the size") {
		CHECK(list.get(0) == 1000);
		CHECK(list.get(1) == 15);
		CHECK(list.get(2) == 16);
		CHECK(list.get(3) == 100);
		CHECK(list.get(4) == 10);
		CHECK(list.get(5) == 1);
	}
}

TEST_CASE("LinkedList removing elements") {
	LinkedList<int> list;
	list.push_at(1, 0);
	list.push_at(10, 0);
	list.push_at(100, 0);
	list.push_at(1000, 0);
	
	list.push_at(15, 1);
	list.push_at(16, 2);

	SECTION("non exising position should throw out of rance") {
		REQUIRE_THROWS_AS(list.erase(100), std::out_of_range);
	}

	SECTION("removing element should decrease the size and move the position of the next elements") {
		list.erase(4);
		CHECK(list.get(4) == 1);
	}
	SECTION("Operator= check")
	{
		LinkedList<int> list2;
		list2 = list;
		CHECK(list2.get(0) == 1000);
		CHECK(list2.get(1) == 15);
		CHECK(list2.get(2) == 16);
		CHECK(list2.get(3) == 100);
		CHECK(list2.get(4) == 10);
		CHECK(list2.get(5) == 1);
	}

	SECTION("Cpy ctor check")
	{
		LinkedList<int> list2(list);
		CHECK(list2.get(0) == 1000);
		CHECK(list2.get(1) == 15);
		CHECK(list2.get(2) == 16);
		CHECK(list2.get(3) == 100);
		CHECK(list2.get(4) == 10);
		CHECK(list2.get(5) == 1);
	}


	SECTION("Iteartor check")
	{
		LinkedList<int> list2(list);
		auto it = list2.begin();
		CHECK(*it == 1000);
		++it;
		CHECK(*it == 15);
		++it;
		CHECK(*it == 16);
		++it;
		CHECK(*it == 100);
		++it;
		CHECK(*it == 10);
		++it;
		CHECK(*it == 1);
		++it;
		CHECK(it == list2.end());
	}

	SECTION("Add to the tail and head")
	{
		LinkedList<int> list3;
		list3.push_at(10000, 0);
		list3.push_at(20000, 0);
		list3.push(2);
		CHECK(list3.front() == 20000);
		list3.pop_front();
		CHECK(list3.front() == 10000);
		CHECK(list3.back() == 2);
	}

	SECTION("Correctly using destructor")
	{
		LinkedList<int> list4;
		list4.push_at(10000, 0);
		list4.push_at(20000, 0);
		list4.push(2);
		list4.~LinkedList();
		CHECK(list4.getSize() == 0);
	}

	SECTION("Check is sorting works correctly")
	{
		LinkedList<int> list5;
		list5.push_at(10000, 0);
		list5.push_at(20000, 0);
		list5.push(2);
		list5.sort();
		CHECK(list5.get(0) == 2);
		CHECK(list5.get(1) == 10000);
		CHECK(list5.get(2) == 20000);
	}

	SECTION("Check something harder with sorting 1000 - 1")
	{
		LinkedList<int> list6;
		for (int i = 0; i < 1000; ++i)
		{
			list6.push(i);
		}
		list6.sort();
		for (int i = 0; i < 1000; ++i)
		{
			CHECK(list6.get(i) == i);
		}
	}
	
	SECTION("Check if erase with iterator removes items correctly")
	{
		LinkedList<int> list7;
		for (int i = 0; i < 1000; ++i)
		{
			list7.push(i);
		}
		auto it = list7.begin();
		for (int i = 0; i < 1000; ++i)
		{
			it = list7.erase(it);
		}
		CHECK(list7.getSize() == 0);
	}
}
