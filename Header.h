#pragma once
#include <mysql/mysql.h>
#include <iostream>
#include<string>
#include<algorithm>
#include<vector>

int qstate;
class BestPlanDB  
{
public:
	BestPlanDB() = default;
	BestPlanDB(const BestPlanDB&) = delete;
	~BestPlanDB() = default;

	BestPlanDB& operator = (const BestPlanDB&) = delete;

    int New_Task(int user_id,int new_task_id, const std::string& new_task);
    int Update_Task(int user_id,int new_task_id, const std::string& new_task);
    std::vector<std::string> get_all_tasks(int user_id);
    std::vector<std::pair<int, std::vector<std::string>>>login(const std::string &user_login,const std::string &user_password);
    int Insert_New_User(const std::string& user_login,const std::string& user_mail,const std::string& user_password);
    int Insert_New_Task(int user_id,std::vector<std::string>tasks);
    int Delete_Task(int user_id,int new_task_id);
    void MakeDataBase();
private:

	MYSQL* MakeConnection() const;
	bool CheckConnection(const MYSQL* connect);

};
