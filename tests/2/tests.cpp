#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include "interface.h"

const string TheBoss = "Uspeshnia";

const string lozenec =
    "Uspeshnia - Gosho \n"
    "Uspeshnia - Misho \n"
    "Gosho     - Pesho \n"
    "Gosho     - Dancho\n"
    "Pesho     - Alex  \n"
    "Dancho    - Boris \n"
    "Dancho    - Kamen \n"
    "Uspeshnia - Slavi \n"
    "Slavi     - Slav1 \n"
    "Slavi     - Slav2 \n"
    "Slav1     - Mecho \n"
    "Mecho     - Q12Adl\n";

const string large =
    "Uspeshnia - 1\n"
    "1-2\n1-3\n1-4\n1-5\n1-6\n1-7\n"
    "2-21\n2-22\n2-23\n2-24\n2-25\n2-26\n2-27\n2-28\n"
    "3-31\n3-32\n3-33\n3-34\n3-35\n3-36\n3-37\n3-38\n3-39\n";

const string loz_new =
    " Uspeshnia   -  MishoPetrov \n"
    " MishoPetrov -  Misho       \n"
    " MishoPetrov -  Slav        \n";


void create(const string& str)
{
    Hierarchy h(str);
}

TEST_CASE("Create and save hierarchy") {
    SECTION("Empty") {
        Hierarchy h("");

        REQUIRE(h.num_employees() == 0);
        REQUIRE(!h.find(TheBoss));
        REQUIRE(h.print() == "");
    }

    SECTION("One pair") {
        const string only_one = "Uspeshnia-Pesho\n";
        
        Hierarchy h(only_one);

        REQUIRE(h.num_employees() == 2);
        
        REQUIRE(h.find(TheBoss));
        REQUIRE(h.find("Pesho"));

        REQUIRE(h.longest_chain() == 2);
        REQUIRE(h.manager("Pesho") == TheBoss);
        
        REQUIRE(h.num_subordinates(TheBoss) == 1);
        REQUIRE(h.num_subordinates("Pesho") == 0);

        REQUIRE(h.print() == only_one);
    }

    SECTION("Loz new") {
        const string loz_print = "Uspeshnia-MishoPetrov\nMishoPetrov-Misho\nMishoPetrov-Slav\n";

        Hierarchy h(loz_new);
        REQUIRE(h.num_employees() == 4);

        REQUIRE(h.find(TheBoss));
        REQUIRE(!h.find("Pesho"));
        REQUIRE(h.find("Misho"));
        REQUIRE(h.find("MishoPetrov"));

        REQUIRE(h.longest_chain() == 3);
        REQUIRE(h.manager("MishoPetrov") == TheBoss);
        REQUIRE(h.manager("Misho") == "MishoPetrov");
        REQUIRE(h.manager("Misho") == h.manager("Slav"));

        REQUIRE(h.num_subordinates(TheBoss) == 1);
        REQUIRE(h.num_subordinates("MishoPetrov") == 2);

        REQUIRE(h.print() == loz_print);
    }

    SECTION("Errors") {
        const string error_format = "Uspeshnia baba Yaga";
        const string no_parent = "Uspeshnia   -  MishoPetrov \n Ivan-Dragan";

        REQUIRE_THROWS(create(error_format));
        REQUIRE_THROWS(create(no_parent));
    }
}


TEST_CASE("Simple selectors") {
    Hierarchy loz(lozenec);
    Hierarchy empty("");

    SECTION("Number employees") {
        REQUIRE(empty.num_employees() == 0);
        REQUIRE(loz.num_employees() == 13);
    }

    SECTION("Manager") {
        REQUIRE(loz.manager(TheBoss) == "");
        REQUIRE(loz.manager("Slavi") == TheBoss);
        REQUIRE(loz.manager("Slav1") == "Slavi");
        REQUIRE(loz.manager("Mecho") == "Slav1");
    }

    SECTION("Number subordinates") {
        REQUIRE(loz.num_subordinates(TheBoss) == 3);
        REQUIRE(loz.num_subordinates("Alex") == 0);

        REQUIRE(loz.num_subordinates("NoName") < 0);
        REQUIRE(empty.num_subordinates("NoName") < 0);
    }

    SECTION("Longest chain") {
        REQUIRE(empty.longest_chain() == 0);
        REQUIRE(loz.longest_chain() == 5);
    }

    SECTION("Find") {
        REQUIRE(!empty.find(""));
        REQUIRE(!empty.find(TheBoss));
        REQUIRE(!empty.find("baba"));

        REQUIRE(loz.find(TheBoss));
        REQUIRE(loz.find("Slavi"));
        REQUIRE(loz.find("Slav1"));
        REQUIRE(loz.find("Slav2"));
        REQUIRE(loz.find("Pesho"));
        REQUIRE(loz.find("Alex"));

        REQUIRE(!loz.find(""));
        REQUIRE(!loz.find("Alex2"));
        REQUIRE(!loz.find("alex"));
    }
}


TEST_CASE("Overloaded") {
    Hierarchy h (large);
    Hierarchy loz(lozenec);
    Hierarchy empty("");

    REQUIRE(h.num_overloaded() == 2);
    REQUIRE(loz.num_overloaded() == 0);
    REQUIRE(empty.num_overloaded() == 0);
}


TEST_CASE("Salary") {
    Hierarchy h(large);
    Hierarchy loz(lozenec);

    REQUIRE(h.getSalary(TheBoss) == 1650);
    REQUIRE(h.getSalary("1") == 3850);
    REQUIRE(h.getSalary("31") == 0);
        
    
    REQUIRE(loz.getSalary(TheBoss) == 1950);
    REQUIRE(loz.getSalary("Alex") == 0);
    REQUIRE(loz.getSalary("Gosho") == 1150);
    REQUIRE(loz.getSalary("Batko") == -1);
}


TEST_CASE("Fire") {
    Hierarchy loz(loz_new);

    CHECK(loz.find("MishoPetrov"));
    CHECK(loz.num_employees() == 4);
    
    REQUIRE(loz.fire("MishoPetrov"));

    REQUIRE(!loz.find("MishoPetrov"));
    REQUIRE(loz.num_employees() == 3);
    REQUIRE(loz.num_subordinates(TheBoss) == 2);

    REQUIRE(!loz.fire("MishoPetrov"));
    REQUIRE(!loz.fire("baba"));
    REQUIRE(!loz.fire(TheBoss));
}


TEST_CASE("Hire") {
    Hierarchy loz(loz_new);
    CHECK(!loz.find("Ico_Petrov"));
    CHECK(loz.num_employees() == 4);
    CHECK(loz.num_subordinates("MishoPetrov") == 2);
    
    
    REQUIRE(loz.hire("Ico_Petrov", "MishoPetrov"));

    REQUIRE(loz.find("Ico_Petrov"));
    REQUIRE(loz.num_employees() == 5);
    REQUIRE(loz.num_subordinates("MishoPetrov") == 3);
    REQUIRE(loz.manager("Ico_Petrov") == "MishoPetrov");

    
    REQUIRE(loz.hire("Ico_Petrov", "Misho"));

    REQUIRE(loz.find("Ico_Petrov"));
    REQUIRE(loz.num_employees() == 5);
    REQUIRE(loz.num_subordinates("MishoPetrov") == 2);
    REQUIRE(loz.num_subordinates("Misho") == 1);
    REQUIRE(loz.manager("Ico_Petrov") == "Misho");

    REQUIRE(!loz.hire("Ico_Petrov", "BadName"));
    REQUIRE(!loz.hire("Ico", "BadName"));
}


TEST_CASE("Incorporate") {
    Hierarchy loz(lozenec);

    CHECK(loz.longest_chain() == 5);
    CHECK(loz.num_employees() == 13);
    CHECK(loz.num_subordinates(TheBoss) == 3);
    CHECK(loz.manager("Misho") == TheBoss);
    loz.incorporate();

    REQUIRE(loz.print() ==
        "Uspeshnia-Gosho\nGosho-Dancho\nGosho-Misho\nGosho-Slavi\nDancho-Boris\n"
        "Dancho-Pesho\nSlavi-Slav1\nBoris-Kamen\nPesho-Alex\nSlav1-Mecho\nSlav1-Slav2\nMecho-Q12Adl\n");

    REQUIRE(loz.longest_chain() == 6);
    REQUIRE(loz.num_employees() == 13);
    REQUIRE(loz.num_subordinates(TheBoss) == 1);
    REQUIRE(loz.manager("Misho") == "Gosho");


    Hierarchy h(large);
    CHECK(h.longest_chain() == 4);
    CHECK(h.num_employees() == 25);
    CHECK(h.num_subordinates("3") == 9);

    h.incorporate();

    REQUIRE(h.print() ==
        "Uspeshnia-1\n1-3\n3-2\n3-31\n3-4\n3-5\n3-6\n3-7\n2-21\n31-32\n31-33\n31-34\n31-35\n31-36\n31-37\n"
        "31-38\n31-39\n21-22\n21-23\n21-24\n21-25\n21-26\n21-27\n21-28\n");
    REQUIRE(h.longest_chain() == 6);
    REQUIRE(h.num_employees() == 25);
    REQUIRE(h.num_subordinates(TheBoss) == 1);
    REQUIRE(h.manager("3") == "1");
    REQUIRE(h.manager("2") == "3");
    REQUIRE(h.num_subordinates("21") == 7);
    REQUIRE(h.num_subordinates("3") == 6);
}


TEST_CASE("Modernize") {
    Hierarchy loz(lozenec);

    CHECK(loz.longest_chain() == 5);
    CHECK(loz.num_employees() == 13);
    CHECK(loz.num_subordinates(TheBoss) == 3);
    CHECK(loz.manager("Dancho") == "Gosho");
    loz.modernize();

    REQUIRE(loz.print() == 
        "Uspeshnia-Dancho\nUspeshnia-Misho\nUspeshnia-Pesho\nUspeshnia-Slav1\nUspeshnia-Slav2\nDancho-Boris\n"
        "Dancho-Kamen\nPesho-Alex\nSlav1-Q12Adl\n");
    REQUIRE(loz.longest_chain() == 3);
    REQUIRE(loz.num_employees() == 10);
    REQUIRE(loz.manager("Dancho") == TheBoss);
    REQUIRE(!loz.find("Gosho"));
    REQUIRE(!loz.find("Mecho"));
    REQUIRE(loz.find("Alex"));


    Hierarchy h(large);
    CHECK(h.longest_chain() == 4);
    CHECK(h.num_employees() == 25);
    CHECK(h.num_subordinates(TheBoss) == 1);
    CHECK(h.manager("3") == "1");
    h.modernize();
    REQUIRE(h.print() ==
        "Uspeshnia-2\nUspeshnia-3\nUspeshnia-4\nUspeshnia-5\nUspeshnia-6\nUspeshnia-7\n"
        "2-21\n2-22\n2-23\n2-24\n2-25\n2-26\n2-27\n2-28\n3-31\n3-32\n3-33\n3-34\n3-35\n3-36\n3-37\n3-38\n3-39\n");
    REQUIRE(h.longest_chain() == 3);
    REQUIRE(h.num_employees() == 24);
    REQUIRE(h.num_subordinates(TheBoss) == 6);
    REQUIRE(h.manager("3") == TheBoss);
    REQUIRE(!h.find("1"));
}


TEST_CASE("Join") {
    Hierarchy l_new(loz_new);
    Hierarchy loz(lozenec);
    Hierarchy h(large);

    Hierarchy l2 = loz.join(loz);
    REQUIRE(l2.print() == loz.print());
    REQUIRE(h.print() == h.join(h).print());

    Hierarchy joined = l_new.join(loz);
    REQUIRE(joined.print() ==
        "Uspeshnia-Gosho\nUspeshnia-Misho\nUspeshnia-MishoPetrov\nUspeshnia-Slavi\nGosho-Dancho\nGosho-Pesho"
        "\nMishoPetrov-Slav\nSlavi-Slav1\nSlavi-Slav2\nDancho-Boris\nDancho-Kamen\nPesho-Alex\nSlav1-Mecho\nMecho-Q12Adl\n");
    REQUIRE(joined.num_employees() == 15);
    REQUIRE(joined.longest_chain() == 5);

    Hierarchy joined2 = h.join(loz);
    REQUIRE(joined2.num_employees() == 13 + 24);
    REQUIRE(joined2.num_subordinates(TheBoss) == 4);
    REQUIRE(joined2.num_overloaded() == 2);
}

