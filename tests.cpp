
#include <gtest/gtest.h>


extern "C" {
#include "Functions.h"
#include "source.c"
}


TEST(TAG_TEST,Assert_1)
{
     char* tag=get_tag();
    EXPECT_EQ(get_tag(),tag);
    free(get_tag());
    free(tag);
}

TEST(TAG_TEST,Assert_2)
{
    const char* str=NULL;
    scanf("%s",str);

    EXPECT_EQ(get_name(str),"head");
}
TEST(TAG_TEST,Assert_3)
{
    EXPECT_EQ(get_closeTag("<body>"),"</body>");
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
