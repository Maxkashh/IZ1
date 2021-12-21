#pragma once
#include <mysql/mysql.h>
#include <iostream>
#include<string>
#include<algorithm>
#include<vector>
using get_strings= std::vector<std::string>;

class BestPlanDB : public MYSQL
{
private:
    MYSQL*  MakeConnection(const std::string &NameOfDataBase) const;
    struct Pair
    {
        Pair(int i,const get_strings& task):id(i),tasks(task){}

        int id;
        get_strings tasks;
    };
    char *NameOfDB;
    MYSQL* newconn;

public:
	BestPlanDB(std::string &NameOdDataBase);
	BestPlanDB(const BestPlanDB&) = delete;
	~BestPlanDB() ;

	BestPlanDB& operator = (const BestPlanDB&) = delete;

    int New_Task(int user_id,int new_task_id, const std::string& new_task);
    int Update_Task(int user_id,int new_task_id, const std::string& new_task);
    get_strings get_all_tasks(int user_id);
    std::vector<Pair>login(const std::string &user_login,const std::string &user_password);
    int Insert_New_User(const std::string& user_login,const std::string& user_mail,const std::string& user_password);
    int Insert_New_Task(int user_id,get_strings tasks);
    int Delete_Task(int user_id,int new_task_id);


};