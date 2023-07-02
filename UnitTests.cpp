//
// Created by ivan on 02.07.23.
//

#include "UnitTests.hpp"
#include "ServerTest.hpp"

void UnitTests::init_tests(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    testing::InitGoogleMock(&argc, argv);
}


int UnitTests::run_tests() {
    return RUN_ALL_TESTS();
}

TEST_F(ServerTest, TestCreateTable) {
    ASSERT_EQ(server->CreateTable("table1"), true);
}

TEST_F(ServerTest, TestRemoveAllTables) {
    ASSERT_EQ(server->RemoveAllTables(), true);
}

TEST_F(ServerTest, TestColumnsInfoOne) {   //test 1 table
    server->CreateTable("table1");
    std::string columns;
    std::fstream f("table1");
    getline(f, columns);
    std::stringstream ss{columns};
    std::string word;
    columns = "Column names: ";
    while (ss >> word) {
        columns += word + " ";
    }
    columns += '\n';
    Tables temp;
    temp["table1"] = columns;
    ASSERT_EQ(server->ColumnsInfo(), temp);
}

TEST_F(ServerTest, TestColumnInfoSomeTables) {  // some tables
    std::string columns;
    server->CreateTable("table1");
    server->CreateTable("table2");
    std::fstream f("table1");
    getline(f, columns);
    std::stringstream ss{columns};
    std::string word;
    columns = "Column names: ";
    while (ss >> word)
        columns += word + " ";
    columns += '\n';
    Tables temp;
    temp["table1"] = columns;
    std::fstream f2("table2");
    getline(f2, columns);
    std::stringstream s{columns};
    columns = "Column names: ";
    while (s >> word)
        columns += word + " ";
    columns += '\n';
    temp["table2"] = columns;
    EXPECT_EQ(server->ColumnsInfo(), temp);
}

TEST_F(ServerTest, TestFiltration) {   // one and some conditionals
    server->CreateTable("table1");
    std::string ExpectedResult = "age id count num_words \n3   5  2     2         \n";
    EXPECT_EQ(server->FiltrationBy("age>=3", "table1"), ExpectedResult);
    EXPECT_EQ(server->FiltrationBy("age>=2 and id>=5", "table1"), ExpectedResult);
}

TEST_F(ServerTest, TestSortBy) {  // one and some conditionals
    server->CreateTable("table1");
    std::string ExpectedResult = "age id count num_words \n1   2  4     1         \n3   5  2     2         \n2   2  2     5         \n";
    EXPECT_EQ(server->SortBy("num_words", "table1"), ExpectedResult);
    EXPECT_EQ(server->SortBy("num_words and age", "table1"), ExpectedResult);
}



