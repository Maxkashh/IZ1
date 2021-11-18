#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include"Header.h"


 
 
 
TEST(init, test2)
{
	BestPlanDB obj;
	EXPECT_NE(obj.CountOfRecords(), 3);
	 

}