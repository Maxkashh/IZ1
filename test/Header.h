#pragma once
#include <mysql.h>
#include <iostream>
#include<string>
int qstate;
class BestPlanDB : public MYSQL
{
public:
	BestPlanDB() = default;
	BestPlanDB(const BestPlanDB&) = delete;
	~BestPlanDB() = default;

	BestPlanDB& operator = (const BestPlanDB&) = delete;
	bool InsertIntoDB(std::string record);
	void DeleteRecord(int id);
	void CheckRecord(std::string record);
	std::string getRecord(int id);
	int CountOfRecords();
	void ShowTable();

private:

	MYSQL* MakeConnection();
	bool CheckConnection(const MYSQL* connect);

};