 
 
#include <mysql.h>
#include <iostream>
#include"Header.h"
using namespace std;
 
 
MYSQL* BestPlanDB:: MakeConnection()
{
	MYSQL* conn;

	conn = mysql_init(0);

	conn = mysql_real_connect(conn, "localhost", "root", "password", "BestPlanDB", 3306, NULL, 0);
	return conn;
}
bool BestPlanDB::CheckConnection(const  MYSQL* connect)
{
	bool status;
	(connect) ? status = true : status = false;
	return status;
}
void BestPlanDB::ShowTable()
{
	MYSQL* newconn = MakeConnection();
	MYSQL_ROW row;
	MYSQL_RES* res;

	if (CheckConnection(newconn))
	{
		string query = "SELECT * FROM User  ";
		const char* q = query.c_str();
		 
		qstate = mysql_query(newconn, q);

		 
		if (!qstate)
		{
			res = mysql_store_result(newconn);
			 
				 
				while (row = mysql_fetch_row(res))
				{
					printf("UserID: %s, Login: %s, Password: %s, Email: %s\n", row[0], row[1], row[2],row[3]);
				}
			 
		}
		else
		{
			cout << "Query failed: " << mysql_error(newconn) << endl;
		}
	}
	 
}
 
   

  bool  BestPlanDB::InsertIntoDB(string record)
  {
	  MYSQL* newconn = MakeConnection();
	  MYSQL_ROW row;
	  MYSQL_RES* res;
	   
	  if (CheckConnection(newconn))
	  {
		  string query = "SELECT * FROM User  ";
		  const char* q = query.c_str();
		  res = mysql_store_result(newconn);
		  int num_fields = mysql_num_fields(res);
		  int num_rows = mysql_num_rows(res);
		  qstate = mysql_query(newconn, q);
		   
		  if (!qstate)
		  {
			   
			  
			  
		  }
		  else
		  {
			  cout << "Query failed: " << mysql_error(newconn) << endl;
		  }
	  }
	  else return false;
  }
  int BestPlanDB::CountOfRecords()
  {
	  MYSQL* newconn = MakeConnection();
	  MYSQL_ROW row;
	  MYSQL_RES* res;

	  if (CheckConnection(newconn))
	  {
		  string query = "SELECT * FROM User  ";
		  const char* q = query.c_str();
		   
		  qstate = mysql_query(newconn, q);

		  if (!qstate)
		  {

			  res = mysql_store_result(newconn);
			   
			  int num_rows = mysql_num_rows(res);
			  
			  return   num_rows;

		  }
		  else
		  {
			  return -1;
		  }
	  }
  }
  string BestPlanDB::getRecord(int id)
  {
	  
  }
int main()
{
	 
	BestPlanDB obj;
	 
	obj.ShowTable();
	cout<<obj.CountOfRecords();
	
	obj.ShowTable();
	return 0;
}
