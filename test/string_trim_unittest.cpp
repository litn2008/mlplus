#include <string>
#include <vector>
#include "gtest/gtest.h"
#include <iostream>
#include "string_utility.h"
using namespace std;
using namespace mlplus;
TEST(trimTest, trimLeft){
    string a = "\tab\t";
    trimLeft(a);
    EXPECT_EQ(a, "ab\t");
}
TEST(trimTest, trimRight){
    string a = "\tab\t";
    trimRight(a);
    EXPECT_EQ(a, "\tab");
}
TEST(trimTest, trimBlank){
    string a = "   ";
    trimLeft(a);
    EXPECT_TRUE(a.empty());
    trimRight(a);
    EXPECT_TRUE(a.empty());
}
TEST(trimTest, trimEmpty){
    string a = "";
    trimLeft(a);
    EXPECT_TRUE(a.empty());
    trimRight(a);
    EXPECT_TRUE(a.empty());
}
        
TEST(trimTest, trimNormal){
    string a = "\t   abcdef  \t";
    trim(a);
    EXPECT_EQ(a, "abcdef");

    a = "abcdef  \t";
    trim(a);
    EXPECT_EQ(a, "abcdef");

    a = "  abcdef";
    trim(a);
    EXPECT_EQ(a, "abcdef");

    a = "\t   \t";
    trim(a);
    EXPECT_EQ(a, "");

    a = "";
    trim(a);
    EXPECT_EQ(a, "");
}

TEST(trimTest, trimNormal2){

    string a = "\tab\t";
    trimLeft(a, "\t ");
    EXPECT_EQ(a, "ab\t");
    trimRight(a);
    EXPECT_EQ(a, "ab");

    a = "   ";
    trimLeft(a, " ");
    EXPECT_TRUE(a.empty());
    trimRight(a, " ");
    EXPECT_TRUE(a.empty());

    a = "";
    trimLeft(a, " \t");
    EXPECT_TRUE(a.empty());
    trimRight(a, " ");
    EXPECT_TRUE(a.empty());

    a = "\t   abcdef  \t";
    trim(a, "\t ");
    EXPECT_EQ(a, "abcdef");

    a = "abcdef  \t";
    trim(a, "\t ");
    EXPECT_EQ(a, "abcdef");

    a = "  abcdef";
    trim(a, "\t ");
    EXPECT_EQ(a, "abcdef");

    a = "\t   \t";
    trim(a, "\t ");
    EXPECT_EQ(a, "");

    a = "";
    trim(a, "\t ");
    EXPECT_EQ(a, "");
}

TEST(trimTest, trimCopyNormal){
    string a = "\tab\t";
    EXPECT_EQ(trimLeftCopy(a), "ab\t");
    EXPECT_EQ(trimRightCopy(a), "\tab");
    EXPECT_EQ(trimCopy(a), "ab");

    a = "   ";

    EXPECT_EQ(trimLeftCopy(a), "");
    EXPECT_EQ(trimRightCopy(a), "");
    EXPECT_EQ(trimCopy(a), "");

    a = "";
    EXPECT_EQ(trimLeftCopy(a), "");
    EXPECT_EQ(trimRightCopy(a), "");
    EXPECT_EQ(trimCopy(a), "");

    a = "\t  abcdef  \t";
    EXPECT_EQ(trimLeftCopy(a), "abcdef  \t");
    EXPECT_EQ(trimRightCopy(a), "\t  abcdef");
    EXPECT_EQ(trimCopy(a), "abcdef");

    a = "abcdef  \t";
    EXPECT_EQ(trimLeftCopy(a), "abcdef  \t");
    EXPECT_EQ(trimRightCopy(a), "abcdef");
    EXPECT_EQ(trimCopy(a), "abcdef");

    a = "  abcdef";
    EXPECT_EQ(trimLeftCopy(a), "abcdef");
    EXPECT_EQ(trimRightCopy(a), "  abcdef");
    EXPECT_EQ(trimCopy(a), "abcdef");


    a = "\t   \t";
    EXPECT_EQ(trimLeftCopy(a), "");
    EXPECT_EQ(trimRightCopy(a), "");
    EXPECT_EQ(trimCopy(a), "");


    a = "";
    EXPECT_EQ(trimLeftCopy(a), "");
    EXPECT_EQ(trimRightCopy(a), "");
    EXPECT_EQ(trimCopy(a), "");

}

TEST(trimTest, trimCopyToNormal){
    string a = "\tab\t";
    string b;
    trimLeftCopyTo(a, b);
    EXPECT_EQ(b, "ab\t");
    trimRightCopyTo(a, b);
    EXPECT_EQ(b, "\tab");
    trimCopyTo(a, b);
    EXPECT_EQ(b, "ab");

    a = "   ";
    trimLeftCopyTo(a, b);
    EXPECT_EQ(b, "");
    trimRightCopyTo(a, b);
    EXPECT_EQ(b, "");
    trimCopyTo(a, b);
    EXPECT_EQ(b, "");


    a = "";
    trimLeftCopyTo(a, b);
    EXPECT_EQ(b, "");
    trimRightCopyTo(a, b);
    EXPECT_EQ(b, "");
    trimCopyTo(a, b);
    EXPECT_EQ(b, "");


    a = "\t  abcdef  \t";
    trimLeftCopyTo(a, b);
    EXPECT_EQ(b, "abcdef  \t");
    trimRightCopyTo(a, b);
    EXPECT_EQ(b, "\t  abcdef");
    trimCopyTo(a, b);
    EXPECT_EQ(b, "abcdef");

    a = "abcdef  \t";
    trimLeftCopyTo(a, b);
    EXPECT_EQ(b, "abcdef  \t");
    trimRightCopyTo(a, b);
    EXPECT_EQ(b, "abcdef");
    trimCopyTo(a, b);
    EXPECT_EQ(b, "abcdef");

    a = "  abcdef";
    trimLeftCopyTo(a, b);
    EXPECT_EQ(b, "abcdef");
    trimRightCopyTo(a, b);
    EXPECT_EQ(b, "  abcdef");
    trimCopyTo(a, b);
    EXPECT_EQ(b, "abcdef");
}

TEST(trimTest, trimCopyToNormal2){
    string a = "\tab\t";
    string b;
    trimLeftCopyTo(a, b, "\t ");
    EXPECT_EQ(b, "ab\t");
    trimRightCopyTo(a, b, "\t ");
    EXPECT_EQ(b, "\tab");
    trimCopyTo(a, b, "\t ");
    EXPECT_EQ(b, "ab");

    a = "   ";
    trimLeftCopyTo(a, b, "\t ");
    EXPECT_EQ(b, "");

    trimRightCopyTo(a, b, "\t ");
    EXPECT_EQ(b, "");
    trimCopyTo(a, b, "\t ");
    EXPECT_EQ(b, "");

    a = "";
    trimLeftCopyTo(a, b, "\t ");
    EXPECT_EQ(b, "");
    trimRightCopyTo(a, b, "\t ");
    EXPECT_EQ(b, "");
    trimCopyTo(a, b, "\t ");
    EXPECT_EQ(b, "");


    a = "\t  abcdef  \t";
    trimLeftCopyTo(a, b, "\t ");
    EXPECT_EQ(b, "abcdef  \t");
    trimRightCopyTo(a, b, "\t ");
    EXPECT_EQ(b, "\t  abcdef");
    trimCopyTo(a, b, "\t ");
    EXPECT_EQ(b, "abcdef");

    a = "abcdef  \t";
    trimLeftCopyTo(a, b, "\t ");
    EXPECT_EQ(b, "abcdef  \t");
    trimRightCopyTo(a, b, "\t ");
    EXPECT_EQ(b, "abcdef");
    trimCopyTo(a, b, "\t ");
    EXPECT_EQ(b, "abcdef");

    a = "  abcdef";
    trimLeftCopyTo(a, b, "\t ");
    EXPECT_EQ(b, "abcdef");
    trimRightCopyTo(a, b, "\t ");
    EXPECT_EQ(b, "  abcdef");
    trimCopyTo(a, b, "\t ");
    EXPECT_EQ(b, "abcdef");

}

