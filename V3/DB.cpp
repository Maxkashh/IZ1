
#include <mysql/mysql.h>
#include <iostream>
#include"DB.h"
#include<algorithm>
#include<cstring>


 MYSQL* BestPlanDB:: MakeConnection(const std::string &NameOfDataBase ) const
{
    MYSQL* conn;
    char buf[255];
    strcpy(buf,NameOfDataBase.c_str());
    conn = mysql_init(0);

    conn = mysql_real_connect(conn, "localhost", "root", "newpassword", buf, 3306, NULL, 0);
    return conn;
}
BestPlanDB::BestPlanDB(std::string &NameOfDataBase)
{
    MYSQL* conn;
    char buf[255];
    strcpy(buf,NameOfDataBase.c_str());
    MYSQL_RES* res=nullptr;
    conn = mysql_init(0);

    conn = mysql_real_connect(conn, "localhost", "root", "newpassword", buf, 3306, NULL, 0);
    bool status;
    (conn) ? status = true : status = false;

    if(status== false)
    {
        std::string query0="CREATE DATABASE `";
        query0+=NameOfDataBase;
        query0+="`";
        std::string  query ="CREATE TABLE `";
        std::string query2;
        std::string query3;
        std::string query4;

        query+=NameOfDataBase;
        query+="`";
        query+=".`User` ( `UserID` INT(11) NOT NULL AUTO_INCREMENT , `Login` VARCHAR(255) NOT NULL , `Password` VARCHAR(255) NOT NULL , `Email` VARCHAR(255) NOT NULL , PRIMARY KEY (`UserID`)) ENGINE = InnoDB;";
        query2=" CREATE TABLE `";
        query2+=NameOfDataBase;
        query2+="`";
        query2+=".`Tasks` ( `TaskID` INT NOT NULL AUTO_INCREMENT , `Task1` VARCHAR(255) NOT NULL , `Task2` VARCHAR(255) NOT NULL , `Task3` VARCHAR(255) NOT NULL , `Task4` VARCHAR(255) NOT NULL , `Task5` VARCHAR(255) NOT NULL , `Task6` VARCHAR(255) NOT NULL , `Task7` VARCHAR(255) NOT NULL , `Userid` INT(11) NOT NULL , PRIMARY KEY (`TaskID`)) ENGINE = InnoDB;";
        query3="ALTER TABLE `User` ADD INDEX( `UserID`);";
        query4="ALTER TABLE `User` ADD FOREIGN KEY (`UserID`) REFERENCES `User`(`UserID`) ON DELETE RESTRICT ON UPDATE CASCADE;";
        std::string query5="USE ";
        query5+=NameOfDataBase;
        std::string pass="newpassword";

        std::string s2 = "sudo mysql -u root -p" + pass+query0+query5+query+query2+query3+query4;
        system(s2.c_str());
        conn = mysql_init(0);

        conn = mysql_real_connect(conn, "localhost", "root", "newpassword", "DB", 3306, NULL, 0);

        (conn) ? status = true : status = false;
    }





    if(status== false)
    {
        throw "Bad connection! please try again!";
    }
    this->newconn=conn;
    this->NameOfDB=buf;


}


BestPlanDB::~BestPlanDB()
{
    mysql_close(newconn);
}


int BestPlanDB::Insert_New_Task(int user_id,get_strings tasks)
{
    int qstate;
    MYSQL_RES* res=nullptr;
    //this->newconn= MakeConnection("DB");


        std::string  query = "INSERT INTO `Tasks` (`TaskID`, `Task1`, `Task2`, `Task3`, `Task4`, `Task5`, `Task6`, `Task7`, `Userid`) VALUES (NULL";
        for(int i=0;i<7;i++)
        {
            query+=", ";
            query+="\'";
            query+=tasks[i];
            query+="\'";


        }
        query+=", ";
        query+="\'";
        query+=std::to_string(user_id);
        query+="\'";
        query+=");";
        const char* q = query.c_str();

        qstate = mysql_query(newconn, q);

        if (!qstate)
        {

            res = mysql_store_result(newconn);

            mysql_close(newconn);

            return 0;
        }
        else
        {
            mysql_close(newconn);
            return -1;
        }
    mysql_close(newconn);
    return -1;
}




int BestPlanDB::New_Task(int user_id,int new_task_id ,const std::string& new_task)
{
    int qstate;
    MYSQL_RES* res;
    std::string check;
    if(new_task_id<=0){return -1;}
    else{
        switch (new_task_id) {
            case 1: check="Task1";break;
            case 2: check="Task2";break;
            case 3: check="Task3";break;
            case 4: check="Task4";break;
            case 5: check="Task5";break;
            case 6: check="Task6";break;
            case 7: check="Task7";break;


        }
    }



        std::string  query = "UPDATE `Tasks` SET ";
        query+=check;
        query+="= ";
        query+="\"";
        query +=new_task;
        query+="\"";
        query+=" ";
        query+=" WHERE Userid= ";
        query+=std::to_string(user_id);
        const char* q = query.c_str();

        qstate = mysql_query(newconn, q);

        if (!qstate)
        {

            mysql_close(newconn);

            return 0;
        }
        else
        {
            mysql_close(newconn);
            return -1;
        }
    return -1;
}
get_strings BestPlanDB::get_all_tasks(int user_id)
{
    std::vector<std::string> arr{"empty task"};
    arr.reserve(7);
    int qstate;
    MYSQL_ROW row;
    MYSQL_RES* res;


        std::string query = "SELECT * FROM `Tasks` WHERE Userid= ";
        query+=std::to_string(user_id);
        int i=1;
        const char* q = query.c_str();

        qstate = mysql_query(newconn, q);


        if (!qstate)
        {
            res = mysql_store_result(newconn);


            while ((row = mysql_fetch_row(res) ))
            {
                for(;i<8;++i)
                { arr.emplace_back(row[i]);}



            }
            for(int i=0;i<8;i++)
            {
                if(arr[i]=="")
                {
                    arr[i]="empty task";
                }

            }

            return arr;

        }
        else
        {

            return arr;

        }

    return arr;

}

std::vector<BestPlanDB::Pair> BestPlanDB:: login(const std::string& user_login,const std::string& user_password)
{

        int qstate;
        MYSQL_ROW row;
        MYSQL_RES* res;


        std::string query = "SELECT UserID FROM `User` WHERE Login=";
        query+="\"";
        query +=user_login;
        query+="\"";
        query+=" AND Password=";
        query+="\"";
        query +=user_password;
        query+="\"";
        const char* q = query.c_str();

         qstate  = mysql_query(newconn, q);

        char buf[32];
        int count=0;

        if (!qstate)
        {
            res = mysql_store_result(newconn);
            while ((row = mysql_fetch_row(res)))
            {
                unsigned long* length = mysql_fetch_lengths(res);
                size_t size = length[0] < sizeof(buf)-1 ? length[0] : sizeof(buf)-1;
                memcpy(buf, row[0], size);
                buf[size] = '\0';
                count = (unsigned long)atoi(buf);
            }
            if(count==0)
            {
                std::vector<std::string> arr{"nothing"};
                Pair pair(count,arr);
                pair.tasks=arr;
                pair.id=count;
                std:: vector<Pair> result;
                result.emplace_back(pair.id,pair.tasks) ;


                return result;
            }

            std::vector<std::string> arr= BestPlanDB::get_all_tasks(count);
            std:: vector<Pair> result;
            Pair pair(count,arr);
            pair.tasks=arr;
            pair.id=count;
            result.emplace_back(pair.id,pair.tasks) ;



            return result;

        }
        else
        {

            std::vector<std::string> arr{"nothing"};
            Pair pair(count,arr);
            pair.tasks=arr;
            pair.id=count;
            std:: vector<Pair> result;
            result.emplace_back(pair.id,pair.tasks) ;
            return result;
        }



}


int BestPlanDB::Update_Task(int user_id,int new_task_id, const std::string& new_task)
{
    int qstate;
    MYSQL_RES* res;
    std::string check;
    switch (new_task_id) {
        case 1: check="Task1";break;
        case 2: check="Task2";break;
        case 3: check="Task3";break;
        case 4: check="Task4";break;
        case 5: check="Task5";break;
        case 6: check="Task6";break;
        case 7: check="Task7";break;


    }


        std::string  query = "UPDATE `Tasks` SET ";
        query+=check;
        query+="= ";
        query+="\"";
        query +=new_task;
        query+="\"";
        query+=" ";
        query+=" WHERE Userid= ";
        query+=std::to_string(user_id);
        const char* q = query.c_str();

        qstate = mysql_query(newconn, q);

        if (!qstate)
        {

            mysql_close(newconn);

            return 0;
        }
        else
        {
            return -1;
        }
    return -1;
}

int BestPlanDB::Insert_New_User(const std::string& user_login,const std::string& user_mail,const std::string& user_password)
{
        //newconn= MakeConnection(NameOfDB);
         MYSQL_RES* res;
         int qstate;
         std::string  query = "INSERT INTO `User` (`UserID`, `Login`, `Password`, `Email`) VALUES (NULL, ";

        query+="\'";
        query +=user_login;
        query+="\'";
        query+=", ";
        query+="\'";
        query +=user_password;
        query+="\'";
        query+=", ";
        query+="\'";
        query +=user_mail;
        query+="\'";
        query+=");";
        const char* q = query.c_str();

        qstate = mysql_query(newconn, q);

        if (!qstate)
        {
            res = mysql_store_result(newconn);
            mysql_close(newconn);

            return 0;
        }
        else
        {
            mysql_close(newconn);
            return -1;
        }
   return -1;

}
int BestPlanDB::Delete_Task(int user_id,int task_id)
{
    BestPlanDB::Update_Task(user_id,task_id,"");
    return 0;
}

//int main()
//{
//    std::string str="DB";
//    std::vector<std::string >str2={""};
//    BestPlanDB obj=BestPlanDB(str);
//    //int a=obj.Insert_New_User("hu","ffttff","aaaa");
//    int b=obj.Insert_New_Task(7,str2);
//}

//    Dobavlenie default tasks
// std::vector<std::string> arr;
//   std::string str="";
//    for(int i=0;i<8;++i){arr.push_back(str);}
//   int b=obj.Insert_New_Task(1,arr);
// Dobavlenie opredelennoi taski
//int c=obj.New_Task(1,1,"Play computer gahems");
// func Update rabotaet analogichno
// zamena na "" tipo udalenie
//int d=obj.Delete_Task(1,1);
//vse taski po id usera
//std::vector<std::string> arrr;
//arrr=obj.get_all_tasks(1);
//for(const auto& elem:arrr){std::cout<<elem<<" ";}
// taski po loginu i parolu

//}


